/* 
 * Copyright (C) 2007, 2009 Piotr Pokora <piotrek.pokora@gmail.com>
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

#ifndef MIDGARD_USER_H
#define MIDGARD_USER_H

#include <glib-object.h>
#include "midgard_dbobject.h"
#include "midgard_object.h"

G_BEGIN_DECLS

/* convention macros */
#define MIDGARD_TYPE_USER (midgard_user_get_type())
#define MIDGARD_USER(object)  \
	        (G_TYPE_CHECK_INSTANCE_CAST ((object),MIDGARD_TYPE_USER, MidgardUser))
#define MIDGARD_USER_CLASS(klass)  \
	        (G_TYPE_CHECK_CLASS_CAST ((klass), MIDGARD_TYPE_USER, MidgardUserClass))
#define MIDGARD_IS_USER(object)   \
	        (G_TYPE_CHECK_INSTANCE_TYPE ((object), MIDGARD_TYPE_USER))
#define MIDGARD_IS_USER_CLASS(klass) \
	        (G_TYPE_CHECK_CLASS_TYPE ((klass), MIDGARD_TYPE_USER))
#define MIDGARD_USER_GET_CLASS(obj) \
	        (G_TYPE_INSTANCE_GET_CLASS ((obj), MIDGARD_TYPE_USER, MidgardUserClass))

typedef struct _MidgardUserClass MidgardUserClass;
typedef struct _MidgardUserPrivate MidgardUserPrivate; 

struct _MidgardUserClass{
	MidgardDBObjectClass parent;
	
	/* methods */
	const MidgardConnection *(*get_connection) (MidgardDBObject *);
	
	/* API methods */
	MidgardObject *(*get_person)		(MidgardUser *self);
	gboolean        (*log_in)              	(MidgardUser *self, GError **error);
	gboolean        (*log_out)             	(MidgardUser *self, GError **error);
	MidgardUser     *(*get)               	(MidgardConnection *mgd, guint n_params, const GParameter *parameters, GError **error);
	MidgardUser     **(*query) 		(MidgardConnection *mgd, guint n_params, const GParameter *parameters, GError **error);
	gboolean        (*create)           	(MidgardUser *self, GError **error);
	gboolean        (*update)             	(MidgardUser *self, GError **error);
	gboolean 	(*delete_record)	(MidgardUser *self, GError **error);
	gboolean 	(*is_user)		(MidgardUser *self);
	gboolean 	(*is_admin)		(MidgardUser *self);
};

struct _MidgardUser{
	MidgardDBObject parent;

	/* < private > */
	MidgardUserPrivate *priv;
	/* MidgardMetadata *metadata; */
};

#define MIDGARD_USER_TYPE_NONE 0
#define MIDGARD_USER_TYPE_USER 1
#define MIDGARD_USER_TYPE_ADMIN 2

GType midgard_user_get_type(void);

MidgardUser 		*midgard_user_new		(MidgardConnection *mgd, guint n_params, const GParameter *parameters);
MidgardUser 		*midgard_user_get		(MidgardConnection *mgd, guint n_params, const GParameter *parameters, GError **error);
MidgardUser 		*midgard_user_quick_login	(MidgardConnection *mgd, const gchar *login, const gchar *password);
MidgardUser 		**midgard_user_query		(MidgardConnection *mgd, guint n_params, const GParameter *parameters, GError **error);
gboolean		midgard_user_create		(MidgardUser *self, GError **error);
gboolean 		midgard_user_update		(MidgardUser *self, GError **error);
gboolean 		midgard_user_delete		(MidgardUser *self, GError **error);
gboolean 		midgard_user_is_user		(MidgardUser *self);
gboolean 		midgard_user_is_admin		(MidgardUser *self);
MidgardObject		*midgard_user_get_person	(MidgardUser *self);
gboolean 		midgard_user_set_person		(MidgardUser *self, MidgardObject *person);
gboolean		midgard_user_log_in 		(MidgardUser *self, GError **error);
gboolean 		midgard_user_log_out 		(MidgardUser *self, GError **error);

/* Deprecated */
gboolean 	midgard_user_set_active	(MidgardUser *user, gboolean flag, GError **error);


G_END_DECLS

#endif /* MIDGARD_USER_H */
