/* midgard_key_config_context.c generated by valac, the Vala compiler
 * generated from midgard_key_config_context.vala, do not modify */

/* 
 * Copyright (C) 2009 Piotr Pokora <piotrek.pokora@gmail.com>
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

#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>


#define MIDGARD_TYPE_KEY_CONFIG_CONTEXT (midgard_key_config_context_get_type ())
#define MIDGARD_KEY_CONFIG_CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MIDGARD_TYPE_KEY_CONFIG_CONTEXT, MidgardKeyConfigContext))
#define MIDGARD_KEY_CONFIG_CONTEXT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), MIDGARD_TYPE_KEY_CONFIG_CONTEXT, MidgardKeyConfigContextClass))
#define MIDGARD_IS_KEY_CONFIG_CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MIDGARD_TYPE_KEY_CONFIG_CONTEXT))
#define MIDGARD_IS_KEY_CONFIG_CONTEXT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MIDGARD_TYPE_KEY_CONFIG_CONTEXT))
#define MIDGARD_KEY_CONFIG_CONTEXT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), MIDGARD_TYPE_KEY_CONFIG_CONTEXT, MidgardKeyConfigContextClass))

typedef struct _MidgardKeyConfigContext MidgardKeyConfigContext;
typedef struct _MidgardKeyConfigContextClass MidgardKeyConfigContextClass;
typedef struct _MidgardKeyConfigContextPrivate MidgardKeyConfigContextPrivate;
#define _g_free0(var) (var = (g_free (var), NULL))

typedef enum  {
	KEY_CONFIG_CONTEXT_ERROR_PATH_IS_NOT_ABSOLUTE
} KeyConfigContextError;
#define KEY_CONFIG_CONTEXT_ERROR key_config_context_error_quark ()
struct _MidgardKeyConfigContext {
	GObject parent_instance;
	MidgardKeyConfigContextPrivate * priv;
};

struct _MidgardKeyConfigContextClass {
	GObjectClass parent_class;
	char** (*list_key_config) (MidgardKeyConfigContext* self, int* result_length1);
};

struct _MidgardKeyConfigContextPrivate {
	char* _context_path;
};


static gpointer midgard_key_config_context_parent_class = NULL;

GQuark key_config_context_error_quark (void);
GType midgard_key_config_context_get_type (void);
#define MIDGARD_KEY_CONFIG_CONTEXT_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), MIDGARD_TYPE_KEY_CONFIG_CONTEXT, MidgardKeyConfigContextPrivate))
enum  {
	MIDGARD_KEY_CONFIG_CONTEXT_DUMMY_PROPERTY,
	MIDGARD_KEY_CONFIG_CONTEXT_CONTEXT_PATH
};
static void midgard_key_config_context_set_context_path (MidgardKeyConfigContext* self, const char* value);
MidgardKeyConfigContext* midgard_key_config_context_construct (GType object_type, const char* context_path);
char** midgard_key_config_context_list_key_config (MidgardKeyConfigContext* self, int* result_length1);
static char** midgard_key_config_context_real_list_key_config (MidgardKeyConfigContext* self, int* result_length1);
const char* midgard_key_config_context_get_context_path (MidgardKeyConfigContext* self);
static void midgard_key_config_context_finalize (GObject* obj);
static void midgard_key_config_context_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void midgard_key_config_context_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);



GQuark key_config_context_error_quark (void) {
	return g_quark_from_static_string ("key_config_context_error-quark");
}


MidgardKeyConfigContext* midgard_key_config_context_construct (GType object_type, const char* context_path) {
	MidgardKeyConfigContext * self;
	self = (MidgardKeyConfigContext*) g_object_new (object_type, NULL);
	midgard_key_config_context_set_context_path (self, context_path);
	return self;
}


static char** midgard_key_config_context_real_list_key_config (MidgardKeyConfigContext* self, int* result_length1) {
	char** result;
	gpointer _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	result = (_tmp0_ = NULL, *result_length1 = 0, _tmp0_);
	return result;
}


char** midgard_key_config_context_list_key_config (MidgardKeyConfigContext* self, int* result_length1) {
	return MIDGARD_KEY_CONFIG_CONTEXT_GET_CLASS (self)->list_key_config (self, result_length1);
}


const char* midgard_key_config_context_get_context_path (MidgardKeyConfigContext* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_context_path;
	return result;
}


static void midgard_key_config_context_set_context_path (MidgardKeyConfigContext* self, const char* value) {
	char* _tmp0_;
	g_return_if_fail (self != NULL);
	self->priv->_context_path = (_tmp0_ = g_strdup (value), _g_free0 (self->priv->_context_path), _tmp0_);
	g_object_notify ((GObject *) self, "context-path");
}


static void midgard_key_config_context_class_init (MidgardKeyConfigContextClass * klass) {
	midgard_key_config_context_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (MidgardKeyConfigContextPrivate));
	MIDGARD_KEY_CONFIG_CONTEXT_CLASS (klass)->list_key_config = midgard_key_config_context_real_list_key_config;
	G_OBJECT_CLASS (klass)->get_property = midgard_key_config_context_get_property;
	G_OBJECT_CLASS (klass)->set_property = midgard_key_config_context_set_property;
	G_OBJECT_CLASS (klass)->finalize = midgard_key_config_context_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), MIDGARD_KEY_CONFIG_CONTEXT_CONTEXT_PATH, g_param_spec_string ("context-path", "Context path", "Information about context path.", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
}


static void midgard_key_config_context_instance_init (MidgardKeyConfigContext * self) {
	self->priv = MIDGARD_KEY_CONFIG_CONTEXT_GET_PRIVATE (self);
	self->priv->_context_path = NULL;
}


static void midgard_key_config_context_finalize (GObject* obj) {
	MidgardKeyConfigContext * self;
	self = MIDGARD_KEY_CONFIG_CONTEXT (obj);
	_g_free0 (self->priv->_context_path);
	G_OBJECT_CLASS (midgard_key_config_context_parent_class)->finalize (obj);
}


GType midgard_key_config_context_get_type (void) {
	static volatile gsize midgard_key_config_context_type_id__volatile = 0;
	if (g_once_init_enter (&midgard_key_config_context_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (MidgardKeyConfigContextClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) midgard_key_config_context_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (MidgardKeyConfigContext), 0, (GInstanceInitFunc) midgard_key_config_context_instance_init, NULL };
		GType midgard_key_config_context_type_id;
		midgard_key_config_context_type_id = g_type_register_static (G_TYPE_OBJECT, "MidgardKeyConfigContext", &g_define_type_info, G_TYPE_FLAG_ABSTRACT);
		g_once_init_leave (&midgard_key_config_context_type_id__volatile, midgard_key_config_context_type_id);
	}
	return midgard_key_config_context_type_id__volatile;
}


static void midgard_key_config_context_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	MidgardKeyConfigContext * self;
	self = MIDGARD_KEY_CONFIG_CONTEXT (object);
	switch (property_id) {
		case MIDGARD_KEY_CONFIG_CONTEXT_CONTEXT_PATH:
		g_value_set_string (value, midgard_key_config_context_get_context_path (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void midgard_key_config_context_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	MidgardKeyConfigContext * self;
	self = MIDGARD_KEY_CONFIG_CONTEXT (object);
	switch (property_id) {
		case MIDGARD_KEY_CONFIG_CONTEXT_CONTEXT_PATH:
		midgard_key_config_context_set_context_path (self, g_value_get_string (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}




