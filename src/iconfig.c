
#include <stdio.h>
#include <stdlib.h>
#include <json-glib/json-glib.h>
#include "iconfig.h"
#include "database/database.h"
#include "action-handler/generic_action_handler.h"
#include "database/base_info.h"
#include "common.h"

typedef struct _IpcamIConfigPrivate
{
    IpcamDatabase *database;
    gchar *model;
} IpcamIConfigPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(IpcamIConfig, ipcam_iconfig, IPCAM_BASE_APP_TYPE);

static void ipcam_iconfig_before_start(IpcamBaseService *base_service);
static void ipcam_iconfig_in_loop(IpcamBaseService *base_service);

static void ipcam_iconfig_dispose(GObject *object)
{
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(IPCAM_ICONFIG(object));
    if (priv->database) {
        g_object_run_dispose(G_OBJECT(priv->database));
        g_clear_object(&priv->database);
        g_free(priv->model);
    }
    G_OBJECT_CLASS(ipcam_iconfig_parent_class)->dispose(object);
}

static void ipcam_iconfig_finalize(GObject *object)
{
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
    object_class->dispose = &ipcam_iconfig_dispose;
    object_class->finalize = &ipcam_iconfig_finalize;
    
    IpcamBaseServiceClass *base_service_class = IPCAM_BASE_SERVICE_CLASS(klass);
    base_service_class->before = ipcam_iconfig_before_start;
    base_service_class->in_loop = ipcam_iconfig_in_loop;
}

static void ipcam_iconfig_before_start(IpcamBaseService *base_service)
{
    IpcamIConfig *iconfig = IPCAM_ICONFIG(base_service);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    /* Message Handler */
    const gchar *name[] =
    {
        "get_misc",
        "set_misc",    
        "get_base_info",
        "set_base_info",
        "get_users",
        "set_users",
        "add_users",
        "del_users",
        "get_datetime",
        "set_datetime",
        "get_video",
        "set_video",
        "get_image",
        "set_image",
        "get_privacy_block",
        "set_privacy_block",
        "get_day_night_mode",
        "set_day_night_mode",
        "get_osd",
        "set_osd",
        "get_szyc",
        "set_szyc",
        "get_network",
        "set_network",
        "get_event_input",
        "set_event_input",
        "get_event_output",
        "set_event_output",
        "get_event_motion",
        "set_event_motion",
        "get_event_cover",
        "set_event_cover",
        "get_event_proc",
        "set_event_proc"
    };

    gint i = 0;
    for (i = 0; i < ARRAY_SIZE(name); i++)
    {
        ipcam_base_app_register_request_handler(IPCAM_BASE_APP(iconfig), name[i], IPCAM_GENERIC_ACTION_HANDLER_TYPE);
    }
    GVariant *value = NULL;
    value = ipcam_iconfig_read(iconfig, IPCAM_BASE_INFO_TYPE, "model", "value");
    if (value)
    {
        priv->model = g_strdup(g_variant_get_string(value, NULL));
        g_variant_unref(value);
    }
}

static void ipcam_iconfig_in_loop(IpcamBaseService *base_service)
{
}

gchar *ipcam_iconfig_get_model(IpcamIConfig *iconfig)
{
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return priv->model;
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

void ipcam_iconfig_set_user_role(IpcamIConfig *iconfig, const gchar *username, const gchar *role)
{
    g_return_if_fail(IPCAM_IS_ICONFIG(iconfig));
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

	ipcam_database_set_user_role (priv->database, username, role);
}

gchar *ipcam_iconfig_get_user_role(IpcamIConfig *iconfig, const gchar *username)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), NULL);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_get_user_role (priv->database, username);
}

gboolean ipcam_iconfig_add_user(IpcamIConfig *iconfig, const gchar *username,
                                const gchar *password, const gchar *role)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), FALSE);
    g_return_val_if_fail(username, FALSE);
    g_return_val_if_fail(password, FALSE);
    g_return_val_if_fail(role, FALSE);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_add_user(priv->database, username, password, role);
}

gboolean ipcam_iconfig_del_user(IpcamIConfig *iconfig, const gchar *username)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), FALSE);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_del_user (priv->database, username);
}

GVariant *ipcam_iconfig_read(IpcamIConfig *iconfig, GType table, const gchar *name, const gchar *sub_name)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), NULL);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_read(priv->database, table, name, sub_name);
}

gboolean ipcam_iconfig_update(IpcamIConfig *iconfig, GType table, const gchar *name, const gchar *sub_name,  GVariant *value)
{
    g_return_val_if_fail(IPCAM_IS_ICONFIG(iconfig), FALSE);
    IpcamIConfigPrivate *priv = ipcam_iconfig_get_instance_private(iconfig);

    return ipcam_database_update(priv->database, table, name, sub_name, value);
}
