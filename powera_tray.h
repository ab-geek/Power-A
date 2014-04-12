
static GtkStatusIcon* create_tray_icon (void)
{
GtkStatusIcon *tray_icon = gtk_status_icon_new ();

gtk_status_icon_set_tooltip_text(tray_icon, "Power A : Gnome Power Management ");
gtk_status_icon_set_visible (tray_icon, TRUE);

g_signal_connect(G_OBJECT(tray_icon),"activate",G_CALLBACK(left_click_cb),tray_icon);
g_signal_connect(G_OBJECT(tray_icon),"popup-menu",G_CALLBACK(right_click_cb),NULL);

update_tray_icon (tray_icon);
g_timeout_add_seconds (update_interval, (GSourceFunc)update_tray_icon, (gpointer)tray_icon);

return tray_icon;
}

static gboolean update_tray_icon (GtkStatusIcon *tray_icon)
{
static gboolean lock = FALSE;

if (!lock) {
lock = TRUE;
update_tray_icon_state (tray_icon);
lock = FALSE;
} else
g_fprintf (stderr, "Tray update locked!?");

return TRUE;
}

static void update_tray_icon_state (GtkStatusIcon *tray_icon)
{
static gint battery_state = -1;
static gint battery_low = -1;
gint battery_present, battery_status;
gint percentage, time;
gchar *time_string;

if (!battery_path)
return;

/* first check if battery is present... */
if (!get_battery_present (&battery_present))
return;

if (!battery_present) {
if (battery_state != MISSING) {
battery_state = MISSING;
notify_message ("No battery present!");
}

set_tooltip_and_icon (tray_icon, MISSING, 0, "");
return;
}

/* ...and then check its status */
if (!get_battery_status (&battery_status))
return;

switch (battery_status) {
case CHARGING:
if (!get_battery_charge_info (&percentage, &time))
return;

time_string = get_time_string (time);

if (battery_state != CHARGING) {
reset_estimated_vars ();

battery_state = CHARGING;
notify_battery_information (CHARGING, percentage, time_string);
}

set_tooltip_and_icon (tray_icon, CHARGING, percentage, time_string);
break;

case DISCHARGING:
if (!get_battery_remaining_charge_info (&percentage, &time))
return;

time_string = get_time_string (time);

if (battery_state != DISCHARGING) {
reset_estimated_vars();

battery_state = DISCHARGING;
battery_low = 0;
notify_battery_information (DISCHARGING, percentage, time_string);
}

if (!battery_low && percentage < 20) {
battery_state = DISCHARGING;
battery_low = 1;
notify_battery_information (LOW_POWER, percentage, time_string);

}

set_tooltip_and_icon(tray_icon, DISCHARGING, percentage, time_string);
break;

case CHARGED:
percentage = 100;

if (battery_state != CHARGED) {
battery_state = CHARGED;
notify_battery_information (CHARGED, percentage, "");
}

set_tooltip_and_icon (tray_icon, CHARGED, percentage, "");
break;

case NOT_CHARGING:
if (battery_state != NOT_CHARGING) {
battery_state = NOT_CHARGING;
notify_message ("Battery isn't charging!");
}
break;
}
}
