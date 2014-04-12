static void get_battery (gchar *udev_device_suffix, gboolean list_battery)
{
struct udev *udev_context;
struct udev_enumerate *udev_enumerate_context;
struct udev_list_entry *udev_devices_list, *udev_device_list_entry;
struct udev_device *udev_device;
gchar *udev_device_path;

udev_context = udev_new ();
if (!udev_context) {
g_fprintf (stderr, "Can't create udev context");
return;
}

udev_enumerate_context = udev_enumerate_new (udev_context);
if (!udev_enumerate_context) {
g_fprintf (stderr, "Can't create udev enumeration context");
return;
}

if (udev_enumerate_add_match_subsystem (udev_enumerate_context, "power_supply")) {
g_fprintf (stderr, "Can't add udev matching subsystem: power_supply");
return;
}

if (udev_enumerate_scan_devices (udev_enumerate_context)) {
g_fprintf (stderr, "Can't scan udev devices");
return;
}

udev_devices_list = udev_enumerate_get_list_entry (udev_enumerate_context);
udev_list_entry_foreach (udev_device_list_entry, udev_devices_list) {

udev_device_path = g_strdup (udev_list_entry_get_name (udev_device_list_entry));
udev_device = udev_device_new_from_syspath (udev_context, udev_device_path);

if (udev_device &&
!g_strcmp0 (udev_device_get_sysattr_value (udev_device, "type"), "Battery")) {
if (list_battery) {
gchar *battery_id = g_path_get_basename (udev_device_path);
g_fprintf (stdout, "battery id: %s\tbattery path: %s\n", battery_id, udev_device_path);
g_free (battery_id);
} else {
if (udev_device_suffix == NULL ||
g_str_has_suffix (udev_device_path, udev_device_suffix)) {

battery_path = udev_device_path;

udev_device_unref (udev_device);
udev_enumerate_unref (udev_enumerate_context);
udev_unref (udev_context);
return;
}
}
}

udev_device_unref (udev_device);
g_free (udev_device_path);
}

udev_enumerate_unref (udev_enumerate_context);
udev_unref (udev_context);

if (!list_battery)
g_fprintf (stderr, "No battery device found!\n");
}
