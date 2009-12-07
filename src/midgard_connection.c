/* 
 * Copyright (C) 2006, 2007, 2008, 2009 Piotr Pokora <piotrek.pokora@gmail.com>
 * Copyright (C) 2006 Jukka Zitting <jukka.zitting@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "midgard_connection.h"
#include "midgard_error.h"
#include "schema.h"
#include <libgda/libgda.h>
#include "midgard_core_connection.h"
#include "midgard_core_object.h"
#include "midgard_core_query.h"
#include "midgard_core_config.h"
#include "midgard_core_query_builder.h"
#include "midgard_user.h"

/**
 * SECTION: MidgardConnection
 * @short_descritpion: MidgardConnection description
 */ 

#define MGD_MYSQL_HOST "127.0.0.1"
#define MGD_MYSQL_DATABASE "midgard"
#define MGD_MYSQL_USERNAME "midgard"
#define MGD_MYSQL_PASSWORD "midgard"

gboolean 
__midgard_connection_open (MidgardConnection *mgd, GHashTable **hashtable, gboolean init_schema);

static MidgardConnectionPrivate *
midgard_connection_private_new (void)
{
	MidgardConnectionPrivate *cnc_private = 
		g_new(MidgardConnectionPrivate, 1);

	cnc_private->pattern = NULL;	
	cnc_private->config = NULL;
	cnc_private->connected = FALSE;
	cnc_private->free_config = FALSE;
	cnc_private->loghandler = 0;
	cnc_private->loglevel = 0;	
	cnc_private->user = NULL;
	cnc_private->inherited = FALSE;
#ifdef HAVE_LIBGDA_4
	cnc_private->parser = NULL;
#else
	cnc_private->client = NULL;
#endif
	cnc_private->connection = NULL;
	cnc_private->configname = NULL;

	cnc_private->error_clbk_connected = FALSE;
	cnc_private->authtypes = NULL;
	cnc_private->authstack = NULL;

	/* Initialize thread *if* you need correct connection uptime when you use only one procces.
	   It works fine in child proccesses */
	/* g_thread_init(NULL); */
	cnc_private->timer = g_timer_new();
	g_timer_start(cnc_private->timer);	

	return cnc_private;
}

static void _midgard_connection_finalize(GObject *object)
{
	g_assert(object != NULL);
	MidgardConnection *self = (MidgardConnection *) object;

	if (self->err != NULL)
		g_clear_error(&self->err);

	if (self->errstr != NULL) {
		g_free(self->errstr);
		self->errstr = NULL;
	}

	if (self->priv->authstack) {
		g_slist_free(self->priv->authstack);
		self->priv->authstack = NULL;
	}

	g_timer_stop(self->priv->timer);
	gdouble bench = g_timer_elapsed(self->priv->timer, NULL);

	if (self->priv->loghandler) {
		g_message("MidgardConnection uptime %.04f seconds", bench);
		g_log_remove_handler(G_LOG_DOMAIN, self->priv->loghandler);
	}

	g_timer_destroy(self->priv->timer);

	g_free(self->priv);
	self->priv = NULL;
}

static void _midgard_connection_dispose(GObject *object)
{
	MidgardConnection *self = (MidgardConnection *) object;

	GdaConnection *gda_cnc = NULL;
#ifndef HAVE_LIBGDA_4
	GdaClient *gda_client = NULL;
#endif

	while (self->priv->user != NULL) {
		// emptying authstack
		gboolean res = midgard_user_log_out((MidgardUser *)self->priv->user);
		g_assert(res == TRUE);
	}

	/* Free only these data which are not inherited */
	if (!self->priv->inherited) {
		if(self->priv->free_config) {
			g_object_unref(self->priv->config);
			self->priv->config = NULL;
			self->priv->free_config = FALSE;
		}

#ifdef HAVE_LIBGDA_4
		if(self->priv->parser != NULL)
			g_object_unref(self->priv->parser);
#else
		gda_client = self->priv->client;
#endif

		gda_cnc = self->priv->connection;
	}

#ifndef HAVE_LIBGDA_4
	/* Unref and free those at the end. There might be some callbacks registered! */
	if (gda_client != NULL)
		g_object_unref(gda_client);
#endif

	/* Disconnect and do not invoke error callbacks */
	if (self->priv->error_clbk_connected)
		midgard_core_connection_disconnect_error_callback(self);

	if (gda_cnc != NULL) {

		g_object_unref(gda_cnc);
		g_signal_emit(self, MIDGARD_CONNECTION_GET_CLASS(self)->signal_id_disconnected, 0);
	}
}

static void _midgard_connection_class_init(
		gpointer g_class, gpointer g_class_data)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS (g_class);
	MidgardConnectionClass *klass = MIDGARD_CONNECTION_CLASS (g_class);

	gobject_class->finalize = _midgard_connection_finalize;
	gobject_class->dispose = _midgard_connection_dispose;

	/* signals */
	/**
	 * MidgardConnection::error:
	 *
	 * error signal is emitted every time when error set is different than MGD_ERR_OK
	 */ 
	klass->signal_id_error = 
		g_signal_new("error",
			G_TYPE_FROM_CLASS(g_class),
			G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
			G_STRUCT_OFFSET (MidgardConnectionClass, error),
			NULL, /* accumulator */
			NULL, /* accu_data */
			g_cclosure_marshal_VOID__VOID,
			G_TYPE_NONE,
			0);
		
	klass->signal_id_auth_changed = 
		g_signal_new("auth-changed",
			G_TYPE_FROM_CLASS(g_class),
			G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
			G_STRUCT_OFFSET (MidgardConnectionClass, auth_changed),
			NULL, /* accumulator */
			NULL, /* accu_data */
			g_cclosure_marshal_VOID__VOID,
			G_TYPE_NONE,
			0);

	klass->signal_id_lost_provider = 
		g_signal_new("lost-provider",
			G_TYPE_FROM_CLASS(g_class),
			G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
			G_STRUCT_OFFSET (MidgardConnectionClass, lost_provider),
			NULL, /* accumulator */
			NULL, /* accu_data */
			g_cclosure_marshal_VOID__VOID,
			G_TYPE_NONE,
			0);
	
	klass->signal_id_connected = 
		g_signal_new("connected",
			G_TYPE_FROM_CLASS(g_class),
			G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
			G_STRUCT_OFFSET (MidgardConnectionClass, connected),
			NULL, /* accumulator */
			NULL, /* accu_data */
			g_cclosure_marshal_VOID__VOID,
			G_TYPE_NONE,
			0);
	
	klass->signal_id_disconnected = 
		g_signal_new("disconnected",
			G_TYPE_FROM_CLASS(g_class),
			G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
			G_STRUCT_OFFSET (MidgardConnectionClass, disconnected),
			NULL, /* accumulator */
			NULL, /* accu_data */
			g_cclosure_marshal_VOID__VOID,
			G_TYPE_NONE,
			0);
}

static void
__connect_callback (MidgardConnection *self)
{
	self->priv->connected = TRUE;
}

static void
__disconnect_callback (MidgardConnection *self)
{
	self->priv->connected = FALSE;
}

static void _midgard_connection_instance_init(GTypeInstance *instance, gpointer g_class)
{
	MidgardConnection *self = (MidgardConnection *) instance;

	/* Public members */
	self->err = NULL;
	self->errstr = g_strdup("MGD_ERR_OK");

	/* Private members */
	self->priv = midgard_connection_private_new();

	g_signal_connect (G_OBJECT(self), "connected", G_CALLBACK(__connect_callback), (gpointer) self);
	g_signal_connect (G_OBJECT(self), "disconnected", G_CALLBACK(__disconnect_callback), (gpointer) self);
}

/* Registers the type as  a fundamental GType unless already registered. */
GType midgard_connection_get_type(void)
{
	static GType type = 0;
	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (MidgardConnectionClass),
			NULL,           /* base_init */
			NULL,           /* base_finalize */
			(GClassInitFunc) _midgard_connection_class_init,
			NULL,           /* class_finalize */
			NULL,           /* class_data */
			sizeof (MidgardConnection),
			0,              /* n_preallocs */
			(GInstanceInitFunc) _midgard_connection_instance_init /* instance_init */
		};
		type = g_type_register_static (G_TYPE_OBJECT, "MidgardConnection", &info, 0);
	}
	return type;
}

/**
 * midgard_connection_new:
 * 
 * Initializes new instance of MidgardConnection object type. 
 *
 * MidgardConnectionClass has no properties registered as class members. 
 * Every internal data of MidgardConnection object is accessible with API
 * functions, and is not settable or gettable as property's value.
 * Particular methods should be implemented for language bindings.
 *
 * #MidgardConnection objects holds runtime ( or request ) non persistent
 * data like authentication type, debug level, etc. 
 *
 * Persistent data like database name, blobs directory are associated with #MidgardConfig object.
 * 
 * Returns: pointer to #MidgardConnection object or %NULL on failure.
 */ 
MidgardConnection *midgard_connection_new(void){
	
	MidgardConnection *self = 
		g_object_new(MIDGARD_TYPE_CONNECTION, NULL);
	
	return self;
}

static gboolean 
__mysql_reconnect (MidgardConnection *mgd)
{
	g_assert (mgd != NULL);

	guint i = 0;
	gboolean opened;

	gda_connection_close_no_warning (mgd->priv->connection);
	g_signal_emit (mgd, MIDGARD_CONNECTION_GET_CLASS (mgd)->signal_id_disconnected, 0);

	/* Try to reconnect 3 times */
	do {
		g_usleep (5000000); /* 5 seconds interval */
		g_debug ("Trying to reopen connection");

		opened = gda_connection_open (mgd->priv->connection, NULL);
	
		if (opened) {
		
			g_signal_emit (mgd, MIDGARD_CONNECTION_GET_CLASS (mgd)->signal_id_connected, 0);
			g_debug ("Successfully reopened connection");
			return TRUE;
		}

		i++;

	} while (i < 3);

	return FALSE;
}

/**
 * Adds a named parameter to the given libgda connection string.
 
 @param cnc libgda connection string
 @param name parameter name
 @param value parameter value
 @param def default value (used if given value is NULL)
*/
static void cnc_add_part(
		GString *cnc,
		const gchar *name, const gchar *value, const gchar *def) 
{
	g_assert(cnc != NULL);
	g_assert(name != NULL);
	if (value == NULL) {
		value = def;
	}
#ifdef HAVE_LIBGDA_4
	if (*value) {
		gchar *tmp;

		/* Add a separating semicolon if there already are
		 parameters before this one. */
		
		if (cnc->len > 0) {
			g_string_append_c(cnc, ';');
		}
		tmp = gda_rfc1738_encode (name);
		g_string_append(cnc, tmp);
		g_free (tmp);

		g_string_append_c(cnc, '=');
		
		tmp = gda_rfc1738_encode (value);
		g_string_append(cnc, tmp);
		g_free (tmp);
	}
#else
	if (*value) {
		/* Add a separating semicolon if there already are
		 parameters before this one. */
		
		if (cnc->len > 0) {
			g_string_append_c(cnc, ';');
		}
		g_string_append(cnc, name);
		g_string_append_c(cnc, '=');
		
		/* Make sure that the parameter being added does not contain a
		 * semicolon that would confuse the simple libgda parser! */
		
		for(; *value; value++) {
			g_string_append_c(cnc, *value != ';' ? *value : ',');
		}
	}
#endif
}

gboolean __midgard_connection_open(
		MidgardConnection *mgd, 
		GHashTable **hashtable, gboolean init_schema)
{
	g_return_val_if_fail(mgd != NULL, FALSE);

	MIDGARD_ERRNO_SET (mgd, MGD_ERR_OK);

	gchar *host, *dbname, *dbuser, *dbpass, *loglevel, *tmpstr;
	guint port = 0;
#ifdef HAVE_LIBGDA_4
	gchar *auth = NULL;
#endif
	MidgardConfig *config = mgd->priv->config;
	host = config->host;
	dbname = config->database;
	dbuser = config->dbuser;
	dbpass = config->dbpass;
	loglevel = config->loglevel;
	port = config->dbport;
	gboolean enable_threads = config->gdathreads;

	/* Get 30% performance boost for non threaded applications */
	if(!enable_threads) 
		g_setenv("LIBGDA_NO_THREADS", "yes", TRUE);

	/* Initialize libgda */
#ifdef HAVE_LIBGDA_4
	gda_init ();
#else
	gchar **args = NULL;
	gda_init ("MIDGARD", "1.9", 0, args);
#endif
	midgard_connection_set_loglevel(mgd, loglevel, NULL);

	if(config->priv->dbtype == MIDGARD_DB_TYPE_SQLITE) {

		const gchar *sqlite_dir[] = {"data", NULL};
		gchar *path = midgard_core_config_build_path(sqlite_dir, NULL, TRUE);
		tmpstr = g_strconcat("DB_DIR=", path, ";", "DB_NAME=", dbname, NULL);
		g_free(path);

	} else if (config->priv->dbtype == MIDGARD_DB_TYPE_ORACLE) {

		GString *cnc = g_string_sized_new(100);
		cnc_add_part(cnc, "TNSNAME", dbname, MGD_MYSQL_HOST);
		cnc_add_part(cnc, "HOST", host, MGD_MYSQL_HOST);
		cnc_add_part(cnc, "DB_NAME", dbname, MGD_MYSQL_DATABASE);
#ifdef HAVE_LIBGDA_4
		tmpstr = g_string_free(cnc, FALSE);

		cnc = g_string_sized_new(100);
		cnc_add_part(cnc, "USERNAME", dbuser, MGD_MYSQL_USERNAME);
		cnc_add_part(cnc, "PASSWORD", dbpass, MGD_MYSQL_PASSWORD);
		auth = g_string_free(cnc, FALSE);
#else
		cnc_add_part(cnc, "USER", dbuser, MGD_MYSQL_USERNAME);
		cnc_add_part(cnc, "PASSWORD", dbpass, MGD_MYSQL_PASSWORD);
		tmpstr = g_string_free(cnc, FALSE);
#endif

	} else { 
		
		GString *cnc = g_string_sized_new(100);
		cnc_add_part(cnc, "HOST", host, MGD_MYSQL_HOST);

		if (port > 0) {

			GString *_strp = g_string_new("");
			g_string_append_printf (_strp, "%d", port);
			cnc_add_part (cnc, "PORT", _strp->str, "");
			g_string_free (_strp, TRUE);
		}

		cnc_add_part(cnc, "DB_NAME", dbname, MGD_MYSQL_DATABASE);
#ifdef HAVE_LIBGDA_4
		tmpstr = g_string_free(cnc, FALSE);

		GString *auth_str = g_string_sized_new(100);
		cnc_add_part(auth_str, "USERNAME", dbuser, MGD_MYSQL_USERNAME);
		cnc_add_part(auth_str, "PASSWORD", dbpass, MGD_MYSQL_PASSWORD);
		auth = g_string_free(auth_str, FALSE);
#else
		cnc_add_part(cnc, "USER", dbuser, MGD_MYSQL_USERNAME);
		cnc_add_part(cnc, "PASSWORD", dbpass, MGD_MYSQL_PASSWORD);
		
		tmpstr = g_string_free(cnc, FALSE);
#endif
	}

	GError *error = NULL;
#ifdef HAVE_LIBGDA_4
	GdaConnection *connection = gda_connection_open_from_string(
			config->dbtype, tmpstr, auth, GDA_CONNECTION_OPTIONS_NONE, &error);

	g_free(auth);	
#else
	GdaClient *client =  gda_client_new();
	GdaConnection *connection = gda_client_open_connection_from_string(
			client, config->dbtype, tmpstr, NULL, NULL, 0, &error);
	mgd->priv->cnc_str = g_strdup(tmpstr);
	mgd->priv->auth_str = NULL;
#endif

	if(connection == NULL) {

		MIDGARD_ERRNO_SET_STRING (mgd, MGD_ERR_NOT_CONNECTED, 
				" Database [%s]. %s", tmpstr, error->message);

		g_free(tmpstr);

		return FALSE;
	
	} 

	g_free(tmpstr);

#ifndef HAVE_LIBGDA_4
	mgd->priv->client = client;
#endif

	mgd->priv->connection = connection;
	midgard_core_connection_connect_error_callback (mgd);	

	if(init_schema) {
		
		if(!g_type_from_name("midgard_language")) {
			
			MidgardSchema *schema = g_object_new(MIDGARD_TYPE_SCHEMA, NULL);
			gchar *path = g_build_path(G_DIR_SEPARATOR_S, config->sharedir, "MidgardObjects.xml", NULL);
			midgard_schema_init(schema, (const gchar *)path);
			g_free(path);
			midgard_schema_read_dir(schema, config->sharedir);
			
			mgd->priv->schema = schema;
		}
	}

	//midgard_connection_set_loglevel(mgd, loglevel, NULL);

	/* Loads available authentication types */
	midgard_core_connection_initialize_auth_types(mgd);

	g_signal_emit (mgd, MIDGARD_CONNECTION_GET_CLASS (mgd)->signal_id_connected, 0);

	return TRUE;
}

/**
 * midgard_connection_open:	
 * @self: #MidgardConnection instance
 * @name: configuration file name
 * @error: pointer to store error 
 *
 * Opens a connection to the database, which is defined in named configuration. 
 * The configuration file is read from the system configuration directory
 * and is used as the configuration for the created connection. For example: `/etc`
 * directory is taken into account if library is compiled with `/usr' prefix, 
 * `/usr/local/etc` if compiled with `/usr/local` prefix, etc.
 *
 * Consider using midgard_connection_open_config(), if you need to open connection to 
 * database which is configured in user's home directory.
 *
 * If the named database configuration can not be read or the connection fails,
 * then %FALSE is returned and an error message is written to the global midgard
 * error state.
 *
 * It also initializes #MidgardSchema object (which is encapsulated by implementation )
 * and register all MgdSchema, #MidgardObjectClass derived classes defined by user.
 * This happens only when basic Midgard classes are not registered in GType system.
 * This is recommended way to initialize MgdSchema types.
 *  
 * Returns: %TRUE if the operation succeeded, %FALSE otherwise.
 */ 
gboolean 
midgard_connection_open (MidgardConnection *self, const char *name, GError **error)
{	
	g_assert(self != NULL);
	g_assert (name != NULL);
	g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

	MIDGARD_ERRNO_SET (self, MGD_ERR_OK);

	/* FIXME, it should be handled by GError */
	if(self->priv->config != NULL){
		midgard_set_error(self,
				MGD_GENERIC_ERROR,
				MGD_ERR_USER_DATA,
				"MidgardConfig already associated with "
				"MidgardConnection");
		return FALSE;
	}
	
	MidgardConfig *config = midgard_config_new();

	GError *rf_error = NULL;
	if(!midgard_config_read_file(config, name, FALSE, &rf_error)) {

		if(rf_error) 
			g_propagate_error(error, rf_error);	
		
		MIDGARD_ERRNO_SET (self, MGD_ERR_NOT_CONNECTED);
		return FALSE;
	}
	
	if(error)
		g_clear_error(&rf_error);

	self->priv->config = config;
	self->priv->free_config = TRUE;

	GHashTable *hash = NULL;
	gboolean rv = TRUE;

	if(!__midgard_connection_open(self, &hash, TRUE)) {

		MIDGARD_ERRNO_SET (self, MGD_ERR_NOT_CONNECTED);
		rv = FALSE;
	}

	g_hash_table_destroy(hash);
	
	return rv;
}

/**
 * midgard_connection_open_from_file:	
 * @mgd: #MidgardConnection instance
 * @filepath: configuration file path
 * @error: pointer to store error 
 *
 * Opens a connection to the database. 
 * The configuration file is read from given filepath. 
 * 
 * Take a look at midgard_connection_open() wrt #MidgardSchema.
 *  
 * Returns: %TRUE if the operation succeeded, %FALSE otherwise.
 */ 
gboolean midgard_connection_open_from_file(
		MidgardConnection *mgd, const char *filepath, GError **error)
{	
	g_assert(mgd != NULL);
	g_assert (filepath != NULL);
	g_return_val_if_fail (error == NULL || *error == NULL, FALSE);
	
	/* FIXME, it should be handled by GError */
	if(mgd->priv->config != NULL){
		midgard_set_error(mgd,
				MGD_GENERIC_ERROR,
				MGD_ERR_USER_DATA,
				"MidgardConfig already associated with "
				"MidgardConnection");
		return FALSE;
	}
	
	MidgardConfig *config = midgard_config_new();

	GError *rf_error = NULL;
	if(!midgard_config_read_file_at_path(config, filepath, &rf_error)) {

		if(rf_error) 
			g_propagate_error(error, rf_error);	

		return FALSE;
	}
	
	if(error)
		g_clear_error(&rf_error);

	mgd->priv->config = config;
	mgd->priv->free_config = TRUE;

	GHashTable *hash = NULL;
	gboolean rv = TRUE;

	if(!__midgard_connection_open(mgd, &hash, TRUE)) 
		rv = FALSE;

	if(hash)
		g_hash_table_destroy(hash);
	
	return rv;
}

/**
 * midgard_connection_open_all:
 * @userdir: switch to read configuration from system or user's directory
 *
 * Every key is configuration name, and value is #MidgardConnection object.
 * Use g_hash_table_destroy to free hashtable and all opened connections.
 *
 * Returns: Newly allocated full #GHashTable.
 */
extern GHashTable *midgard_connection_open_all(gboolean userdir)
{
	GHashTable *cncs = 
		g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_object_unref);
	GHashTable *hash = NULL;

	gchar **cfgs = midgard_config_list_files(userdir);
	
	if(!cfgs) 
		return FALSE;

	guint i = 0;

	while(cfgs[i] != NULL) {
		
		MidgardConnection *cnc = midgard_connection_new();
		g_debug("Initialize new connection using '%s' configuration", cfgs[i]);
		
		GError *error = NULL;
		MidgardConfig *config = midgard_config_new();
		
		if(!midgard_config_read_file(config, cfgs[i], userdir, &error)) {

			if(error) {
				g_warning("%s", error->message);
				g_error_free(error);
			}

			i++;
			continue;
		}

		cnc->priv->config = config;
		cnc->priv->free_config = TRUE;

		if(__midgard_connection_open(cnc, &hash, TRUE)) {

			g_hash_table_insert(cncs, g_strdup(cfgs[i]), cnc);
		
		} else {
			
			g_object_unref(cnc);
			g_warning("Configuration %s failed", cfgs[i]);
		}
		
		i++;
	}
	
	if(hash)
		g_hash_table_destroy(hash);

	g_strfreev(cfgs);
	
	return cncs;
}

/**
 * midgard_connection_open_config:
 * @self: [in]newly initialized #MidgardConnection object
 * @config: #MidgardConfig object
 *
 * Opens a #MidgardConnection with the given configuration. 
 *
 * Take a look at midgard_connection_open() wrt #MidgardSchema.
 *
 * If #MidgardConnection is already associated with given config, method returns %TRUE.
 * If associated with another one, %FALSE is returned and MGD_ERR_INTERNAL error is set.
 *
 * Returns: %TRUE on success, %FALSE otherwise
 */
gboolean midgard_connection_open_config(
		MidgardConnection *self, MidgardConfig *config)
{
	g_assert(self != NULL);	
	g_assert(config != NULL);

	if (self->priv->config && (self->priv->config == config))
		return TRUE;

	if (self->priv->config && (self->priv->config != config)) {

		MIDGARD_ERRNO_SET_STRING (self, MGD_ERR_INTERNAL, "Midgard connection already associated with configuration");
		return FALSE;
	}

	self->priv->config = config;

	GHashTable *hash = NULL;
	gboolean rv = TRUE;

	if(!__midgard_connection_open(self, &hash, TRUE))
		rv = FALSE;

	if(hash)
		g_hash_table_destroy(hash);

	return rv;
}

gboolean midgard_connection_struct_open_config(
		MidgardConnection *self, MidgardConfig *config)
{
	g_assert(self != NULL);
	g_assert(config != NULL);
	
	self->priv->config = config;
	
	if(!__midgard_connection_open(self, NULL, FALSE))
		return FALSE;
	
	return TRUE;
}

/**
 * midgard_connection_set_loglevel:
 * @self: #MidgardConnection instance
 * @level: Loglevel string
 * @log_func: log handler function
 *
 * Sets log level of the given MidgardConnection.
 * Overwrites internal #MidgardConnection's log level defined in configuration file. 
 * By default MidgardConnection holds loglevel which is associated with ( and duplicated 
 * from ) #MidgardConfig. 
 * #MidgardConfig object's log level isn't changed by this function
 *
 * This method is a shortcut which sets correctly loghandler,loglevel
   and GLib's log function. Default log function will be used if %NULL 
 * is defined. Core's default function is #midgard_error_default_log.
 * 
 * Available levels: error, warn, warning, info, message, debug.
 * warn is default loglevel, SQL queries are logged with debug level.
 * With info level, function names ( and classes' names ) are ( at least should be) logged in language bindings
 *
 * Returns: %TRUE if debug level is set, %FALSE otherwise
 */
gboolean midgard_connection_set_loglevel(
		MidgardConnection *self, const gchar *level, GLogFunc log_func)
{
	g_assert(self != NULL);

	GLogFunc _func = log_func;
	if(_func == NULL)
		_func = midgard_error_default_log;

	gint loglevel = 
		midgard_error_parse_loglevel(level);

	if(loglevel > -1)
		self->priv->loglevel = loglevel;
	else
		return FALSE;
	
	guint loghandler = midgard_connection_get_loghandler(self);
	if(loghandler)
		g_log_remove_handler(G_LOG_DOMAIN, loghandler);

	loghandler = g_log_set_handler(G_LOG_DOMAIN, G_LOG_LEVEL_MASK,
			_func, (gpointer)self);
	
	if(loghandler == 0)
		return FALSE;

	midgard_connection_set_loghandler(self, loghandler);

	return TRUE;
}

/**
 * midgard_connection_get_loglevel:
 * @self: MidgardConnection instance
 *
 * Returns: unsigned integer flag specified by GLogLevelFlags.
 */ 
guint midgard_connection_get_loglevel(MidgardConnection *self)
{
	g_assert(self != NULL);

	return self->priv->loglevel;
}

/**
 * midgard_connection_set_loghandler:
 * @self: #MidgardConnection instance
 * @loghandler: loghandler id
 *
 * Sets internal loghandler id associated with G_LOG_DOMAIN and loglevel.
 * Caller is responsible to remove loghandler using g_log_remove_handler
 * when new loglevel for G_LOG_DOMAIN is set.
 *
 * See also: #midgard_connection_set_loglevel 
 */ 
void midgard_connection_set_loghandler(
		MidgardConnection *self, guint loghandler){

	g_assert(self != NULL);

	/* if(self->priv->loghandler > 0) {
		g_warning("Remove old loghandler first");
		return;
	} */
	
	self->priv->loghandler = loghandler;

	return;
}

/**
 * midgard_connection_get_loghandler:
 * @self: #MidgardConnection instance
 * 
 * Returns: unsigned integer value which is associated with G_LOG_DOMAIN and 
 * MidgardConnection's loglevel currently set.
 */
guint midgard_connection_get_loghandler(MidgardConnection *self)
{
	g_assert(self != NULL);
	
	return self->priv->loghandler;
}

/**
 * midgard_connection_get_error:
 * @self: #MidgardConnection instance
 *
 * Error id may be one of set by #midgard_error.
 * Returns: Last error id set 
 */ 
gint midgard_connection_get_error(MidgardConnection *self)
{
	g_assert(self != NULL);

	return self->errnum;
}

/**
 * midgard_connection_set_error:
 * @self: #MidgardConnection instance
 * @errcode: error code
 *
 * Valid #errcode is one defined in #MgdErrorGeneric.
 */
void midgard_connection_set_error(MidgardConnection *self, gint errcode)
{
	g_assert(self != NULL);

	MIDGARD_ERRNO_SET(self, errcode);
}

/**
 * midgard_connection_get_error_string:
 * @self: #MidgardConnection instance
 *
 * Error string may be one set by #midgard_error.
 * Returns: last error string
 */
const gchar *midgard_connection_get_error_string(MidgardConnection *self)
{
	g_return_val_if_fail(self != NULL, NULL);

	return (const gchar *)self->errstr;
}

/**
 * midgard_connection_get_user:
 * @self: MidgardConnection instance
 *
 * NULL is explicitly returned if there's no midgard_user logged in 
 * for the given MidgardConnection.
 * See also #MidgardUser methods if you need midgard_person associated with user.
 * Returns: A pointer to MidgardUser instance or %NULL
 */ 
MidgardUser *midgard_connection_get_user(MidgardConnection *self)
{
	g_return_val_if_fail(self != NULL, NULL);

	if (self->priv->user == NULL)
		return NULL;

	if (!G_IS_OBJECT(self->priv->user))
		return NULL;

	return MIDGARD_USER(self->priv->user);
}

/**
 * midgard_connection_reopen:
 * @self: #MidgardConnection instance
 * 
 * This is MySQL optimized workaround for lost connection event.
 *
 * Returns: %TRUE on success, %FALSE otherwise
 */
gboolean midgard_connection_reopen(MidgardConnection *self)
{
	g_assert(self != NULL);

	const gchar *query = "SELECT id FROM person LIMIT 1";
	GdaDataModel *model =
		midgard_core_query_get_model(self, query);

	if (model) {

		g_object_unref(model);
		return TRUE;
	}

	guint dbtype = self->priv->config->priv->dbtype;
	const GList *events;
	glong errcode = 0;
	events = gda_connection_get_events (self->priv->connection);

	if (!events) {
		
		g_warning("Can not get connection events. Error code is unknown.");
		return FALSE;
	}

	GList *l;
	for (l = (GList *) events; l != NULL; l = l->next) {

		GdaConnectionEvent *event;
		event = GDA_CONNECTION_EVENT (l->data);

		if (gda_connection_event_get_event_type (event) == GDA_CONNECTION_EVENT_ERROR) {

			errcode = gda_connection_event_get_code(event);

			switch (dbtype) {

				case MIDGARD_DB_TYPE_MYSQL:

					if (errcode == 2006) { /* CR_SERVER_GONE_ERROR , we can not use it */
						g_debug("MySQL server has gone away. Reconnect.");
						return __mysql_reconnect(self);
					}
					break;

				default:
					/* do nothing */
					break;
			}
		}
	}

	return FALSE;
}

/**
 * midgard_connection_list_auth_types: 
 * @self: #MidgardConnection instance 
 * @n_types: a pointer to store number of returned types
 *
 * List available and registered authentication types.
 * Use g_free() to free returned array.
 * 
 * Returns: NULL terminated array with authentication types.
 */
gchar **
midgard_connection_list_auth_types (MidgardConnection *self, guint *n_types)
{
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (n_types != NULL, NULL);

	*n_types = 0;

	if (!self->priv->authtypes)
		return NULL;

	GSList *slist;
	guint j = 0;

	for (slist = self->priv->authtypes; slist != NULL; slist = slist->next) 
		j++;

	*n_types = j;

	if (*n_types == 0)
		return NULL;

	gchar **types = g_new (gchar*, *n_types+1);
	guint i = 0;

	for (slist = self->priv->authtypes; slist != NULL; slist = slist->next) {

		MgdCoreAuthType *mcat = (MgdCoreAuthType *) slist->data;
		types[i] = mcat->name;
		i++;
	}
	
	types[i] = NULL;

	return types;
}

/**
 * midgard_connection_is_connected:
 * @self: #MidgardConnection instance
 *
 * Returns: %TRUE if database connection is established, %FALSE otherwise
 */
gboolean 
midgard_connection_is_connected (MidgardConnection *self)
{
	g_return_val_if_fail (self != NULL, FALSE);

	return self->priv->connected;
}

/**
 * midgard_connection_copy:
 * @self: #MidgardConnection instance
 *
 * This function duplicates given #MidgardConnection. It doesn't make deep copy. 
 * All persistant data are kept unchanged, but runtime related members are reset 
 * to default state. This function is helpful if application is forking and new 
 * processes might have different environment variables.
 *
 * Call g_object_unref if returned object is no longer needed.
 *
 * Returns: Newly allocated and duplicated #MidgardConnection
 */ 
MidgardConnection *midgard_connection_copy(MidgardConnection *self)
{
	g_assert(self != NULL);

	MidgardConnection *new_mgd = midgard_connection_new();

	// override private connection properties
	new_mgd->priv->config = self->priv->config;
	new_mgd->priv->loglevel = self->priv->loglevel;
#ifdef HAVE_LIBGDA_4
	new_mgd->priv->parser = self->priv->parser;
#else
	new_mgd->priv->client = self->priv->client;
#endif
	new_mgd->priv->connection = self->priv->connection;
	new_mgd->priv->inherited = TRUE;

	new_mgd->priv->authtypes = self->priv->authtypes;

	/* Set pattern pointer. This is important (at least) for signals.
	 * If we need to disconnect from signal at some point (e.g. indexes creation)
	 * we should disconnect copy and original one. */
	new_mgd->priv->pattern = self;

	/* Connect connection copy to error callback */
	midgard_core_connection_connect_error_callback(new_mgd);

	/* Disconnect original connection from error callback.
	 * Copy will be used for this. Do not duplicate callbacks invokation */
	midgard_core_connection_disconnect_error_callback(self);

	return new_mgd;
}
