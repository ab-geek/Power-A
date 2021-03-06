#include <gtk/gtk.h>
#include <libudev.h>
#include <libnotify/notify.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "./powera.h"
#include "./powera_main.h"
#include "./powera_option.h"
#include "./powera_calculation.h"
#include "./powera_bool.h"
#include "./powera_notify.h"
#include "./powera_clicks.h"
#include "./powera_sys.h"
#include "./powera_tray.h"



gboolean function_to_call(gpointer data){
   GtkWidget * window_10_sec = (GtkWidget *) data;
   gtk_widget_hide(window_10_sec);
	create_tray_icon();
	
   return(FALSE);
}


int main(int argc,char *argv[])
{

	gtk_init(&argc,&argv);
	get_options (argc, argv);
	get_battery (argc > 1 ? argv[1] : NULL, FALSE); //if true then list battery and stop forward execution
	notify_init ("Power A : Gnome Power Management");
	
	//for splash
	GtkWidget *image, *window;
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated(GTK_WINDOW (window), FALSE);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	image=gtk_image_new_from_file("load.png");
  gtk_container_add(GTK_CONTAINER(window), image);
 gtk_widget_show_all (window);
	g_timeout_add (2000, function_to_call,window);

	gtk_main();
}
