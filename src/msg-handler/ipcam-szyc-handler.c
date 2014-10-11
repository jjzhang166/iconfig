/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * ipcam-szyc-handler.c
 * Copyright (C) 2014 Watson Xu <xuhuashan@gmail.com>
 *
 * iconfig is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * iconfig is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include <glib/gprintf.h>
#include <base_app.h>
#include "ipcam-szyc-handler.h"
#include "iconfig.h"
#include "sysutils.h"
#include "common.h"

G_DEFINE_TYPE (IpcamSzycMsgHandler, ipcam_szyc_msg_handler, IPCAM_TYPE_MESSAGE_HANDLER);

static void
ipcam_szyc_msg_handler_init (IpcamSzycMsgHandler *ipcam_szyc_msg_handler)
{
}

static void
ipcam_szyc_msg_handler_finalize (GObject *object)
{
    G_OBJECT_CLASS (ipcam_szyc_msg_handler_parent_class)->finalize (object);
}

static gboolean
ipcam_szyc_msg_handler_read_param(IpcamSzycMsgHandler *handler, JsonBuilder *builder, const gchar *name)
{
    IpcamIConfig *iconfig;
    g_object_get(G_OBJECT(handler), "app", &iconfig, NULL);
    gchar *value = NULL;
    gboolean ret = FALSE;

    value = ipcam_iconfig_get_szyc(iconfig, name);
    if (value)
    {
        json_builder_set_member_name(builder, name);
        json_builder_add_string_value(builder, value);
        ret = TRUE;
    }

    return ret;
}

static gboolean
ipcam_szyc_msg_handler_update_param(IpcamSzycMsgHandler *handler, const gchar *name, const gchar *value)
{
    IpcamIConfig *iconfig;
    g_object_get(G_OBJECT(handler), "app", &iconfig, NULL);

    ipcam_iconfig_set_szyc(iconfig, name, value);
    return TRUE;
}

static gboolean
ipcam_szyc_msg_handler_get_action_impl(IpcamMessageHandler *handler, JsonNode *request, JsonNode **response)
{
    JsonBuilder *builder = json_builder_new();
    JsonArray *req_array;
    int idx;

    req_array = json_object_get_array_member(json_node_get_object(request), "items");

    json_builder_begin_object(builder);
    json_builder_set_member_name(builder, "items");
    json_builder_begin_object(builder);
    for (idx = 0; idx < json_array_get_length(req_array); idx++)
    {
        const gchar *name = json_array_get_string_element(req_array, idx);
        ipcam_szyc_msg_handler_read_param(IPCAM_SZYC_MSG_HANDLER(handler), builder, name);
    }
    json_builder_end_object(builder);
    json_builder_end_object(builder);

    *response = json_builder_get_root(builder);

    g_object_unref(builder);

    return TRUE;
}

static gboolean
ipcam_szyc_msg_handler_put_action_impl(IpcamMessageHandler *handler, JsonNode *request, JsonNode **response)
{
    JsonBuilder *builder = json_builder_new();
    JsonObject *req_obj;
    GList *members, *item;

    req_obj = json_object_get_object_member(json_node_get_object(request), "items");
    members = json_object_get_members(req_obj);

    json_builder_begin_object(builder);
    json_builder_set_member_name(builder, "items");
    json_builder_begin_object(builder);
    for (item = g_list_first(members); item; item = g_list_next(item))
    {
        const gchar *name = item->data;
        const gchar *value = json_object_get_string_member(req_obj, name);
        ipcam_szyc_msg_handler_update_param(IPCAM_SZYC_MSG_HANDLER(handler), name, value);
        ipcam_szyc_msg_handler_read_param(IPCAM_SZYC_MSG_HANDLER(handler), builder, name);
    }
    g_list_free(members);
    json_builder_end_object(builder);
    json_builder_end_object(builder);

    *response = json_builder_get_root(builder);

    g_object_unref(builder);

    return TRUE;
}

static void
ipcam_szyc_msg_handler_class_init (IpcamSzycMsgHandlerClass *klass)
{
    GObjectClass* object_class = G_OBJECT_CLASS (klass);
    IpcamMessageHandlerClass *parent_class = IPCAM_MESSAGE_HANDLER_CLASS(klass);

    object_class->finalize = ipcam_szyc_msg_handler_finalize;

    parent_class->get_action = ipcam_szyc_msg_handler_get_action_impl;
    parent_class->put_action = ipcam_szyc_msg_handler_put_action_impl;
}