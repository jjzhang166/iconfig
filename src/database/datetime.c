#include "datetime.h"

enum {
  PROP_0,
  PROP_ID,
  PROP_NAME,
  PROP_INT_VALUE,
  PROP_STR_VALUE,
  N_PROPERTIES
};

typedef struct _IpcamDatetimePrivate
{
    guint id;
    gchar *name;
    guint int_value;
    gchar *str_value;
} IpcamDatetimePrivate;

G_DEFINE_TYPE_WITH_PRIVATE(IpcamDatetime, ipcam_datetime, GOM_TYPE_RESOURCE);

static GParamSpec *obj_properties[N_PROPERTIES] = {NULL, };

static void ipcam_datetime_finalize(GObject *object)
{
    IpcamDatetimePrivate *priv = ipcam_datetime_get_instance_private(IPCAM_DATETIME(object));
    g_free(priv->name);
    g_free(priv->str_value);
    G_OBJECT_CLASS(ipcam_datetime_parent_class)->finalize(object);
}
static void ipcam_datetime_set_property(GObject      *object,
                                        guint        property_id,
                                        const GValue *value,
                                        GParamSpec   *pspec)
{
    IpcamDatetime *self = IPCAM_DATETIME(object);
    IpcamDatetimePrivate *priv = ipcam_datetime_get_instance_private(self);
    switch(property_id)
    {
    case PROP_ID:
        {
            priv->id = g_value_get_int(value);
        }
        break;
    case PROP_NAME:
        {
            g_free(priv->name);
            priv->name = g_value_dup_string(value);
        }
        break;
    case PROP_INT_VALUE:
        {
            priv->int_value = g_value_get_int(value);
        }
        break;
    case PROP_STR_VALUE:
        {
            g_free(priv->str_value);
            priv->str_value = g_value_dup_string(value);
        }
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}
static void ipcam_datetime_get_property(GObject    *object,
                                   guint       property_id,
                                   GValue     *value,
                                   GParamSpec *pspec)
{
    IpcamDatetime *self = IPCAM_DATETIME(object);
    IpcamDatetimePrivate *priv = ipcam_datetime_get_instance_private(self);
    switch(property_id)
    {
    case PROP_ID:
        {
            g_value_set_int(value, priv->id);
        }
        break;
    case PROP_NAME:
        {
            g_value_set_string(value, priv->name);
        }
        break;
    case PROP_INT_VALUE:
        {
            g_value_set_int(value, priv->int_value);
        }
        break;
    case PROP_STR_VALUE:
        {
            g_value_set_string(value, priv->str_value);
        }
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}
static void ipcam_datetime_init(IpcamDatetime *self)
{
}
static void ipcam_datetime_class_init(IpcamDatetimeClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->set_property = &ipcam_datetime_set_property;
    object_class->get_property = &ipcam_datetime_get_property;
    object_class->finalize = &ipcam_datetime_finalize;

    GomResourceClass *resource_class = GOM_RESOURCE_CLASS(klass);
    gom_resource_class_set_table(resource_class, "datetime");
  
    obj_properties[PROP_ID] =
        g_param_spec_int("id",
                         "ID",
                         "The ID for the user.",
                         0,
                         65535,
                         0, // default value
                         G_PARAM_READWRITE);
    obj_properties[PROP_NAME] =
        g_param_spec_string("name",
                            "Parameter Name",
                            "Datetime parameter name.",
                            NULL, // default value
                            G_PARAM_READWRITE);
    obj_properties[PROP_INT_VALUE] =
        g_param_spec_int("intvalue",
                         "Parameter value",
                         "Datetime parameter integer value.",
                         0,
                         65535,
                         0, // default value
                         G_PARAM_READWRITE);
    obj_properties[PROP_STR_VALUE] =
        g_param_spec_string("strvalue",
                            "Parameter value",
                            "Datetime parameter string value.",
                            NULL, // default value
                            G_PARAM_READWRITE);

    g_object_class_install_properties(object_class, N_PROPERTIES, obj_properties);
    gom_resource_class_set_primary_key(resource_class, "id");
    gom_resource_class_set_unique(resource_class, "name");
    gom_resource_class_set_notnull(resource_class, "name");
}