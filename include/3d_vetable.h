/*
 * Copyright (C) 2003 by Dave J. Andruczyk <djandruczyk at yahoo dot com>
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

#ifndef __3D_VETABLE_H__
#define __3D_VETABLE_H__

#include <gtk/gtk.h>

/* GL includes */
#include <gtk/gtkwidget.h>
#include <gtk/gtkgl.h>
#ifdef __WIN32__
 #include <gdk/gdkglglext.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <pango/pangoft2.h>
#include <gdk/gdkkeysyms.h>

/* Prototypes */
gint create_ve3d_view(GtkWidget *, gpointer );
gint free_ve3d_view(GtkWidget *);
GdkGLConfig* get_gl_config(void);
void ve3d_realize (GtkWidget *, gpointer );
gboolean ve3d_configure_event(GtkWidget *, GdkEventConfigure *,gpointer);
gboolean ve3d_expose_event(GtkWidget *, GdkEventExpose *, gpointer);
gboolean ve3d_motion_notify_event(GtkWidget *, GdkEventMotion *,gpointer);
gboolean ve3d_key_press_event (GtkWidget *, GdkEventKey *, gpointer);
gboolean ve3d_button_press_event(GtkWidget *, GdkEventButton *, gpointer);
void ve3d_calculate_scaling(void *);
void ve3d_draw_ve_grid(void *);
void ve3d_draw_active_indicator(void *);
void ve3d_draw_runtime_indicator(void *);
void ve3d_draw_axis(void *);
void ve3d_draw_text(gchar * text, gfloat x, gfloat y, gfloat z);
void ve3d_load_font_metrics(void);
void reset_3d_view(GtkWidget *);
void initialize_ve3d_view(void *);

/* Prototypes */

/* Datastructures... */

/*!
 \brief the Ve_View_3D structure contains all the field to create and 
 manipulate a 3D view of a MegaSquirt VE/Spark table, and should work in
 theory for any sized table
 */
struct Ve_View_3D
{
	gint beginX;
	gint beginY;
	gint active_y;
	gint active_x;
	gfloat dt;
	gfloat sphi;
	gfloat stheta;
	gfloat sdepth;
	gfloat zNear;
	gfloat zFar;
	gfloat aspect;
	gfloat x_div;
	gfloat y_div;
	gfloat z_div;
	gfloat h_strafe;
	gfloat v_strafe;
	gint x_max;
	gint y_max;
	gint z_max;
	gint z_min;
	gchar *x_source;
	gchar *y_source;
	gchar *z_source;
	GtkWidget *drawing_area;
	GtkWidget *window;
	GtkWidget *burn_but;
	gint y_base;
	gint y_page;
	gint y_bincount;
	gint tbl_base;
	gint tbl_page;
	gint x_base;
	gint x_page;
	gint x_bincount;
	gboolean is_spark;
	gchar *table_name;
	gint table_num;
};

#endif
