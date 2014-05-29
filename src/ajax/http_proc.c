#include <stdio.h>
#include <string.h>
#include "http_proc.h"
#include "http_request_handler.h"
#include "http_base_info_handler.h"
#include "iconfig.h"

enum
{
    PROP_0,
    PROP_APP,
    N_PROPERTIES
};

typedef struct _IpcamHttpProcPrivate
{
    IpcamIConfig *iconfig;
    GList *request_handler_list;
} IpcamHttpProcPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(IpcamHttpProc, ipcam_http_proc, G_TYPE_OBJECT)

static GParamSpec *obj_properties[N_PROPERTIES] = {NULL, };

static void ipcam_http_proc_finalize(GObject *object)
{
    IpcamHttpProcPrivate *priv = ipcam_http_proc_get_instance_private(IPCAM_HTTP_PROC(object));
    GList *item = g_list_first(priv->request_handler_list);
    for (; item; item = g_list_next(item))
    {
        g_object_unref(item->data);
    }
    g_list_free(priv->request_handler_list);
    G_OBJECT_CLASS(ipcam_http_proc_parent_class)->finalize(object);
}
static void ipcam_http_proc_init(IpcamHttpProc *self)
{
    IpcamHttpProcPrivate *priv = ipcam_http_proc_get_instance_private(self);
    IpcamHttpRequestHandler *base_info_handler =
        g_object_new(IPCAM_HTTP_BASE_INFO_HANDLER_TYPE, "app", priv->iconfig, NULL);
    priv->request_handler_list = g_list_append(priv->request_handler_list, base_info_handler);
}
static void ipcam_http_proc_get_property(GObject    *object,
                                         guint       property_id,
                                         GValue     *value,
                                         GParamSpec *pspec)
{
    IpcamHttpProc *self = IPCAM_HTTP_PROC(object);
    IpcamHttpProcPrivate *priv = ipcam_http_proc_get_instance_private(self);
    switch(property_id)
    {
    case PROP_APP:
        {
            g_value_set_object(value, priv->iconfig);
        }
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}
static void ipcam_http_proc_set_property(GObject      *object,
                                         guint         property_id,
                                         const GValue *value,
                                         GParamSpec   *pspec)
{
    IpcamHttpProc *self = IPCAM_HTTP_PROC(object);
    IpcamHttpProcPrivate *priv = ipcam_http_proc_get_instance_private(self);
    switch(property_id)
    {
    case PROP_APP:
        {
            priv->iconfig = g_value_get_object(value);
        }
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}
static void ipcam_http_proc_class_init(IpcamHttpProcClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->finalize = &ipcam_http_proc_finalize;
    object_class->get_property = &ipcam_http_proc_get_property;
    object_class->set_property = &ipcam_http_proc_set_property;

    obj_properties[PROP_APP] =
        g_param_spec_object("app",
                            "application",
                            "application.",
                            IPCAM_ICONFIG_TYPE, // default value
                            G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);

    g_object_class_install_properties(object_class, N_PROPERTIES, obj_properties);
}
IpcamHttpResponse *ipcam_http_proc_get_response(IpcamHttpProc *http_proc, IpcamHttpRequest *http_request)
{
    g_return_val_if_fail(IPCAM_IS_HTTP_PROC(http_proc), NULL);
    g_return_val_if_fail(IPCAM_IS_HTTP_REQUEST(http_request), NULL);

    IpcamHttpResponse *response = g_object_new(IPCAM_HTTP_RESPONSE_TYPE, NULL);

    IpcamHttpProcPrivate *priv = ipcam_http_proc_get_instance_private(http_proc);
    GList *item = g_list_first(priv->request_handler_list);
    for (; item; item = g_list_next(item))
    {
        if (ipcam_http_request_handler_dispatch(item->data, http_request, response))
        {
            break;
        }
    }
    
    return response;
}
