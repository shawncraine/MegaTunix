/*
 * Copyright (C) 2002-2012 by Dave J. Andruczyk <djandruczyk at yahoo dot com>
 *
 * Linux Megasquirt tuning software
 * 
 * 
 * This software comes under the GPL (GNU Public License)
 * You may freely copy,distribute, etc. this as long as all the source code
 * is made available for FREE.
 * 
 * No warranty is made or implied. You use this program at your own risk.
 */

/*!
  \file include/notifications.h
  \ingroup Headers
  \brief Header for notification message functions
  \author David Andruczyk
  */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __NOTIFICATIONS_H__
#define __NOTIFICATIONS_H__

#include <enums.h>
#include <gtk/gtk.h>

/* Prototypes */
void set_group_color(GuiColor, const gchar * );
void set_reqfuel_color(GuiColor, gint );
void set_widget_color(gpointer, gpointer );
void update_logbar(const gchar *, const gchar *, gchar *, gboolean, gboolean,gboolean);
void no_ms_connection(void);
void warn_user(const gchar *);
void error_msg(const gchar *);
void set_title(gchar *);
void conn_warning(void);
void kill_conn_warning(void);
gboolean reset_infolabel(gpointer);
gboolean get_response(GtkWidget *, gpointer );

gint close_dialog(GtkWidget *, gpointer);
gint dialog_response(GtkWidget *, gpointer );
gboolean set_warning_flag(gpointer);
/* Prototypes */

#endif
#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif
