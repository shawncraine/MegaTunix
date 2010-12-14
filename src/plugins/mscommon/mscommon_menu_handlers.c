/*
 * Copyright (C) 2003 by Dave J. Andruczyk <djandruczyk at yahoo dot com>
 *
 * Linux Megasquirt tuning software
 * 
 * 
 * This software comes under the GPL (GNU Public License)
 * You may freely copy,distribute etc. this as long as the source code
 * is made available for FREE.
 * 
 * No warranty is made or implied. You use this program at your own risk.
 */

#include <config.h>
#include <datamgmt.h>
#include <debugging.h>
#include <firmware.h>
#include <gtk/gtk.h>
#include <mscommon_menu_handlers.h>

extern gconstpointer *global_data;


void common_plugin_menu_setup(GladeXML *xml)
{
	void (*ecu_plugin_menu_setup)(GladeXML *) = NULL;
	GtkWidget *item = NULL;

	if (get_symbol_f("ecu_plugin_menu_setup",(void *)&ecu_plugin_menu_setup))
		ecu_plugin_menu_setup(xml);
	return;
}


G_MODULE_EXPORT gboolean create_ignition_map(GtkWidget *widget, gpointer data)
{
	GladeXML* xml = NULL;
	GtkWidget* item = NULL;
	gint i = 0;
	gint x = 0;
	gint y = 0;
	gint table=  0;
	gchar *table_title = NULL;
	Firmware_Details *firmware = NULL;
	gint canID = 0;
	gdouble x_bin[64], y_bin[64];
	gint page = 0;
	gint base = 0;
	DataSize size = MTX_U08;
	gint mult = 0;
	void *evaluator = NULL;
	gdouble light_advance = 0.0;
	gdouble idle_rpm = 0.0;
	gdouble idle_load = 0.0;
	gdouble idle_advance = 0.0;
	gdouble peak_torque_rpm = 0.0;
	gdouble peak_torque_load = 0.0;
	gdouble peak_torque_advance = 0.0;
	gdouble advance = 0.0;
	gdouble maximum_rpm_advance = 0.0;
	gdouble maximum_retard = 0.0;
	gdouble retard_start_load = 0.0;
	GList ***ve_widgets = NULL;
	GList *list = NULL;
	gchar * tmpbuf = NULL;
	gint precision = 0;

	ve_widgets = DATA_GET(global_data,"ve_widgets");
	firmware = DATA_GET(global_data,"firmware");
	canID = firmware->canID;

	xml = glade_get_widget_tree (GTK_WIDGET (widget));

	/* find the combo box */
	item = glade_xml_get_widget (xml, "spark_table_combo");
	if (!item)
	{
		dbg_func_f(CRITICAL, g_strdup_printf(__FILE__ ": create_ignition_map():\n\tUnable to find spark table combo! where am I?\n"));
		return TRUE;
	}

	/* the selected text in the combo box */
	table_title = (gchar *) gtk_combo_box_get_active_text(GTK_COMBO_BOX(item));
	if (table_title == NULL)
	{
		dbg_func_f(CRITICAL, g_strdup_printf(__FILE__ ": create_ignition_map():\n\ttable_title was unavailable\n"));
		return TRUE;
	}

	/* iterate through the firmware tables looking for a match */
	for (table=0; table!= firmware->total_tables; table++)
		if (!g_strcmp0(table_title, firmware->table_params[table]->table_name)) /* we have a match? */
			break;

	/* light load */
	item = glade_xml_get_widget (xml, "light_advance");
	light_advance = strtod(gtk_entry_get_text(GTK_ENTRY(item)), NULL);

	/* idle */
	item = glade_xml_get_widget (xml, "idle_rpm");
	idle_rpm = strtod(gtk_entry_get_text(GTK_ENTRY(item)), NULL);

	item = glade_xml_get_widget (xml, "idle_advance");
	idle_advance = strtod(gtk_entry_get_text(GTK_ENTRY(item)), NULL);

	item = glade_xml_get_widget (xml, "idle_load");
	idle_load = strtod(gtk_entry_get_text(GTK_ENTRY(item)), NULL);

	/* peak torque */
	item = glade_xml_get_widget (xml, "peak_torque_rpm");
	peak_torque_rpm = strtod(gtk_entry_get_text(GTK_ENTRY(item)), NULL);

	item = glade_xml_get_widget (xml, "peak_torque_advance");
	peak_torque_advance = strtod(gtk_entry_get_text(GTK_ENTRY(item)), NULL);

	item = glade_xml_get_widget (xml, "peak_torque_load");
	peak_torque_load = strtod(gtk_entry_get_text(GTK_ENTRY(item)), NULL);

	/* extra advance at tables maximum RPM */
	item = glade_xml_get_widget (xml, "maximum_rpm_advance");
	maximum_rpm_advance = strtod(gtk_entry_get_text(GTK_ENTRY(item)), NULL);

	/* retard */
	item = glade_xml_get_widget (xml, "maximum_retard");
	maximum_retard = strtod(gtk_entry_get_text(GTK_ENTRY(item)), NULL);

	item = glade_xml_get_widget (xml, "retard_start_load");
	retard_start_load = strtod(gtk_entry_get_text(GTK_ENTRY(item)), NULL);

	/* build a copy of the x and y bins */
	/* Find bin corresponding to rpm  */
	page = firmware->table_params[table]->x_page;
	base = firmware->table_params[table]->x_base;
	size = firmware->table_params[table]->x_size;
	mult = get_multiplier_f(size);

	evaluator = eval_create_f(firmware->table_params[table]->x_ul_conv_expr);

	/* fetch us a copy of the x bins */
	for (i=0; i != firmware->table_params[table]->x_bincount; i++)
		x_bin[i] = eval_x_f(evaluator, ms_get_ecu_data(canID, page, base+(i*mult), size));

	eval_destroy_f(evaluator);

	/* Find bin corresponding to load  */
	page = firmware->table_params[table]->y_page;
	base = firmware->table_params[table]->y_base;
	size = firmware->table_params[table]->y_size;
	mult = get_multiplier_f(size);

	evaluator = eval_create_f(firmware->table_params[table]->y_ul_conv_expr);

	/* fetch us a copy of the y bins */
	for (i=0; i != firmware->table_params[table]->y_bincount; i++)
		y_bin[i] = eval_x_f(evaluator, ms_get_ecu_data(canID, page, base+(i*mult), size));

	eval_destroy_f(evaluator);

	page = firmware->table_params[table]->z_page;
	base = firmware->table_params[table]->z_base;
	size = firmware->table_params[table]->z_size;
	mult = get_multiplier_f(size);


	/* generate a spark table :) */
	for (y=0; y != firmware->table_params[table]->y_bincount; y++)
	{
		for (x=0; x != firmware->table_params[table]->x_bincount; x++)
		{

			/* idle -> peak torque rpm, advance interpolate */
			advance = linear_interpolate(x_bin[x], idle_rpm, peak_torque_rpm, idle_advance, peak_torque_advance);

			/* maximum extra advance? */
			if (x_bin[x] > peak_torque_rpm)
				advance += linear_interpolate(x_bin[x], peak_torque_rpm, x_bin[firmware->table_params[table]->x_bincount-1], 0, maximum_rpm_advance);

			/* low load advance */
			/* high load retard */
			if (y_bin[y] > retard_start_load)
				advance -= linear_interpolate(y_bin[y], retard_start_load, y_bin[firmware->table_params[table]->y_bincount-1], 0, maximum_retard);

			/* HACK ALERT,  this assumes the list at
			 * ve_widgets[page][offset], contains the VEtable widget at
			 * offset 0 of that list.  (assumptions are bad practice!)
			 */
			if (firmware->capabilities & PIS)
				list = ve_widgets[firmware->table_params[table]->z_page][firmware->table_params[table]->z_base + ((x * firmware->table_params[table]->y_bincount) * mult) + (y * mult)];
			else
				list = ve_widgets[firmware->table_params[table]->z_page][firmware->table_params[table]->z_base + ((y * firmware->table_params[table]->y_bincount) * mult) + (x * mult)];
			widget = g_list_nth_data(list,0);
			precision = (GINT)OBJ_GET(widget, "precision");
			tmpbuf = g_strdup_printf("%1$.*2$f", advance, precision);
			gtk_entry_set_text(GTK_ENTRY(widget), tmpbuf);
			g_free(tmpbuf);

			std_entry_handler_f(GTK_WIDGET(widget), NULL);
		}
	}

	gtk_widget_hide(glade_xml_get_widget (xml, "create_ignition_window"));
	return TRUE;
}


/* non extrapolating linear dual line interpolation (3 times fast after 6 beers :-) */
G_MODULE_EXPORT gdouble linear_interpolate(gdouble offset, gdouble slope1_a, gdouble slope1_b, gdouble slope2_a, gdouble slope2_b)
{
	gdouble slope1, slope2, result;
	gdouble ratio;
	gint negative = 0;

	/* prevent extrapolation */
	if (offset <= slope1_a) return slope2_a;
	if (offset >= slope1_b) return slope2_b;

	offset -= slope1_a;
	slope1 = slope1_b - slope1_a;

	if (slope2_a > slope2_b)
	{
		slope2 = slope2_a - slope2_b;
		negative = 1;
	}
	else slope2 = slope2_b - slope2_a;

	ratio = (gdouble) offset / slope1;
	result = ((gdouble)slope2_a * (1-ratio) + (gdouble)slope2_b * ratio);
	return result;
}

