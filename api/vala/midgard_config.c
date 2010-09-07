/* midgard_config.c generated by valac 0.9.7.65-335d, the Vala compiler
 * generated from midgard_config.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include "midgard_config.h"
#include <stdlib.h>
#include <string.h>
#include <midgard_core.h>

#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

struct _MidgardConfigPrivate {
	char* _configname;
	char* _authtype;
	char* _dbname;
	char* _dbpass;
	char* _dbtype;
	char* _dbuser;
	char* _host;
	char* _logfilename;
	char* _loglevel;
	char* _midgardpassword;
	char* _midgardusername;
	guint _port;
	char* _sharedir;
	char* _vardir;
	char* _blobdir;
	char* _cachedir;
	char* _dbdir;
	gboolean _tablecreate;
	gboolean _tableupdate;
	gboolean _testunit;
};


static gpointer midgard_config_parent_class = NULL;

#define MIDGARD_CONFIG_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), MIDGARD_TYPE_CONFIG, MidgardConfigPrivate))
enum  {
	MIDGARD_CONFIG_DUMMY_PROPERTY,
	MIDGARD_CONFIG_AUTHTYPE,
	MIDGARD_CONFIG_DBNAME,
	MIDGARD_CONFIG_DBPASS,
	MIDGARD_CONFIG_DBTYPE,
	MIDGARD_CONFIG_DBUSER,
	MIDGARD_CONFIG_HOST,
	MIDGARD_CONFIG_LOGFILENAME,
	MIDGARD_CONFIG_LOGLEVEL,
	MIDGARD_CONFIG_MIDGARDPASSWORD,
	MIDGARD_CONFIG_MIDGARDUSERNAME,
	MIDGARD_CONFIG_PORT,
	MIDGARD_CONFIG_SHAREDIR,
	MIDGARD_CONFIG_VARDIR,
	MIDGARD_CONFIG_BLOBDIR,
	MIDGARD_CONFIG_CACHEDIR,
	MIDGARD_CONFIG_DBDIR,
	MIDGARD_CONFIG_TABLECREATE,
	MIDGARD_CONFIG_TABLEUPDATE,
	MIDGARD_CONFIG_TESTUNIT
};
static void midgard_config_finalize (GObject* obj);
static void midgard_config_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void midgard_config_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
void midgard_main (void);


#line 129 "midgard_config.vala"
gboolean midgard_config_read_file (MidgardConfig* self, const char* name, gboolean user, GError** error) {
#line 73 "midgard_config.c"
	gboolean result = FALSE;
	gboolean _tmp0_;
	GError * _inner_error_ = NULL;
#line 129 "midgard_config.vala"
	g_return_val_if_fail (self != NULL, FALSE);
#line 129 "midgard_config.vala"
	g_return_val_if_fail (name != NULL, FALSE);
#line 131 "midgard_config.vala"
	_tmp0_ = midgard_core_config_read_file (self, name, user, &_inner_error_);
#line 83 "midgard_config.c"
	if (_inner_error_ != NULL) {
		if ((_inner_error_->domain == G_KEY_FILE_ERROR) || (_inner_error_->domain == G_FILE_ERROR)) {
			g_propagate_error (error, _inner_error_);
			return FALSE;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return FALSE;
		}
	}
	result = _tmp0_;
#line 131 "midgard_config.vala"
	return result;
#line 97 "midgard_config.c"
}


#line 139 "midgard_config.vala"
MidgardConfig* midgard_config_copy (MidgardConfig* self, MidgardConfig* src) {
#line 103 "midgard_config.c"
	MidgardConfig* result = NULL;
	MidgardConfig* dest;
	char* _tmp0_;
	char* _tmp1_;
	char* _tmp2_;
	char* _tmp3_;
	char* _tmp4_;
	char* _tmp5_;
	char* _tmp6_;
	char* _tmp7_;
	char* _tmp8_;
	char* _tmp9_;
	char* _tmp10_;
	char* _tmp11_;
	char* _tmp12_;
	char* _tmp13_;
	char* _tmp14_;
	char* _tmp15_;
#line 139 "midgard_config.vala"
	g_return_val_if_fail (self != NULL, NULL);
#line 139 "midgard_config.vala"
	g_return_val_if_fail (src != NULL, NULL);
#line 141 "midgard_config.vala"
	dest = midgard_config_new ();
#line 142 "midgard_config.vala"
	dest->priv->_authtype = (_tmp0_ = g_strdup (src->priv->_authtype), _g_free0 (dest->priv->_authtype), _tmp0_);
#line 143 "midgard_config.vala"
	dest->priv->_dbname = (_tmp1_ = g_strdup (src->priv->_dbname), _g_free0 (dest->priv->_dbname), _tmp1_);
#line 144 "midgard_config.vala"
	dest->priv->_dbpass = (_tmp2_ = g_strdup (src->priv->_dbpass), _g_free0 (dest->priv->_dbpass), _tmp2_);
#line 145 "midgard_config.vala"
	dest->priv->_dbtype = (_tmp3_ = g_strdup (src->priv->_dbtype), _g_free0 (dest->priv->_dbtype), _tmp3_);
#line 146 "midgard_config.vala"
	dest->priv->_dbuser = (_tmp4_ = g_strdup (src->priv->_dbuser), _g_free0 (dest->priv->_dbuser), _tmp4_);
#line 147 "midgard_config.vala"
	dest->priv->_host = (_tmp5_ = g_strdup (src->priv->_host), _g_free0 (dest->priv->_host), _tmp5_);
#line 148 "midgard_config.vala"
	dest->priv->_logfilename = (_tmp6_ = g_strdup (src->priv->_logfilename), _g_free0 (dest->priv->_logfilename), _tmp6_);
#line 149 "midgard_config.vala"
	dest->priv->_loglevel = (_tmp7_ = g_strdup (src->priv->_loglevel), _g_free0 (dest->priv->_loglevel), _tmp7_);
#line 150 "midgard_config.vala"
	dest->priv->_midgardpassword = (_tmp8_ = g_strdup (src->priv->_midgardpassword), _g_free0 (dest->priv->_midgardpassword), _tmp8_);
#line 151 "midgard_config.vala"
	dest->priv->_midgardusername = (_tmp9_ = g_strdup (src->priv->_midgardusername), _g_free0 (dest->priv->_midgardusername), _tmp9_);
#line 152 "midgard_config.vala"
	dest->priv->_port = src->priv->_port;
#line 153 "midgard_config.vala"
	dest->priv->_sharedir = (_tmp10_ = g_strdup (src->priv->_sharedir), _g_free0 (dest->priv->_sharedir), _tmp10_);
#line 154 "midgard_config.vala"
	dest->priv->_vardir = (_tmp11_ = g_strdup (src->priv->_vardir), _g_free0 (dest->priv->_vardir), _tmp11_);
#line 155 "midgard_config.vala"
	dest->priv->_blobdir = (_tmp12_ = g_strdup (src->priv->_blobdir), _g_free0 (dest->priv->_blobdir), _tmp12_);
#line 156 "midgard_config.vala"
	dest->priv->_cachedir = (_tmp13_ = g_strdup (src->priv->_cachedir), _g_free0 (dest->priv->_cachedir), _tmp13_);
#line 157 "midgard_config.vala"
	dest->priv->_dbdir = (_tmp14_ = g_strdup (src->priv->_dbdir), _g_free0 (dest->priv->_dbdir), _tmp14_);
#line 158 "midgard_config.vala"
	dest->priv->_tablecreate = src->priv->_tablecreate;
#line 159 "midgard_config.vala"
	dest->priv->_tableupdate = src->priv->_tableupdate;
#line 160 "midgard_config.vala"
	dest->priv->_testunit = src->priv->_testunit;
#line 162 "midgard_config.vala"
	dest->priv->_configname = (_tmp15_ = g_strdup (src->priv->_configname), _g_free0 (dest->priv->_configname), _tmp15_);
#line 168 "midgard_config.c"
	result = dest;
#line 166 "midgard_config.vala"
	return result;
#line 172 "midgard_config.c"
}


#line 6 "midgard_config.vala"
MidgardConfig* midgard_config_construct (GType object_type) {
#line 178 "midgard_config.c"
	MidgardConfig * self;
#line 6 "midgard_config.vala"
	self = (MidgardConfig*) g_object_new (object_type, NULL);
#line 182 "midgard_config.c"
	return self;
}


#line 6 "midgard_config.vala"
MidgardConfig* midgard_config_new (void) {
#line 6 "midgard_config.vala"
	return midgard_config_construct (MIDGARD_TYPE_CONFIG);
#line 191 "midgard_config.c"
}


const char* midgard_config_get_authtype (MidgardConfig* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_authtype;
#line 34 "midgard_config.vala"
	return result;
#line 201 "midgard_config.c"
}


void midgard_config_set_authtype (MidgardConfig* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
#line 35 "midgard_config.vala"
	self->priv->_authtype = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_authtype), _tmp0_);
#line 210 "midgard_config.c"
	g_object_notify ((GObject *) self, "authtype");
}


const char* midgard_config_get_dbname (MidgardConfig* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_dbname;
#line 39 "midgard_config.vala"
	return result;
#line 221 "midgard_config.c"
}


void midgard_config_set_dbname (MidgardConfig* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
#line 40 "midgard_config.vala"
	self->priv->_dbname = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_dbname), _tmp0_);
#line 230 "midgard_config.c"
	g_object_notify ((GObject *) self, "dbname");
}


const char* midgard_config_get_dbpass (MidgardConfig* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_dbpass;
#line 44 "midgard_config.vala"
	return result;
#line 241 "midgard_config.c"
}


void midgard_config_set_dbpass (MidgardConfig* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
#line 45 "midgard_config.vala"
	self->priv->_dbpass = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_dbpass), _tmp0_);
#line 250 "midgard_config.c"
	g_object_notify ((GObject *) self, "dbpass");
}


const char* midgard_config_get_dbtype (MidgardConfig* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_dbtype;
#line 49 "midgard_config.vala"
	return result;
#line 261 "midgard_config.c"
}


void midgard_config_set_dbtype (MidgardConfig* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
#line 50 "midgard_config.vala"
	self->priv->_dbtype = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_dbtype), _tmp0_);
#line 270 "midgard_config.c"
	g_object_notify ((GObject *) self, "dbtype");
}


const char* midgard_config_get_dbuser (MidgardConfig* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_dbuser;
#line 54 "midgard_config.vala"
	return result;
#line 281 "midgard_config.c"
}


void midgard_config_set_dbuser (MidgardConfig* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
#line 55 "midgard_config.vala"
	self->priv->_dbuser = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_dbuser), _tmp0_);
#line 290 "midgard_config.c"
	g_object_notify ((GObject *) self, "dbuser");
}


const char* midgard_config_get_host (MidgardConfig* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_host;
#line 59 "midgard_config.vala"
	return result;
#line 301 "midgard_config.c"
}


void midgard_config_set_host (MidgardConfig* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
#line 60 "midgard_config.vala"
	self->priv->_host = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_host), _tmp0_);
#line 310 "midgard_config.c"
	g_object_notify ((GObject *) self, "host");
}


const char* midgard_config_get_logfilename (MidgardConfig* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_logfilename;
#line 64 "midgard_config.vala"
	return result;
#line 321 "midgard_config.c"
}


void midgard_config_set_logfilename (MidgardConfig* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
#line 65 "midgard_config.vala"
	self->priv->_logfilename = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_logfilename), _tmp0_);
#line 330 "midgard_config.c"
	g_object_notify ((GObject *) self, "logfilename");
}


const char* midgard_config_get_loglevel (MidgardConfig* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_loglevel;
#line 69 "midgard_config.vala"
	return result;
#line 341 "midgard_config.c"
}


void midgard_config_set_loglevel (MidgardConfig* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
#line 70 "midgard_config.vala"
	self->priv->_loglevel = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_loglevel), _tmp0_);
#line 350 "midgard_config.c"
	g_object_notify ((GObject *) self, "loglevel");
}


const char* midgard_config_get_midgardpassword (MidgardConfig* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_midgardpassword;
#line 74 "midgard_config.vala"
	return result;
#line 361 "midgard_config.c"
}


void midgard_config_set_midgardpassword (MidgardConfig* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
#line 75 "midgard_config.vala"
	self->priv->_midgardpassword = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_midgardpassword), _tmp0_);
#line 370 "midgard_config.c"
	g_object_notify ((GObject *) self, "midgardpassword");
}


const char* midgard_config_get_midgardusername (MidgardConfig* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_midgardusername;
#line 79 "midgard_config.vala"
	return result;
#line 381 "midgard_config.c"
}


void midgard_config_set_midgardusername (MidgardConfig* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
#line 80 "midgard_config.vala"
	self->priv->_midgardusername = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_midgardusername), _tmp0_);
#line 390 "midgard_config.c"
	g_object_notify ((GObject *) self, "midgardusername");
}


guint midgard_config_get_port (MidgardConfig* self) {
	guint result;
	g_return_val_if_fail (self != NULL, 0U);
	result = self->priv->_port;
#line 84 "midgard_config.vala"
	return result;
#line 401 "midgard_config.c"
}


void midgard_config_set_port (MidgardConfig* self, guint value) {
	g_return_if_fail (self != NULL);
#line 85 "midgard_config.vala"
	self->priv->_port = value;
#line 409 "midgard_config.c"
	g_object_notify ((GObject *) self, "port");
}


const char* midgard_config_get_sharedir (MidgardConfig* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_sharedir;
#line 89 "midgard_config.vala"
	return result;
#line 420 "midgard_config.c"
}


void midgard_config_set_sharedir (MidgardConfig* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
#line 90 "midgard_config.vala"
	self->priv->_sharedir = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_sharedir), _tmp0_);
#line 429 "midgard_config.c"
	g_object_notify ((GObject *) self, "sharedir");
}


const char* midgard_config_get_vardir (MidgardConfig* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_vardir;
#line 94 "midgard_config.vala"
	return result;
#line 440 "midgard_config.c"
}


void midgard_config_set_vardir (MidgardConfig* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
#line 95 "midgard_config.vala"
	self->priv->_vardir = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_vardir), _tmp0_);
#line 449 "midgard_config.c"
	g_object_notify ((GObject *) self, "vardir");
}


const char* midgard_config_get_blobdir (MidgardConfig* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_blobdir;
#line 99 "midgard_config.vala"
	return result;
#line 460 "midgard_config.c"
}


void midgard_config_set_blobdir (MidgardConfig* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
#line 100 "midgard_config.vala"
	self->priv->_blobdir = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_blobdir), _tmp0_);
#line 469 "midgard_config.c"
	g_object_notify ((GObject *) self, "blobdir");
}


const char* midgard_config_get_cachedir (MidgardConfig* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_cachedir;
#line 104 "midgard_config.vala"
	return result;
#line 480 "midgard_config.c"
}


void midgard_config_set_cachedir (MidgardConfig* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
#line 105 "midgard_config.vala"
	self->priv->_cachedir = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_cachedir), _tmp0_);
#line 489 "midgard_config.c"
	g_object_notify ((GObject *) self, "cachedir");
}


const char* midgard_config_get_dbdir (MidgardConfig* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_dbdir;
#line 109 "midgard_config.vala"
	return result;
#line 500 "midgard_config.c"
}


void midgard_config_set_dbdir (MidgardConfig* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
#line 110 "midgard_config.vala"
	self->priv->_dbdir = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_dbdir), _tmp0_);
#line 509 "midgard_config.c"
	g_object_notify ((GObject *) self, "dbdir");
}


gboolean midgard_config_get_tablecreate (MidgardConfig* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	result = self->priv->_tablecreate;
#line 114 "midgard_config.vala"
	return result;
#line 520 "midgard_config.c"
}


void midgard_config_set_tablecreate (MidgardConfig* self, gboolean value) {
	g_return_if_fail (self != NULL);
#line 115 "midgard_config.vala"
	self->priv->_tablecreate = value;
#line 528 "midgard_config.c"
	g_object_notify ((GObject *) self, "tablecreate");
}


gboolean midgard_config_get_tableupdate (MidgardConfig* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	result = self->priv->_tableupdate;
#line 119 "midgard_config.vala"
	return result;
#line 539 "midgard_config.c"
}


void midgard_config_set_tableupdate (MidgardConfig* self, gboolean value) {
	g_return_if_fail (self != NULL);
#line 120 "midgard_config.vala"
	self->priv->_tableupdate = value;
#line 547 "midgard_config.c"
	g_object_notify ((GObject *) self, "tableupdate");
}


gboolean midgard_config_get_testunit (MidgardConfig* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	result = self->priv->_testunit;
#line 124 "midgard_config.vala"
	return result;
#line 558 "midgard_config.c"
}


void midgard_config_set_testunit (MidgardConfig* self, gboolean value) {
	g_return_if_fail (self != NULL);
#line 125 "midgard_config.vala"
	self->priv->_testunit = value;
#line 566 "midgard_config.c"
	g_object_notify ((GObject *) self, "testunit");
}


static void midgard_config_class_init (MidgardConfigClass * klass) {
	midgard_config_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (MidgardConfigPrivate));
	G_OBJECT_CLASS (klass)->get_property = midgard_config_get_property;
	G_OBJECT_CLASS (klass)->set_property = midgard_config_set_property;
	G_OBJECT_CLASS (klass)->finalize = midgard_config_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_AUTHTYPE, g_param_spec_string ("authtype", "authtype", "authtype", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_DBNAME, g_param_spec_string ("dbname", "dbname", "dbname", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_DBPASS, g_param_spec_string ("dbpass", "dbpass", "dbpass", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_DBTYPE, g_param_spec_string ("dbtype", "dbtype", "dbtype", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_DBUSER, g_param_spec_string ("dbuser", "dbuser", "dbuser", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_HOST, g_param_spec_string ("host", "host", "host", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_LOGFILENAME, g_param_spec_string ("logfilename", "logfilename", "logfilename", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_LOGLEVEL, g_param_spec_string ("loglevel", "loglevel", "loglevel", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_MIDGARDPASSWORD, g_param_spec_string ("midgardpassword", "midgardpassword", "midgardpassword", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_MIDGARDUSERNAME, g_param_spec_string ("midgardusername", "midgardusername", "midgardusername", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_PORT, g_param_spec_uint ("port", "port", "port", 0, G_MAXUINT, 0U, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_SHAREDIR, g_param_spec_string ("sharedir", "sharedir", "sharedir", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_VARDIR, g_param_spec_string ("vardir", "vardir", "vardir", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_BLOBDIR, g_param_spec_string ("blobdir", "blobdir", "blobdir", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_CACHEDIR, g_param_spec_string ("cachedir", "cachedir", "cachedir", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_DBDIR, g_param_spec_string ("dbdir", "dbdir", "dbdir", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_TABLECREATE, g_param_spec_boolean ("tablecreate", "tablecreate", "tablecreate", FALSE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_TABLEUPDATE, g_param_spec_boolean ("tableupdate", "tableupdate", "tableupdate", FALSE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_CONFIG_TESTUNIT, g_param_spec_boolean ("testunit", "testunit", "testunit", FALSE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void midgard_config_instance_init (MidgardConfig * self) {
	self->priv = MIDGARD_CONFIG_GET_PRIVATE (self);
	self->priv->_configname = g_strdup ("");
	self->priv->_authtype = g_strdup ("");
	self->priv->_dbname = g_strdup ("midgard");
	self->priv->_dbpass = g_strdup ("midgard");
	self->priv->_dbtype = g_strdup ("SQLite");
	self->priv->_dbuser = g_strdup ("midgard");
	self->priv->_host = g_strdup ("localhost");
	self->priv->_logfilename = g_strdup ("");
	self->priv->_loglevel = g_strdup ("warn");
	self->priv->_midgardpassword = g_strdup ("");
	self->priv->_midgardusername = g_strdup ("");
	self->priv->_port = (guint) 0;
	self->priv->_sharedir = g_strdup ("");
	self->priv->_vardir = g_strdup ("");
	self->priv->_blobdir = g_strdup ("");
	self->priv->_cachedir = g_strdup ("");
	self->priv->_dbdir = g_strdup ("");
	self->priv->_tablecreate = FALSE;
	self->priv->_tableupdate = FALSE;
	self->priv->_testunit = FALSE;
}


static void midgard_config_finalize (GObject* obj) {
	MidgardConfig * self;
	self = MIDGARD_CONFIG (obj);
	_g_free0 (self->priv->_configname);
	_g_free0 (self->priv->_authtype);
	_g_free0 (self->priv->_dbname);
	_g_free0 (self->priv->_dbpass);
	_g_free0 (self->priv->_dbtype);
	_g_free0 (self->priv->_dbuser);
	_g_free0 (self->priv->_host);
	_g_free0 (self->priv->_logfilename);
	_g_free0 (self->priv->_loglevel);
	_g_free0 (self->priv->_midgardpassword);
	_g_free0 (self->priv->_midgardusername);
	_g_free0 (self->priv->_sharedir);
	_g_free0 (self->priv->_vardir);
	_g_free0 (self->priv->_blobdir);
	_g_free0 (self->priv->_cachedir);
	_g_free0 (self->priv->_dbdir);
	G_OBJECT_CLASS (midgard_config_parent_class)->finalize (obj);
}


GType midgard_config_get_type (void) {
	static volatile gsize midgard_config_type_id__volatile = 0;
	if (g_once_init_enter (&midgard_config_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (MidgardConfigClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) midgard_config_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (MidgardConfig), 0, (GInstanceInitFunc) midgard_config_instance_init, NULL };
		GType midgard_config_type_id;
		midgard_config_type_id = g_type_register_static (G_TYPE_OBJECT, "MidgardConfig", &g_define_type_info, 0);
		g_once_init_leave (&midgard_config_type_id__volatile, midgard_config_type_id);
	}
	return midgard_config_type_id__volatile;
}


static void midgard_config_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	MidgardConfig * self;
	self = MIDGARD_CONFIG (object);
	switch (property_id) {
		case MIDGARD_CONFIG_AUTHTYPE:
		g_value_set_string (value, midgard_config_get_authtype (self));
		break;
		case MIDGARD_CONFIG_DBNAME:
		g_value_set_string (value, midgard_config_get_dbname (self));
		break;
		case MIDGARD_CONFIG_DBPASS:
		g_value_set_string (value, midgard_config_get_dbpass (self));
		break;
		case MIDGARD_CONFIG_DBTYPE:
		g_value_set_string (value, midgard_config_get_dbtype (self));
		break;
		case MIDGARD_CONFIG_DBUSER:
		g_value_set_string (value, midgard_config_get_dbuser (self));
		break;
		case MIDGARD_CONFIG_HOST:
		g_value_set_string (value, midgard_config_get_host (self));
		break;
		case MIDGARD_CONFIG_LOGFILENAME:
		g_value_set_string (value, midgard_config_get_logfilename (self));
		break;
		case MIDGARD_CONFIG_LOGLEVEL:
		g_value_set_string (value, midgard_config_get_loglevel (self));
		break;
		case MIDGARD_CONFIG_MIDGARDPASSWORD:
		g_value_set_string (value, midgard_config_get_midgardpassword (self));
		break;
		case MIDGARD_CONFIG_MIDGARDUSERNAME:
		g_value_set_string (value, midgard_config_get_midgardusername (self));
		break;
		case MIDGARD_CONFIG_PORT:
		g_value_set_uint (value, midgard_config_get_port (self));
		break;
		case MIDGARD_CONFIG_SHAREDIR:
		g_value_set_string (value, midgard_config_get_sharedir (self));
		break;
		case MIDGARD_CONFIG_VARDIR:
		g_value_set_string (value, midgard_config_get_vardir (self));
		break;
		case MIDGARD_CONFIG_BLOBDIR:
		g_value_set_string (value, midgard_config_get_blobdir (self));
		break;
		case MIDGARD_CONFIG_CACHEDIR:
		g_value_set_string (value, midgard_config_get_cachedir (self));
		break;
		case MIDGARD_CONFIG_DBDIR:
		g_value_set_string (value, midgard_config_get_dbdir (self));
		break;
		case MIDGARD_CONFIG_TABLECREATE:
		g_value_set_boolean (value, midgard_config_get_tablecreate (self));
		break;
		case MIDGARD_CONFIG_TABLEUPDATE:
		g_value_set_boolean (value, midgard_config_get_tableupdate (self));
		break;
		case MIDGARD_CONFIG_TESTUNIT:
		g_value_set_boolean (value, midgard_config_get_testunit (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void midgard_config_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	MidgardConfig * self;
	self = MIDGARD_CONFIG (object);
	switch (property_id) {
		case MIDGARD_CONFIG_AUTHTYPE:
		midgard_config_set_authtype (self, g_value_get_string (value));
		break;
		case MIDGARD_CONFIG_DBNAME:
		midgard_config_set_dbname (self, g_value_get_string (value));
		break;
		case MIDGARD_CONFIG_DBPASS:
		midgard_config_set_dbpass (self, g_value_get_string (value));
		break;
		case MIDGARD_CONFIG_DBTYPE:
		midgard_config_set_dbtype (self, g_value_get_string (value));
		break;
		case MIDGARD_CONFIG_DBUSER:
		midgard_config_set_dbuser (self, g_value_get_string (value));
		break;
		case MIDGARD_CONFIG_HOST:
		midgard_config_set_host (self, g_value_get_string (value));
		break;
		case MIDGARD_CONFIG_LOGFILENAME:
		midgard_config_set_logfilename (self, g_value_get_string (value));
		break;
		case MIDGARD_CONFIG_LOGLEVEL:
		midgard_config_set_loglevel (self, g_value_get_string (value));
		break;
		case MIDGARD_CONFIG_MIDGARDPASSWORD:
		midgard_config_set_midgardpassword (self, g_value_get_string (value));
		break;
		case MIDGARD_CONFIG_MIDGARDUSERNAME:
		midgard_config_set_midgardusername (self, g_value_get_string (value));
		break;
		case MIDGARD_CONFIG_PORT:
		midgard_config_set_port (self, g_value_get_uint (value));
		break;
		case MIDGARD_CONFIG_SHAREDIR:
		midgard_config_set_sharedir (self, g_value_get_string (value));
		break;
		case MIDGARD_CONFIG_VARDIR:
		midgard_config_set_vardir (self, g_value_get_string (value));
		break;
		case MIDGARD_CONFIG_BLOBDIR:
		midgard_config_set_blobdir (self, g_value_get_string (value));
		break;
		case MIDGARD_CONFIG_CACHEDIR:
		midgard_config_set_cachedir (self, g_value_get_string (value));
		break;
		case MIDGARD_CONFIG_DBDIR:
		midgard_config_set_dbdir (self, g_value_get_string (value));
		break;
		case MIDGARD_CONFIG_TABLECREATE:
		midgard_config_set_tablecreate (self, g_value_get_boolean (value));
		break;
		case MIDGARD_CONFIG_TABLEUPDATE:
		midgard_config_set_tableupdate (self, g_value_get_boolean (value));
		break;
		case MIDGARD_CONFIG_TESTUNIT:
		midgard_config_set_testunit (self, g_value_get_boolean (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


#line 170 "midgard_config.vala"
void midgard_main (void) {
#line 797 "midgard_config.c"
}


#line 170 "midgard_config.vala"
int main (int argc, char ** argv) {
#line 170 "midgard_config.vala"
	g_type_init ();
#line 170 "midgard_config.vala"
	midgard_main ();
#line 170 "midgard_config.vala"
	return 0;
#line 809 "midgard_config.c"
}



