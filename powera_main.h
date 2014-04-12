#include "powera_bright.h"
#include "powera_info.h"
#include "powera_process.h"
#include "powera_priority.h"



void set_cpu()
{
	system("./cpu.sh");

}
void switchgraphics()
{
	system("scripts/switch_between_cards.sh");
}
void updatepercent (GtkWidget *percent)
{
	gint percentage,time;
	
	if (!get_battery_charge_info (&percentage, &time))
return;
	gchar *text=NULL;
	text=(gchar*)g_malloc(25);
	g_sprintf(text,"%d",percentage);
	gtk_label_set_text(percent,text);
}

void updatetime (GtkWidget *battinfo)
{
	/*gint percentage,time;
	gchar *time_string;
	if (!get_battery_charge_info (&percentage, &time))
return;
	
	time_string = get_time_string (time);
	gchar *text=NULL;
	text=(gchar*)g_malloc(50);*/
	system("acpi>temp/chargestate");
	char *content;
	gsize length;
	GError *error=NULL;
	g_file_get_contents("temp/chargestate",&content,&length,&error);	
	
	gtk_label_set_text(battinfo,content);
	

}
static void main_window()
{


	GtkStatusIcon *tray_icon;
	GtkWidget *win,*frame;
		
	GtkWidget *img1,*img2,*img3,*img4,*img5,*label,*sys,*btry,*b,*b1,*b2,*b3,*b4,*cpu,*app,*hsep,*vsep;
	GtkWidget *graphics;
	win=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(win),"Power A: GNOME Power Management");
	gtk_widget_set_size_request(win,530,450);
	gtk_window_set_position(GTK_WINDOW(win),GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(win), 0);
	gtk_window_set_icon(GTK_WINDOW(win),icon("Battery0.png"));
	frame=gtk_fixed_new();
	
	

	
	label=gtk_label_new("Select an Option");
	gtk_fixed_put(GTK_FIXED(frame),label,45,180);
	GdkColor lcolor;
	gdk_color_parse ("white", &lcolor);
	gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &lcolor);
	
	b1=gtk_button_new_with_mnemonic("_Change Power Modes");
	gtk_widget_set_size_request(b1,200,25);
	gtk_fixed_put(GTK_FIXED(frame),b1,20,210);
	g_signal_connect(b1,"clicked",G_CALLBACK(pre_option),b1);
		
	b3=gtk_button_new_with_mnemonic("_View and Kill Process");
	gtk_widget_set_size_request(b3,200,25);
	gtk_fixed_put(GTK_FIXED(frame),b3,20,240);
	g_signal_connect(b3,"clicked",G_CALLBACK(kill_process),b3);

	cpu=gtk_button_new_with_mnemonic("_Set CPU Performance");
	gtk_widget_set_size_request(cpu,200,25);
	gtk_fixed_put(GTK_FIXED(frame),cpu,20,270);
	g_signal_connect(cpu,"clicked",G_CALLBACK(set_cpu),b3);

	app=gtk_button_new_with_mnemonic("_Set Softwares Priority");
	gtk_widget_set_size_request(app,200,25);
	gtk_fixed_put(GTK_FIXED(frame),app,20,300);
	g_signal_connect(app,"clicked",G_CALLBACK(set_priority),app);

	btry=gtk_button_new_with_mnemonic("View _Battery Information");
	gtk_widget_set_size_request(btry,200,25);
	gtk_fixed_put(GTK_FIXED(frame),btry,20,330);
	g_signal_connect(btry,"clicked",G_CALLBACK(bat_info),btry);

	sys=gtk_button_new_with_mnemonic("View _System Information");
	gtk_widget_set_size_request(sys,200,25);
	gtk_fixed_put(GTK_FIXED(frame),sys,20,360);
	g_signal_connect(sys,"clicked",G_CALLBACK(sys_info),sys);

	graphics=gtk_button_new_with_mnemonic("Change active graphics card");
	gtk_widget_set_size_request(graphics,200,25);
	gtk_fixed_put(GTK_FIXED(frame),graphics,300,330);
	g_signal_connect(graphics,"clicked",G_CALLBACK(switchgraphics),graphics);

	
	GtkWidget *boot;
	boot=gtk_button_new_with_mnemonic("_Shutdown/Reboot/Hibernate");
	gtk_widget_set_size_request(boot,200,25);
	gtk_fixed_put(GTK_FIXED(frame),boot,300,360);
	g_signal_connect(boot,"clicked",G_CALLBACK(shut_option),boot);	


	img1=gtk_image_new_from_file("pw.jpg");
	img2=gtk_image_new_from_file("full.png");
	img3=gtk_image_new_from_file("charge.png");
	img4=gtk_image_new_from_file("Battery0.png");
	img5=gtk_image_new_from_file("discharge.png");
	gtk_fixed_put(GTK_FIXED(frame),img1,20,20);

void updatestate(GtkWidget *stateicon)
{
	gint status;
	get_battery_status (&status);
	//printf("%d",status);
if(status==1){
	gtk_label_set_text(stateicon,"Battery is Charging");}
if(status==2){
	gtk_label_set_text(stateicon,"Battery is Discharging");}
if(status==3){
	gtk_label_set_text(stateicon,"Battery is Full.\nPlug our your charger");}
}
void updatestateimage(GtkWidget *stateimage)
{
	gint status;
	get_battery_status (&status);
if(status==1){
	stateimage=gtk_image_new_from_file("charge.png"); }
if(status==2){
	stateimage=gtk_image_new_from_file("discharge.png");}
if(status==3){
	stateimage=gtk_image_new_from_file("full.png");}
}
	

	
	GdkColor color;
	gdk_color_parse ("green", &color);
	
	GtkWidget *stateicon;
	stateicon=gtk_label_new("Battery state");
	gtk_widget_modify_fg(stateicon, GTK_STATE_NORMAL, &color); 
	gtk_fixed_put(GTK_FIXED(frame),stateicon,340,120);
	updatestate(stateicon);
	g_timeout_add_seconds (3,updatestate, (gpointer)stateicon);


GtkWidget *stateimage;
	gint status;
	get_battery_status (&status);
if(status==1){
	stateimage=gtk_image_new_from_file("charge.png"); }
if(status==2){
	stateimage=gtk_image_new_from_file("discharge.png");}
if(status==3){
	stateimage=gtk_image_new_from_file("full.png");}
	gtk_fixed_put(GTK_FIXED(frame),stateimage,360,70);
	updatestateimage(stateimage);
	g_timeout_add_seconds (3,updatestateimage, (gpointer)stateimage);

	GtkWidget *battinfo;
	
	system("acpi>temp/chargestate");
	char *content;
	gsize length;
	GError *error=NULL;
	g_file_get_contents("temp/chargestate",&content,&length,&error);	
	battinfo=gtk_label_new(content);
	//gtk_label_set_text(battinfo,string);
	gtk_fixed_put(GTK_FIXED(frame),battinfo,70,395);
	
	gtk_widget_modify_fg(battinfo, GTK_STATE_NORMAL, &color);
	GtkWidget *battpercent;
	battpercent=gtk_label_new("");
	gtk_widget_modify_fg(battpercent, GTK_STATE_NORMAL, &color);
	gtk_fixed_put(GTK_FIXED(frame),battpercent,340,140);
	GtkWidget *percent;
	percent=gtk_label_new("% charge available");
	gtk_fixed_put(GTK_FIXED(frame),percent,355,140);
	gtk_widget_modify_fg(percent, GTK_STATE_NORMAL, &color);

	updatetime(battinfo);
	updatepercent(battpercent);
	g_timeout_add_seconds (5,updatetime, (gpointer)battinfo);
	g_timeout_add_seconds (5,updatepercent, (gpointer)battpercent);
	
	

	GtkWidget *hsep2;
	hsep2=gtk_hseparator_new();
	gtk_widget_set_size_request(hsep2,200,2);
	gtk_fixed_put(GTK_FIXED(frame),hsep2,300,170);


	void get_date(GtkWidget *date)
	{
	system("date>temp/date");
	gchar *filename,*content;
	gsize bytes;
	GError *error = NULL;
	GtkWidget *cont;
	filename = g_build_filename ("temp", "date", NULL);
	g_file_get_contents (filename, &content, &bytes, &error);
	gtk_label_set_text(date,content);	
	}
	
		
	GtkWidget *date;
	date=gtk_label_new(NULL);
	gtk_fixed_put(GTK_FIXED(frame), date,330,420);
	gdk_color_parse ("white", &color);
	gtk_widget_modify_fg(date, GTK_STATE_NORMAL, &color);
	get_date(date);
	g_timeout_add_seconds (1,get_date, (gpointer)date);



	
	//brightness
    int i, j, screen, major, minor;
    double min, max, current;
    long current_test;
    char *dpy_name = NULL;
    Display *dpy;
    XRRScreenResources *resources;
    RROutput output;
    XRRPropertyInfo *info;
    Atom backlight;

   
    GtkWidget *scale;
    GObject *adjustment;
    GtkWidget *button;
    GtkWidget *box;

    callback_data data;

 

    /* set up display and check some X stuff */
    dpy = XOpenDisplay( dpy_name );
    if( !dpy )
    {
	fprintf( stderr, "Can't open display \"%s\"\n", XDisplayName( dpy_name ) );
	exit( 1 );
    }
    if( !XRRQueryVersion( dpy, &major, &minor ) )
    {
	fprintf( stderr, "RandR extension missing\n" );
	exit( 1 );
    }
    if( major < 1 || ( major == 1 && minor < 2 ) )
    {
	fprintf( stderr, "RandR version %d.%d too old\n", major, minor );
	exit( 1 );
    }

    backlight = XInternAtom( dpy, "BACKLIGHT", True );
    if( backlight == None )
    {
	fprintf( stderr, "No outputs have backlight property\n" );
	exit( 1 );
    }

    /* get current backlight value */
    for( screen = 0; screen < ScreenCount( dpy ); screen++ )
    {
	resources = XRRGetScreenResources( dpy, RootWindow( dpy, screen ) );

	if( !resources )
	    continue;

	for( j = 0; j < resources->noutput; j++ )
	{
	    output = resources->outputs[j];
	    current_test = backlight_get( backlight, dpy, output );
	    if( current_test != -1 )
	    {
		info = XRRQueryOutputProperty( dpy, output, backlight );
		if( info )
		{
		    if( info->range && info->num_values == 2 )
		    {
			min = info->values[0];
			max = info->values[1];
			current = ( double ) ( current_test * 100 / ( max - min ) );
			break;
		    }
		    XFree( info );
		}
	    }
	    XRRFreeScreenResources( resources );
	}
    }


   
    /* adjustment  */
    adjustment = gtk_adjustment_new( current, 0.0, 100.001, 0.001, 0.001, 0.001 );

    /* data is the thing we pass around in callbacks */
    data.adjustment = GTK_ADJUSTMENT( adjustment );
    data.display = dpy;
    data.backlight = backlight;
    /* box to store the scale and OK button */
   // box = gtk_vbox_new( FALSE, 0 );
    /* scale  */
     scale = gtk_hscale_new( GTK_ADJUSTMENT( adjustment ) );

    gtk_widget_set_size_request( GTK_WIDGET( scale ), 250, 40 );
    gtk_range_set_update_policy( GTK_RANGE( scale ), GTK_UPDATE_CONTINUOUS );
    gtk_scale_set_digits( GTK_SCALE( scale ), 2 );
    gtk_scale_set_draw_value( GTK_SCALE( scale ), TRUE );
    gtk_scale_set_value_pos( GTK_SCALE( scale ), GTK_POS_RIGHT );
    g_signal_connect( G_OBJECT( scale ), "value_changed", G_CALLBACK( set_callback ), &data );
  //  gtk_box_pack_start( GTK_BOX( box ), scale, TRUE, TRUE, 0 );
  
    
    gtk_fixed_put(GTK_FIXED(frame),scale,300,260);
  GtkWidget *brightness;
  brightness=gtk_label_new("Adjust the brightness level");
  gtk_fixed_put(GTK_FIXED(frame),brightness,300,240);
gtk_widget_modify_fg(brightness, GTK_STATE_NORMAL, &color);
	
	gdk_color_parse ("black", &color);
	gtk_widget_modify_bg(win, GTK_STATE_NORMAL, &color);
	
	hsep=gtk_hseparator_new();
	gtk_widget_set_size_request(hsep,220,2);
	gtk_fixed_put(GTK_FIXED(frame),hsep,10,170);
	hsep=gtk_hseparator_new();
	gtk_widget_set_size_request(hsep,590,2);
	gtk_fixed_put(GTK_FIXED(frame),hsep,10,390);
	hsep=gtk_hseparator_new();
	gtk_widget_set_size_request(hsep,590,2);
	gtk_fixed_put(GTK_FIXED(frame),hsep,10,420);

	gtk_container_set_border_width(GTK_CONTAINER(win), 10);
	gtk_container_add(GTK_CONTAINER(win), frame);
	
	g_signal_connect(win,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect (G_OBJECT (win), "delete_event", G_CALLBACK (state_event), NULL);
	g_signal_connect (G_OBJECT (win), "window-state-event", G_CALLBACK (state_event), win);
	gtk_window_set_deletable(win,TRUE);
	gtk_window_reshow_with_initial_size (win);
	gtk_widget_show_all(win);
	gtk_main();
	
}
	
