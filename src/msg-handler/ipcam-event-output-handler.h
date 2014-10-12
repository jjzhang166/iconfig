/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * ipcam-base-info-handler.h
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

#ifndef _IPCAM_EVENT_OUTPUT_MSG_HANDLER_H_
#define _IPCAM_EVENT_OUTPUT_MSG_HANDLER_H_

#include <glib-object.h>
#include "ipcam-message-handler.h"

G_BEGIN_DECLS

#define IPCAM_TYPE_EVENT_OUTPUT_MSG_HANDLER             (ipcam_event_output_msg_handler_get_type ())
#define IPCAM_EVENT_OUTPUT_MSG_HANDLER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), IPCAM_TYPE_EVENT_OUTPUT_MSG_HANDLER, IpcamEventOutputMsgHandler))
#define IPCAM_EVENT_OUTPUT_MSG_HANDLER_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), IPCAM_TYPE_EVENT_OUTPUT_MSG_HANDLER, IpcamEventOutputMsgHandlerClass))
#define IPCAM_IS_EVENT_OUTPUT_MSG_HANDLER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IPCAM_TYPE_EVENT_OUTPUT_MSG_HANDLER))
#define IPCAM_IS_EVENT_OUTPUT_MSG_HANDLER_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), IPCAM_TYPE_EVENT_OUTPUT_MSG_HANDLER))
#define IPCAM_EVENT_OUTPUT_MSG_HANDLER_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), IPCAM_TYPE_EVENT_OUTPUT_MSG_HANDLER, IpcamEventOutputMsgHandlerClass))

typedef struct _IpcamEventOutputMsgHandlerClass IpcamEventOutputMsgHandlerClass;
typedef struct _IpcamEventOutputMsgHandler IpcamEventOutputMsgHandler;
typedef struct _IpcamEventOutputMsgHandlerPrivate IpcamEventOutputMsgHandlerPrivate;


struct _IpcamEventOutputMsgHandlerClass
{
    IpcamMessageHandlerClass parent_class;
};

struct _IpcamEventOutputMsgHandler
{
    IpcamMessageHandler parent_instance;

    IpcamEventOutputMsgHandlerPrivate *priv;
};

GType ipcam_event_output_msg_handler_get_type (void) G_GNUC_CONST;

G_END_DECLS

#endif /* _IPCAM_EVENT_OUTPUT_MSG_HANDLER_H_ */

