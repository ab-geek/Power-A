#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

typedef struct
{
    Display *display;
    GtkAdjustment *adjustment;
    Atom backlight;
} callback_data;

static long backlight_get( Atom backlight, Display * dpy, RROutput output )
{
    unsigned long nitems;
    unsigned long bytes_after;
    unsigned char *prop;
    Atom actual_type;
    int actual_format;
    long value;

    if( XRRGetOutputProperty( dpy, output, backlight,
			      0, 4, False, False, None, &actual_type, &actual_format, &nitems, &bytes_after, &prop ) != Success )
	return -1;
    if( actual_type != XA_INTEGER || nitems != 1 || actual_format != 32 )
	value = -1;
    else
	value = *( ( long * ) prop );
    XFree( prop );
    return value;
}

static void backlight_set( Atom backlight, Display * dpy, RROutput output, long value )
{
    XRRChangeOutputProperty( dpy, output, backlight, XA_INTEGER, 32, PropModeReplace, ( unsigned char * ) &value, 1 );
}

static void set_callback( GtkWidget * widget, callback_data * data )
{
    double value = ( data->adjustment )->value;
    Display *dpy = data->display;
    Atom backlight = data->backlight;

    int j, screen;
    double min, max, set;

    XRRScreenResources *resources;
    RROutput output;
    XRRPropertyInfo *info;

    for( screen = 0; screen < ScreenCount( dpy ); screen++ )
    {
	resources = XRRGetScreenResources( dpy, RootWindow( dpy, screen ) );

	if( !resources )
	    continue;

	for( j = 0; j < resources->noutput; j++ )
	{
	    output = resources->outputs[j];
	    if( backlight_get( backlight, dpy, output ) != -1 )
	    {
		info = XRRQueryOutputProperty( dpy, output, backlight );

		if( info )
		{
		    if( info->range && info->num_values == 2 )
		    {
			min = info->values[0];
			max = info->values[1];
			set = min + value * ( max - min ) / 100;
			if( set > max )
			    set = max;
			if( set < min )
			    set = min;
			backlight_set( backlight, dpy, output, ( long ) set );
			XFlush( dpy );
		    }
		    XFree( info );
		}
	    }
	}
	XRRFreeScreenResources( resources );
    }
}

