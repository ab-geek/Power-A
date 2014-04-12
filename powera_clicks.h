

static void about_us()
{
	GtkWidget *win,*label;
	win=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(win),"Power A: About us");
	gtk_widget_set_size_request(win,450,300);
	gtk_window_set_position(GTK_WINDOW(win),GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(win), 0);
	label=gtk_label_new("We are Computer engineering students from Kathmandu University \n This is our first project on II semester\n\t\t Developers\n Ashish Belwase \n Ashmit Bhattarai \n Amit Joshi \n Sushil Subedi \n\n Under the supervision of \n Dhiraj Shrestha");
	gtk_container_add(GTK_CONTAINER(win),label);
	GdkColor lcolor;
	gdk_color_parse ("black", &lcolor);
	gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &lcolor);
	g_signal_connect(win,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect (G_OBJECT (win), "delete_event", G_CALLBACK (state_event), NULL);
	g_signal_connect (G_OBJECT (win), "window-state-event", G_CALLBACK (state_event), win);
	gtk_window_set_deletable(win,TRUE);
	gtk_window_reshow_with_initial_size (win);
	
	gtk_widget_show_all(win);
	gtk_main();
}


static void left_click_cb(GtkWidget *tray_icon)
{
	
		g_signal_connect(tray_icon,"activate",G_CALLBACK(main_window),NULL);


}
static void right_click_cb(GtkStatusIcon *icon,int button,int time,gpointer data)
{
	GtkWidget *menu,*view,*exit,*about;
	menu = gtk_menu_new();
	view=gtk_menu_item_new_with_label("Open Power-A");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),view);
	g_signal_connect (G_OBJECT (view), "activate", G_CALLBACK (main_window), NULL);
	view=gtk_menu_item_new_with_label("About us");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),view);
	g_signal_connect (G_OBJECT (view), "activate", G_CALLBACK (about_us), NULL);
	view=gtk_menu_item_new_with_label("Exit the program");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),view);
	g_signal_connect (G_OBJECT (view), "activate", G_CALLBACK (gtk_main_quit), NULL);
	gtk_widget_show_all(menu);
	gtk_menu_popup(GTK_MENU(menu),NULL,NULL,gtk_status_icon_position_menu,icon,button,time);
	
}
