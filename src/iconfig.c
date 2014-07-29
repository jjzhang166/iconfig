
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <json-glib/json-glib.h>
#include "iconfig.h"
#include "database/database.h"
#include "ajax/ajax.h"
#include "action-handler/generic_action_handler.h"

typedef struct _IpcamIConfigPrivate
{
    IpcamDatabase *database;
    IpcamAjax *ajax;
} IpcamIConfigPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(IpcamIConfig, ipcam_iconfig, IPCAM_BASE_APP_TYPE);

static void ipcam_iconfig_before_start(IpcamBaseService *base_service);
static void ipcam_iconfig_in_loop(IpcamBaseService *base_service);

static void ipcam_iconfig_finalize(GObject *object)
{
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(IPCAM_ICONFIG(object));
    g_clear_object(&priv->database);
    g_clear_object(&priv->ajax);
    G_OBJECT_CLASS(ipcam_iconfig_parent_class)->finalize(object);
}
static void ipcam_iconfig_init(IpcamIConfig *self)
{
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(self);
    priv->database = g_object_new(IPCAM_DATABASE_TYPE, NULL);
}
static void ipcam_iconfig_class_init(IpcamIConfigClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->finalize = &ipcam_iconfig_finalize;
    
    IpcamBaseServiceClass *base_service_class = IPCAM_BASE_SERVICE_CLASS(klass);
    base_service_class->before = ipcam_iconfig_before_start;
    base_service_class->in_loop = ipcam_iconfig_in_loop;
}

static void ipcam_iconfig_before_start(IpcamBaseService *base_service)
{
    IpcamIConfig *iconfig = IPCAM_ICONFIG(base_service);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);
    const gchar *ajax_addr = ipcam_base_app_get_config(IPCAM_BASE_APP(iconfig), "ajax:address");
    const gchar *port = ipcam_base_app_get_config(IPCAM_BASE_APP(iconfig), "ajax:port");
    if (ajax_addr != NULL && port != NULL)
    {
        priv->ajax = g_object_new(IPCAM_AJAX_TYPE,
                                  "app", iconfig,
                                  "address", ajax_addr,
                                  "port", strtol(port, NULL, 10),
                                  NULL);
    }

    /* Message Handler */
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "get_base_info", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "set_base_info", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "get_osd", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "set_osd", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "get_video", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "set_video", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "get_scene", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "set_scene", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "get_network", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "set_network", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "get_datetime", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "set_datetime", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "get_users", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "set_users", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "add_users", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), "del_users", IPCAM_GENERIC_ACTION_HANDLER_TYPE);
}

static void ipcam_iconfig_in_loop(IpcamBaseService *base_service)
{
}

gchar *ipcam_iconfig_get_base_info(IpcamIConfig *iconfig, const gchar *name)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), NULL);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_get_baseinfo(priv->database, (gchar *)name);
}

void ipcam_iconfig_set_base_info(IpcamIConfig *iconfig, const char *name, const char *value)
{
    g_return_if_fail(IPCAM_IS_ICONFIG(iconfig));
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    ipcam_database_set_baseinfo(priv->database, (gchar *)name, (gchar *)value);
}

gboolean ipcam_iconfig_get_osd(IpcamIConfig *iconfig,
                               const gchar *name,
                               gboolean *isshow,
                               guint *size,
                               guint *x,
                               guint *y,
                               guint *color)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), FALSE);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_get_osd(priv->database, (gchar *)name, isshow, size, x, y, color);
}

void ipcam_iconfig_set_osd(IpcamIConfig *iconfig,
                            const gchar *name,
                            gboolean isshow,
                            guint size,
                            guint x,
                            guint y,
                            guint color)
{
    g_return_if_fail(IPCAM_IS_ICONFIG(iconfig));
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    ipcam_database_set_osd(priv->database, (gchar *)name, isshow, size, x, y, color);
}

gint ipcam_iconfig_get_video_int(IpcamIConfig *iconfig,
                                 const gchar *profile, const gchar *name)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), -1);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);
    gchar *key = NULL;

    asprintf(&key, "%s:%s", profile, name);
    gint ret = ipcam_database_get_video_int(priv->database, key);
    free(key);

	return ret;
}

void ipcam_iconfig_set_video_int(IpcamIConfig *iconfig,
                                 const gchar *profile, const gchar *name,
                                 gint value)
{
    g_return_if_fail(IPCAM_IS_ICONFIG(iconfig));
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);
    gchar *key = NULL;

    asprintf(&key, "%s:%s", profile, name);
	ipcam_database_set_video_int(priv->database, key, value);
    free(key);
}

gchar *ipcam_iconfig_get_video_string(IpcamIConfig *iconfig,
                                      const gchar *profile, const gchar *name)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), -1);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);
    gchar *key = NULL;

    asprintf(&key, "%s:%s", profile, name);
    gchar *ret = ipcam_database_get_video_string(priv->database, key);
    free(key);

	return ret;
}

void ipcam_iconfig_set_video_string(IpcamIConfig *iconfig,
                                    const gchar *profile, const gchar *name,
                                    const gchar *value)
{
    g_return_if_fail(IPCAM_IS_ICONFIG(iconfig));
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);
    gchar *key = NULL;

    asprintf(&key, "%s:%s", profile, name);
	ipcam_database_set_video_string(priv->database, key, value);
    free(key);
}

gint ipcam_iconfig_get_scene(IpcamIConfig *iconfig, const gchar *name)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), -1);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_get_scene(priv->database, (gchar *)name);
}

void ipcam_iconfig_set_scene(IpcamIConfig *iconfig, const gchar *name, gint value)
{
    g_return_if_fail(IPCAM_IS_ICONFIG(iconfig));
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

	ipcam_database_set_scene(priv->database, (gchar *)name, value);
}

gint ipcam_iconfig_get_network(IpcamIConfig *iconfig, const gchar *name)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), -1);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_get_network(priv->database, name);
}

void ipcam_iconfig_set_network(IpcamIConfig *iconfig, const gchar *name, guint value)
{
    g_return_if_fail(IPCAM_IS_ICONFIG(iconfig));
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    ipcam_database_set_network(priv->database, name, value);
}

gchar *ipcam_iconfig_get_network_static(IpcamIConfig *iconfig, const gchar *name)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), NULL);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_get_network_static(priv->database, name);
}

void ipcam_iconfig_set_network_static(IpcamIConfig *iconfig, const gchar *name, gchar *value)
{
    g_return_if_fail(IPCAM_IS_ICONFIG(iconfig));
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    ipcam_database_set_network_static(priv->database, name, value);
}

gchar *ipcam_iconfig_get_network_pppoe(IpcamIConfig *iconfig, const gchar *name)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), NULL);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_get_network_pppoe(priv->database, name);
}

void ipcam_iconfig_set_network_pppoe(IpcamIConfig *iconfig, const gchar *name, gchar *value)
{
    g_return_if_fail(IPCAM_IS_ICONFIG(iconfig));
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    ipcam_database_set_network_pppoe(priv->database, name, value);
}

gint ipcam_iconfig_get_network_port(IpcamIConfig *iconfig, const gchar *name)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), -1);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_get_network_port(priv->database, name);
}

void ipcam_iconfig_set_network_port(IpcamIConfig *iconfig, const gchar *name, guint value)
{
    g_return_if_fail(IPCAM_IS_ICONFIG(iconfig));
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    ipcam_database_set_network_port(priv->database, name, value);
}

void ipcam_iconfig_set_datetime(IpcamIConfig *iconfig, const gchar *name, guint int_value, gchar *str_value)
{
    g_return_if_fail(IPCAM_IS_ICONFIG(iconfig));
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    ipcam_database_set_datetime (priv->database, name, int_value, str_value);
}

void ipcam_iconfig_get_datetime(IpcamIConfig *iconfig, const gchar *name, guint *int_value, gchar **str_value)
{
    g_return_if_fail(IPCAM_IS_ICONFIG(iconfig));
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    ipcam_database_get_datetime (priv->database, name, int_value, str_value);
}

GList *ipcam_iconfig_get_users(IpcamIConfig *iconfig)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), NULL);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_get_users (priv->database);
}

void ipcam_iconfig_set_user_password(IpcamIConfig *iconfig, const gchar *username, gchar *password)
{
    g_return_if_fail(IPCAM_IS_ICONFIG(iconfig));
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    ipcam_database_set_user_password (priv->database, username, password);
}

gchar *ipcam_iconfig_get_user_password(IpcamIConfig *iconfig, const gchar *username)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), NULL);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_get_user_password (priv->database, username);
}

void ipcam_iconfig_set_user_privilege(IpcamIConfig *iconfig, const gchar *username, guint privilege)
{
    g_return_if_fail(IPCAM_IS_ICONFIG(iconfig));
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

	ipcam_database_set_user_privilege (priv->database, username, privilege);
}

guint ipcam_iconfig_get_user_privilege(IpcamIConfig *iconfig, const gchar *username)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), 0);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_get_user_privilege (priv->database, username);
}

void ipcam_iconfig_del_user(IpcamIConfig *iconfig, const gchar *username)
{
    g_return_if_fail(IPCAM_IS_ICONFIG(iconfig));
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_del_user (priv->database, username);
}
