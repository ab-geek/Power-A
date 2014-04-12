#include "pmodes.h"
void state_event(GtkWidget *window,GdkEventWindowState *event)
{
	if(event->changed_mask == GDK_WINDOW_STATE_ICONIFIED && (event->new_window_state == GDK_WINDOW_STATE_ICONIFIED || event->new_window_state == (GDK_WINDOW_STATE_ICONIFIED | GDK_WINDOW_STATE_MAXIMIZED)))
    {
        gtk_widget_hide(window);
        //gtk_status_icon_set_visible(GTK_STATUS_ICON(trayIcon), TRUE);
    }
	
}
GdkPixbuf *icon(const gchar *filename)
{
	GdkPixbuf *pixbuf;
	GError *error=NULL;
	pixbuf=gdk_pixbuf_new_from_file(filename,&error);
	if(!pixbuf)
	{
		fprintf(stderr,"%s\n",error->message);
		g_error_free(error);
	}
	return pixbuf;
}
void sens(GtkWidget* button,gpointer first_button)
{
	gtk_widget_set_sensitive(GTK_WIDGET(first_button),1);
}

void destroy(GtkWidget* button,gpointer sub_win)
{
	gtk_widget_destroy(sub_win);
}
//for graphics
void graphics_info(GtkWidget* graphics,gpointer first_button)
{
	GtkWidget *window,*frame,*button,*label;
	gtk_widget_set_sensitive(GTK_WIDGET(graphics),0);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(window),1);
	//gtk_widget_set_size_request(window,200,200);
	gtk_window_set_title(GTK_WINDOW(window),"Graphics Information");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), 0);
	frame=gtk_fixed_new();
	system(" lspci | grep VGA >info/graphicsinfo");
	char *content;gsize length;GError *error=NULL;
	g_file_get_contents("info/graphicsinfo",&content,&length,&error);	
	label=gtk_label_new(content);
	gtk_fixed_put(GTK_FIXED(frame),label,10,40);	
	button=gtk_button_new_with_mnemonic("_Exit");
	gtk_widget_set_size_request(button,100,20);
	gtk_fixed_put(GTK_FIXED(frame),button,150,160);
	g_signal_connect(button,"clicked",G_CALLBACK(sens),first_button);
	g_signal_connect(button,"clicked",G_CALLBACK(destroy),window);
	gtk_container_add(GTK_CONTAINER(window),frame);
	gtk_widget_show_all(window);
}
//for audio
void audio_info(GtkWidget* audio,gpointer first_button)
{
	GtkWidget *window,*frame,*button,*label;
	gtk_widget_set_sensitive(GTK_WIDGET(audio),1);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(window),1);
	//gtk_widget_set_size_request(window,200,200);
	gtk_window_set_title(GTK_WINDOW(window),"Audio Information");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), 0);
	frame=gtk_fixed_new();
	system(" aplay --list-devices >info/audioinfo");
	char *content;gsize length;GError *error=NULL;
	g_file_get_contents("info/audioinfo",&content,&length,&error);	
	label=gtk_label_new(content);
	gtk_fixed_put(GTK_FIXED(frame),label,10,40);	
	button=gtk_button_new_with_mnemonic("_Exit");
	gtk_widget_set_size_request(button,100,20);
	gtk_fixed_put(GTK_FIXED(frame),button,150,220);
	g_signal_connect(button,"clicked",G_CALLBACK(sens),first_button);
	g_signal_connect(button,"clicked",G_CALLBACK(destroy),window);
	gtk_container_add(GTK_CONTAINER(window),frame);
	gtk_widget_show_all(window);
}
//for software
void software_info(GtkWidget* software,gpointer first_button)
{	GtkWidget *window,*frame,*button,*label;
	gtk_widget_set_sensitive(GTK_WIDGET(software),1);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(window),1);
	//gtk_widget_set_size_request(window,200,200);
	gtk_window_set_title(GTK_WINDOW(window),"Software Information");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), 0);
	frame=gtk_fixed_new();
	system(" cat /etc/issue & uname -a>info/softwareinfo");
	char *content;gsize length;GError *error=NULL;
	g_file_get_contents("info/softwareinfo",&content,&length,&error);	
	label=gtk_label_new(content);
	gtk_fixed_put(GTK_FIXED(frame),label,10,40);	
	button=gtk_button_new_with_mnemonic("_Exit");
	gtk_widget_set_size_request(button,100,20);
	gtk_fixed_put(GTK_FIXED(frame),button,150,160);
	g_signal_connect(button,"clicked",G_CALLBACK(sens),first_button);
	g_signal_connect(button,"clicked",G_CALLBACK(destroy),window);
	gtk_container_add(GTK_CONTAINER(window),frame);
	gtk_widget_show_all(window);
}
//for network
void network_info(GtkWidget* network,gpointer first_button)
{	GtkWidget *window,*frame,*button,*label;
	gtk_widget_set_sensitive(GTK_WIDGET(network),1);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(window),1);
	//gtk_widget_set_size_request(window,200,200);
	gtk_window_set_title(GTK_WINDOW(window),"Network Information");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), 0);
	frame=gtk_fixed_new();
	system("ifconfig>info/networkinfo");
	char *content;gsize length;GError *error=NULL;
	g_file_get_contents("info/networkinfo",&content,&length,&error);	
	label=gtk_label_new(content);
	gtk_fixed_put(GTK_FIXED(frame),label,10,40);	
	button=gtk_button_new_with_mnemonic("_Exit");
	gtk_widget_set_size_request(button,100,20);
	gtk_fixed_put(GTK_FIXED(frame),button,150,480);
	g_signal_connect(button,"clicked",G_CALLBACK(sens),first_button);
	g_signal_connect(button,"clicked",G_CALLBACK(destroy),window);
	gtk_container_add(GTK_CONTAINER(window),frame);
	gtk_widget_show_all(window);
}
//for processor
void processor_info(GtkWidget* processor,gpointer first_button)
{	GtkWidget *window,*frame,*button,*label;
	gtk_widget_set_sensitive(GTK_WIDGET(processor),1);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(window),1);
	//gtk_widget_set_size_request(window,200,800);
	gtk_window_set_title(GTK_WINDOW(window),"Processor Information");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), 0);
	frame=gtk_fixed_new();
	system(" cat /proc/cpuinfo >info/processorinfo");
	char *content;gsize length;GError *error=NULL;
	g_file_get_contents("info/processorinfo",&content,&length,&error);	
	label=gtk_label_new(content);
	gtk_fixed_put(GTK_FIXED(frame),label,10,40);	
	button=gtk_button_new_with_mnemonic("_Exit");
	gtk_widget_set_size_request(button,100,20);
	gtk_fixed_put(GTK_FIXED(frame),button,150,160);
	g_signal_connect(button,"clicked",G_CALLBACK(sens),first_button);
	g_signal_connect(button,"clicked",G_CALLBACK(destroy),window);
	gtk_container_add(GTK_CONTAINER(window),frame);
	gtk_widget_show_all(window);
}
//for memory

void memory_info(GtkWidget* memory,gpointer first_button)
{	GtkWidget *window,*frame,*button,*label;
	gtk_widget_set_sensitive(GTK_WIDGET(memory),1);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(window),1);
	//gtk_widget_set_size_request(window,200,200);
	gtk_window_set_title(GTK_WINDOW(window),"Memory Information");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), 0);
	frame=gtk_fixed_new();
	system("cat /proc/meminfo >info/memoryinfo");
	char *content;gsize length;GError *error=NULL;
	g_file_get_contents("info/memoryinfo",&content,&length,&error);	
	label=gtk_label_new(content);
	gtk_fixed_put(GTK_FIXED(frame),label,10,40);	
	button=gtk_button_new_with_mnemonic("_Exit");
	gtk_widget_set_size_request(button,100,20);
	gtk_fixed_put(GTK_FIXED(frame),button,150,160);
	g_signal_connect(button,"clicked",G_CALLBACK(sens),first_button);
	g_signal_connect(button,"clicked",G_CALLBACK(destroy),window);
	gtk_container_add(GTK_CONTAINER(window),frame);
	gtk_widget_show_all(window);
}
//for hard disk
void hardisk_info(GtkWidget* hardisk,gpointer first_button)
{	GtkWidget *window,*frame,*button,*label;
	gtk_widget_set_sensitive(GTK_WIDGET(hardisk),1);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(window),1);
	//gtk_widget_set_size_request(window,200,200);
	gtk_window_set_title(GTK_WINDOW(window),"Hard Disk Information");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), 0);
	frame=gtk_fixed_new();
	system(" df -H >info/hardiskinfo");
	char *content;gsize length;GError *error=NULL;
	g_file_get_contents("info/hardiskinfo",&content,&length,&error);	
	label=gtk_label_new(content);
	gtk_fixed_put(GTK_FIXED(frame),label,10,40);	
	button=gtk_button_new_with_mnemonic("_Exit");
	gtk_widget_set_size_request(button,100,20);
	gtk_fixed_put(GTK_FIXED(frame),button,150,250);
	g_signal_connect(button,"clicked",G_CALLBACK(sens),first_button);
	g_signal_connect(button,"clicked",G_CALLBACK(destroy),window);
	gtk_container_add(GTK_CONTAINER(window),frame);
	gtk_widget_show_all(window);
}
//for usb
void usb_info(GtkWidget* usb,gpointer first_button)
{	GtkWidget *window,*frame,*button,*label;
	gtk_widget_set_sensitive(GTK_WIDGET(usb),1);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(window),1);
	//gtk_widget_set_size_request(window,200,200);
	gtk_window_set_title(GTK_WINDOW(window),"USB Information");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), 0);
	frame=gtk_fixed_new();
	system(" lsusb >info/usbinfo");
	char *content;gsize length;GError *error=NULL;
	g_file_get_contents("info/usbinfo",&content,&length,&error);	
	label=gtk_label_new(content);
	gtk_fixed_put(GTK_FIXED(frame),label,10,40);	
	button=gtk_button_new_with_mnemonic("_Exit");
	gtk_widget_set_size_request(button,100,20);
	gtk_fixed_put(GTK_FIXED(frame),button,150,220);
	g_signal_connect(button,"clicked",G_CALLBACK(sens),first_button);
	g_signal_connect(button,"clicked",G_CALLBACK(destroy),window);
	gtk_container_add(GTK_CONTAINER(window),frame);
	gtk_widget_show_all(window);
}

void sys_info(GtkWidget* btry,gpointer first_button)
{
	GtkWidget *window,*frame,*topic,*button,*graphics,*audio,*software,*network,*processor,*memory,*hardisk,*usb;

	gtk_widget_set_sensitive(GTK_WIDGET(btry),0);

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(window),1);
	gtk_widget_set_size_request(window,400,280);
	gtk_window_set_title(GTK_WINDOW(window),"System Information");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), 0);
	frame=gtk_fixed_new();
	
	topic=gtk_label_new("What information would you like to view ?");
	gtk_fixed_put(GTK_FIXED(frame),topic,10,10);

	graphics=gtk_button_new_with_label("Graphics card info");
	g_signal_connect(graphics,"clicked",G_CALLBACK(graphics_info),graphics);
	gtk_fixed_put(GTK_FIXED(frame),graphics,10,50);

	audio=gtk_button_new_with_label("Audio info");
	g_signal_connect(audio,"clicked",G_CALLBACK(audio_info),audio);
	gtk_fixed_put(GTK_FIXED(frame),audio,180,50);

	software=gtk_button_new_with_label("Software info");
	g_signal_connect(software,"clicked",G_CALLBACK(software_info),software);
	gtk_fixed_put(GTK_FIXED(frame),software,10,90);

	network=gtk_button_new_with_label("Network card info");
	g_signal_connect(network,"clicked",G_CALLBACK(network_info),network);
	gtk_fixed_put(GTK_FIXED(frame),network,180,90);

	processor=gtk_button_new_with_label("Processor info");
	g_signal_connect(processor,"clicked",G_CALLBACK(processor_info),processor);
	gtk_fixed_put(GTK_FIXED(frame),processor,10,130);

	memory=gtk_button_new_with_label("Memory info");
	g_signal_connect(memory,"clicked",G_CALLBACK(memory_info),memory);
	gtk_fixed_put(GTK_FIXED(frame),memory,180,130);

	hardisk=gtk_button_new_with_label("Hard disk info");
	g_signal_connect(hardisk,"clicked",G_CALLBACK(hardisk_info),hardisk);
	gtk_fixed_put(GTK_FIXED(frame),hardisk,10,170);

	usb=gtk_button_new_with_label("USB info");
	g_signal_connect(usb,"clicked",G_CALLBACK(usb_info),usb);
	gtk_fixed_put(GTK_FIXED(frame),usb,180,170);

	button=gtk_button_new_with_mnemonic("_Exit");
	gtk_widget_set_size_request(button,50,20);
	gtk_fixed_put(GTK_FIXED(frame),button,100,250);
	g_signal_connect(button,"clicked",G_CALLBACK(sens),first_button);
	g_signal_connect(button,"clicked",G_CALLBACK(destroy),window);
	gtk_container_add(GTK_CONTAINER(window),frame);
	gtk_widget_show_all(window);
}

void bat_info(GtkWidget* btry,gpointer first_button)
{
	GtkWidget *window,*frame,*button,*label;
	gtk_widget_set_sensitive(GTK_WIDGET(btry),0);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(window),1);
	gtk_widget_set_size_request(window,400,400);
	gtk_window_set_title(GTK_WINDOW(window),"Battery Information");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), 0);
	frame=gtk_fixed_new();
	system(" cat /proc/acpi/battery/BAT0/info>temp/battinfo");
	char *content;
	gsize length;
	GError *error=NULL;
	g_file_get_contents("temp/battinfo",&content,&length,&error);	
	label=gtk_label_new(content);

	gtk_fixed_put(GTK_FIXED(frame),label,10,40);	
	
	button=gtk_button_new_with_mnemonic("_OK");
	gtk_widget_set_size_request(button,100,20);
	gtk_fixed_put(GTK_FIXED(frame),button,280,360);
	g_signal_connect(button,"clicked",G_CALLBACK(sens),first_button);
	g_signal_connect(button,"clicked",G_CALLBACK(destroy),window);

	//for image

	GtkWidget *img2,*img3,*img5;
	img2=gtk_image_new_from_file("full.png");
	img3=gtk_image_new_from_file("charge.png");
	img5=gtk_image_new_from_file("discharge.png");
	
	GtkWidget *battinfo;
	system("acpi>temp/chargestate");
	 FILE *fp;
    char string[100];
	char st;
	
   fp = fopen("temp/chargestate", "r");
    while(!feof(fp)) {
       fgets(string, 199, fp);   }
      fclose(fp);
	st=string[11];
	printf("%c",st);
	
	if(st=='D') 
{	gtk_fixed_put(GTK_FIXED(frame),img5,250,250);
		GtkWidget *discharg;
	  discharg=gtk_label_new("Battery is Discharging");
	gtk_fixed_put(GTK_FIXED(frame),discharg,250,290);
}
	else if(st=='C') 
	{ gtk_fixed_put(GTK_FIXED(frame),img3,250,250);
		GtkWidget *charg;
	  charg=gtk_label_new("Battery is charging");
	gtk_fixed_put(GTK_FIXED(frame),charg,250,290);
}
	else if(st=='F') 
	{ gtk_fixed_put(GTK_FIXED(frame),img2,250,250);
		GtkWidget *charg;
	  charg=gtk_label_new("Battery is Full \nUnplug your charger");
	gtk_fixed_put(GTK_FIXED(frame),charg,250,290);
}

	gtk_container_add(GTK_CONTAINER(window),frame);
	gtk_widget_show_all(window);
}

void pre_option(GtkWidget* button,gpointer first_button)
{
	GtkWidget *window,*b1,*b2,*b3,*b4,*b5,*frame;

	gtk_widget_set_sensitive(GTK_WIDGET(first_button),0);

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(window),1);
	gtk_widget_set_size_request(window,240,200);
	gtk_window_set_title(GTK_WINDOW(window),"Choose Power Mode");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), 0);
	frame=gtk_fixed_new();
	
	b1=gtk_button_new_with_mnemonic("_Power Saver");
	gtk_widget_set_size_request(b1,200,25);
	gtk_fixed_put(GTK_FIXED(frame),b1,20,20);
	g_signal_connect(b1,"clicked",G_CALLBACK(power_saver),NULL);
 	
	b2=gtk_button_new_with_mnemonic("_Balanced");
	gtk_widget_set_size_request(b2,200,25);
	gtk_fixed_put(GTK_FIXED(frame),b2,20,50);
	g_signal_connect(b2,"clicked",G_CALLBACK(balanced),NULL);
	
	
	b3=gtk_button_new_with_mnemonic("_High Performance");
	gtk_widget_set_size_request(b3,200,25);
	gtk_fixed_put(GTK_FIXED(frame),b3,20,80);
	g_signal_connect(b3,"clicked",G_CALLBACK(high_performance),NULL);

	

	b5=gtk_button_new_with_mnemonic("_OK");
	gtk_widget_set_size_request(b5,200,25);
	gtk_fixed_put(GTK_FIXED(frame),b5,20,160);
	g_signal_connect(b5,"clicked",G_CALLBACK(sens),first_button);
	g_signal_connect(b5,"clicked",G_CALLBACK(destroy),window);

	gtk_container_add(GTK_CONTAINER(window),frame);
	gtk_widget_show_all(window);
}
void shutdown()
{
	system("shutdown -h now");
}
void reboot()
{
	system("shutdown -r now");
}
void sleeep()
{
	system("/etc/acpi/sleep.sh force");
}
void hibernate()
{
	system("/etc/acpi/hibernate.sh");
}
void shut_option(GtkWidget* button,gpointer first_button)
{
	GtkWidget *window,*b1,*b2,*b3,*b4,*b5,*frame;

	gtk_widget_set_sensitive(GTK_WIDGET(first_button),0);

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(window),1);
	gtk_widget_set_size_request(window,240,200);
	gtk_window_set_title(GTK_WINDOW(window),"Choose an Option");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), 0);
	frame=gtk_fixed_new();
	
	b1=gtk_button_new_with_mnemonic("_Shutdown");
	gtk_widget_set_size_request(b1,200,20);
	gtk_fixed_put(GTK_FIXED(frame),b1,20,20);
	g_signal_connect(b1,"clicked",G_CALLBACK(shutdown),NULL);
 	
	b2=gtk_button_new_with_mnemonic("_Reboot");
	gtk_widget_set_size_request(b2,200,20);
	gtk_fixed_put(GTK_FIXED(frame),b2,20,50);
	g_signal_connect(b2,"clicked",G_CALLBACK(reboot),NULL);
	
	
	b3=gtk_button_new_with_mnemonic("_Sleep");
	gtk_widget_set_size_request(b3,200,20);
	gtk_fixed_put(GTK_FIXED(frame),b3,20,80);
	g_signal_connect(b3,"clicked",G_CALLBACK(sleeep),NULL);

	b4=gtk_button_new_with_mnemonic("_Hibernate");
	gtk_widget_set_size_request(b4,200,20);
	gtk_fixed_put(GTK_FIXED(frame),b4,20,110);
	g_signal_connect(b4,"clicked",G_CALLBACK(hibernate),NULL);

	b5=gtk_button_new_with_mnemonic("_OK");
	gtk_widget_set_size_request(b5,200,20);
	gtk_fixed_put(GTK_FIXED(frame),b5,20,160);
	g_signal_connect(b5,"clicked",G_CALLBACK(sens),first_button);
	g_signal_connect(b5,"clicked",G_CALLBACK(destroy),window);

	gtk_container_add(GTK_CONTAINER(window),frame);
	gtk_widget_show_all(window);
}


