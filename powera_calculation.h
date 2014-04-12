static gboolean get_battery_charge_info (gint *percentage, gint *time)
{
gdouble full_capacity, remaining_capacity, current_rate;

if (!get_battery_full_capacity (&full_capacity) ||
!get_battery_remaining_capacity (&remaining_capacity))
return FALSE;

*percentage = (gint)fmin(floor(remaining_capacity / full_capacity * 100.0), 100.0);

if (!is_rate_possible) {
if (!get_battery_estimated_time (remaining_capacity, full_capacity, time))
*time = ERROR_TIME;

return TRUE;
}

if (!get_battery_current_rate (&current_rate))
return FALSE;

*time = (gint)(((full_capacity - remaining_capacity) / current_rate) * 60.0);

return TRUE;
}

static gboolean get_battery_remaining_charge_info (gint *percentage, gint *time)
{
gdouble full_capacity, remaining_capacity, current_rate;

if (!get_battery_full_capacity (&full_capacity) ||
!get_battery_remaining_capacity (&remaining_capacity))
return FALSE;

*percentage = (gint)fmin(floor(remaining_capacity / full_capacity * 100.0), 100.0);

if (!is_rate_possible) {
if (!get_battery_estimated_time (remaining_capacity, 0, time))
*time = ERROR_TIME;

return TRUE;
}

if (!get_battery_current_rate (&current_rate))
return FALSE;

*time = (gint)((remaining_capacity / current_rate) * 60.0);

return TRUE;
}

/* y = 0 if discharging or battery_full_capacity */
static gboolean get_battery_estimated_time (gdouble remaining_capacity, gdouble y, gint *time)
{
gdouble m = 0;
gdouble calc_sec = 0;

if (prev_remaining_capacity == -1)
prev_remaining_capacity = remaining_capacity;

*time = prev_time;
secs_last_time_change += update_interval;

/* y=mx+b...x=(y-b)/m solving for when y = full_charge or 0
* y2=remaining_capacity y1=prev_remain run=secs_last_time_change b=prev_remain
*/

if (prev_remaining_capacity != remaining_capacity) {
m = (remaining_capacity - prev_remaining_capacity) / (gdouble)(secs_last_time_change);
calc_sec = ((y - prev_remaining_capacity) / m) - (secs_last_time_change);
*time = (gint)((calc_sec) / (gdouble)60);

prev_remaining_capacity = remaining_capacity;
prev_time = *time;
secs_last_time_change = 0;
}

return TRUE;
}

static void reset_estimated_vars (void)
{
prev_remaining_capacity = -1;
prev_time = ERROR_TIME;
secs_last_time_change = 0;
}

