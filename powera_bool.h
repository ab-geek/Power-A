
static gboolean get_sysattr_string (gchar *attribute, gchar **value)
{
gchar *sysattr_filename;
gboolean sysattr_status;

g_return_val_if_fail (attribute != NULL, FALSE);
g_return_val_if_fail (value != NULL, FALSE);

sysattr_filename = g_build_filename (battery_path, attribute, NULL);
sysattr_status = g_file_get_contents (sysattr_filename, value, NULL, NULL);
g_free (sysattr_filename);

return sysattr_status;
}

static gboolean get_battery_present (gint *present)
{
gchar *sysattr_value;
gboolean sysattr_status;

g_return_val_if_fail (present != NULL, FALSE);

sysattr_status = get_sysattr_string ("present", &sysattr_value);
if (sysattr_status) {
*present = (g_str_has_prefix (sysattr_value, "1") ? 1 : 0);
g_free (sysattr_value);
}

return sysattr_status;
}

static gboolean get_battery_status (gint *status)
{
gchar *sysattr_value;
gboolean sysattr_status;

g_return_val_if_fail (status != NULL, FALSE);

sysattr_status = get_sysattr_string ("status", &sysattr_value);
if (sysattr_status) {
if (g_str_has_prefix (sysattr_value, "Charging"))
*status = CHARGING;
else if (g_str_has_prefix (sysattr_value, "Discharging"))
*status = DISCHARGING;
else if (g_str_has_prefix (sysattr_value, "Not charging"))
*status = NOT_CHARGING;
else if (g_str_has_prefix (sysattr_value, "Full"))
*status = CHARGED;
else
*status = UNKNOWN;

g_free (sysattr_value);
}

return sysattr_status;
}

static gboolean get_sysattr_double (gchar *attribute, gdouble *value)
{
gchar *sysattr_filename, *sysattr_content;
gboolean sysattr_status;

g_return_val_if_fail (attribute != NULL, FALSE);
g_return_val_if_fail (value != NULL, FALSE);

sysattr_filename = g_build_filename (battery_path, attribute, NULL);
sysattr_status = g_file_get_contents (sysattr_filename, &sysattr_content, NULL, NULL);
g_free (sysattr_filename);

if (sysattr_status) {
*value = g_ascii_strtod (sysattr_content, NULL);
if (errno || *value < 0.01) sysattr_status = FALSE;
g_free (sysattr_content);
}

return sysattr_status;
}

static gboolean get_battery_remaining_capacity (gdouble *capacity)
{
gboolean status;

g_return_val_if_fail (capacity != NULL, FALSE);

status = get_sysattr_double ("energy_now", capacity);
if (!status) status = get_sysattr_double ("charge_now", capacity);

return status;
}

static gboolean get_battery_full_capacity (gdouble *capacity)
{
static gboolean status = FALSE;
static gdouble fixed_capacity = 0.0;

g_return_val_if_fail (capacity != NULL, FALSE);

if (!status) {
status = get_sysattr_double ("energy_full", &fixed_capacity);
if (!status) status = get_sysattr_double ("charge_full", &fixed_capacity);
}

*capacity = fixed_capacity;

return status;
}

static gboolean get_battery_current_rate (gdouble *rate)
{
gboolean status;

g_return_val_if_fail (rate != NULL, FALSE);

status = get_sysattr_double ("power_now", rate);
if (!status) status = get_sysattr_double ("current_now", rate);

is_rate_possible = status;

return status;
}

