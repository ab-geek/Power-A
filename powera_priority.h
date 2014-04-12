
static void calculate_priority( Data *data )
{


FILE *f;
char *p=strdup(gtk_entry_get_text( data->e1 ));
char *q=strdup(gtk_entry_get_text( data->e2 ));
char r[]="  ";

int x;

	const char abc[]="renice -n ";
	strcat(q,r);
	strcat(abc,q);
	strcat(abc,p);
	system(abc);


//gtk_label_set_label( data->res, result );
//g_free( result );
}

void set_priority(GtkWidget* b3,gpointer first_button)
{
	
	
	GtkWidget *window;
	GtkWidget *entry,*entry2;
	GtkWidget *scrolled_window;
	GtkWidget *button,*b2;
	GtkWidget *label1,*label2;
	Data *data;
	GtkWidget *fixed;
	data = g_slice_new0( Data );

	system("ps -eo user,pid,comm  >temp/list");

	gtk_widget_set_sensitive(GTK_WIDGET(b3),1);
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(window),1);
	gtk_window_set_title (GTK_WINDOW (window), "Adjust the priority of Program");
	gtk_widget_set_size_request(GTK_WINDOW(window),800,500);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), 0);
	
	gtk_container_set_border_width (GTK_CONTAINER (window), 20);

	fixed = gtk_fixed_new ();

	label1 = gtk_label_new ("Enter the PID and priority number of\n process that you want to \nadjust. Value is from -20 to 20.\n Higher the value lesser the priority ");
	gtk_fixed_put(GTK_FIXED(fixed), label1, 15, 5);
	entry = gtk_entry_new();
	gtk_entry_set_max_length( GTK_ENTRY( entry ), 50 );
	gtk_entry_set_text (GTK_ENTRY (entry), "PID ");
	gtk_editable_select_region (GTK_EDITABLE (entry), 0, -1);
	data->e1 = GTK_ENTRY( entry );
	gtk_fixed_put(GTK_FIXED(fixed), entry, 15, 100);

	entry2 = gtk_entry_new();
	gtk_entry_set_max_length( GTK_ENTRY( entry2 ), 50 );
	gtk_entry_set_text (GTK_ENTRY (entry2), "Priority ");
	gtk_editable_select_region (GTK_EDITABLE (entry2), 0, -1);
	data->e2 = GTK_ENTRY( entry2 );
	gtk_fixed_put(GTK_FIXED(fixed), entry2, 15, 130);

	button = gtk_button_new_with_label ("OK");
	g_signal_connect_swapped (G_OBJECT (button), "clicked",
	G_CALLBACK(calculate_priority), data);
	gtk_fixed_put(GTK_FIXED(fixed), button, 15, 160);


	label2 = gtk_label_new( "List of Process running on your computer");
	gtk_fixed_put(GTK_FIXED(fixed), label2, 260,0);
	GtkWidget *success;
	success = gtk_label_new( "");
	gtk_fixed_put(GTK_FIXED(fixed), success, 15,200);
	data->res = GTK_LABEL( success );
	GdkColor color;
	gdk_color_parse ("red", &color);
	gtk_widget_modify_fg(label2, GTK_STATE_NORMAL, &color);

	scrolled_window=gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_usize(scrolled_window, 500,800);
	gtk_fixed_put(GTK_FIXED(fixed), scrolled_window, 250, 20);

	gchar *filename,*content;
	gsize bytes;
	GError *error = NULL;
	GtkWidget *cont;
	filename = g_build_filename ("temp", "list", NULL);

	g_file_get_contents (filename, &content, &bytes, &error);
	cont=gtk_label_new(NULL);
	gtk_label_set_text(cont,content);
	
	gtk_scrolled_window_add_with_viewport( GTK_SCROLLED_WINDOW(scrolled_window),cont);


	GtkLayout *lay=gtk_layout_new(NULL,NULL);
	gtk_layout_put(lay,fixed,0,0);
	gtk_layout_set_size (lay,300,1024);

	b2=gtk_button_new_with_mnemonic("_Exit");
	gtk_widget_set_size_request(b2,50,20);
	gtk_fixed_put(GTK_FIXED(fixed),b2,300,600);
	g_signal_connect(b2,"clicked",G_CALLBACK(sens),first_button);
	g_signal_connect(b2,"clicked",G_CALLBACK(destroy),window);

	gtk_container_add (GTK_CONTAINER (window), lay);
	gtk_widget_show_all( window );
	
}
