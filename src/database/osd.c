#include "osd.h"

enum {
  PROP_0,
  PROP_ID,
  PROP_NAME,
  PROP_IS_SHOW,
  PROP_SIZE,
  PROP_LEFT,
  PROP_TOP,
  PROP_COLOR,
  N_PROPERTIES
};

typedef struct _IpcamOsdPrivate
{
    guint id;
    gchar *name;
    gboolean is_show;
    guint size;
    guint left;
    guint top;
    guint color;
} IpcamOsdPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(IpcamOsd, ipcam_osd, GOM_TYPE_RESOURCE);

static GParamSpec *obj_properties[N_PROPERTIES] = {NULL, };

static void ipcam_osd_finalize(GObject *object)
{
    IpcamOsdPrivate *priv = ipcam_osd_get_instance_private(IPCAM_OSD(object));
    g_free(priv->name);
    G_OBJECT_CLASS(ipcam_osd_parent_class)->finalize(object);
}
static void ipcam_osd_set_property(GObject      *object,
                                   guint        property_id,
                                   const GValue *value,
                                   GParamSpec   *pspec)
{
    IpcamOsd *self = IPCAM_OSD(object);
    IpcamOsdPrivate *priv = ipcam_osd_get_instance_private(self);
    switch(property_id)
    {
    case PROP_ID:
        {
            priv->id = g_value_get_uint(value);
        }
        break;
    case PROP_NAME:
        {
            g_free(priv->name);
            priv->name = g_value_dup_string(value);
        }
        break;
    case PROP_IS_SHOW:
        {
            priv->is_show = g_value_get_boolean(value);
        }
        break;
    case PROP_SIZE:
        {
            priv->size = g_value_get_uint(value);
        }
        break;
    case PROP_LEFT:
        {
            priv->left = g_value_get_uint(value);
        }
        break;
    case PROP_TOP:
        {
            priv->top = g_value_get_uint(value);
        }
        break;
    case PROP_COLOR:
        {
            priv->color = g_value_get_uint(value);
        }
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}
static void ipcam_osd_get_property(GObject    *object,
                                   guint       property_id,
                                   GValue     *value,
                                   GParamSpec *pspec)
{
    IpcamOsd *self = IPCAM_OSD(object);
    IpcamOsdPrivate *priv = ipcam_osd_get_instance_private(self);
    switch(property_id)
    {
    case PROP_ID:
        {
            g_value_set_uint(value, priv->id);
        }
        break;
    case PROP_NAME:
        {
            g_value_set_string(value, priv->name);
        }
        break;
    case PROP_IS_SHOW:
        {
            g_value_set_boolean(value, priv->is_show);
        }
        break;
    case PROP_SIZE:
        {
            g_value_set_uint(value, priv->size);
        }
        break;
    case PROP_LEFT:
        {
            g_value_set_uint(value, priv->left);
        }
        break;
    case PROP_TOP:
        {
            g_value_set_uint(value, priv->top);
        }
        break;
    case PROP_COLOR:
        {
            g_value_set_uint(value, priv->color);
        }
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}
static void ipcam_osd_init(IpcamOsd *self)
{
}
static void ipcam_osd_class_init(IpcamOsdClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->set_property = &ipcam_osd_set_property;
    object_class->get_property = &ipcam_osd_get_property;
    object_class->finalize = &ipcam_osd_finalize;

    GomResourceClass *resource_class = GOM_RESOURCE_CLASS(klass);
    gom_resource_class_set_table(resource_class, "osd");
  
    obj_properties[PROP_ID] =
        g_param_spec_uint("id",
                          "ID",
                          "The ID for the user.",
                          0,
                          G_MAXUINT,
                          0, // default value
                          G_PARAM_READWRITE);
    obj_properties[PROP_NAME] =
        g_param_spec_string("name",
                            "Name",
                            "Name.",
                            NULL, // default value
                            G_PARAM_READWRITE);
    obj_properties[PROP_IS_SHOW] =
        g_param_spec_boolean("isshow",
                             "Show?",
                             "Is this content show?",
                             TRUE,
                             G_PARAM_READWRITE);
    obj_properties[PROP_SIZE] =
        g_param_spec_uint("size",
                          "Size",
                          "Font size of the content.",
                          1,
                          100,
                          20, // default value
                          G_PARAM_READWRITE);
    obj_properties[PROP_LEFT] =
        g_param_spec_uint("left",
                          "left position",
                          "X axsis position, percent of image resolution.",
                          0,
                          1000,
                          0, // default value
                          G_PARAM_READWRITE);
    obj_properties[PROP_TOP] =
        g_param_spec_uint("top",
                          "top position",
                          "Y Axsis position, percent of image resolution.",
                          0,
                          1000,
                          0, // default value
                          G_PARAM_READWRITE);
    obj_properties[PROP_COLOR] =
        g_param_spec_uint("color",
                          "OSD color",
                          "Color of the content.",
                          0,
                          G_MAXUINT,
                          0, // default value
                          G_PARAM_READWRITE);

    g_object_class_install_properties(object_class, N_PROPERTIES, obj_properties);
    gom_resource_class_set_primary_key(resource_class, "id");
    gom_resource_class_set_unique(resource_class, "name");
    gom_resource_class_set_notnull(resource_class, "name");
}
