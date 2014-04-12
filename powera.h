static void main_window(void);
static void get_options (int argc, char **argv);
static void get_battery (gchar *udev_device_suffix, gboolean list_battery);

static gboolean get_sysattr_string (gchar *attribute, gchar **value);
static gboolean get_battery_present (gint *present);
static gboolean get_battery_status (gint *status);


static gboolean get_sysattr_double (gchar *attribute, gdouble *value);
static gboolean get_battery_remaining_capacity (gdouble *capacity);
static gboolean get_battery_full_capacity (gdouble *capacity);
static gboolean get_battery_current_rate (gdouble *rate);

static gboolean get_battery_charge_info (gint *percentage, gint *time);
static gboolean get_battery_remaining_charge_info (gint *percentage, gint *time);
static gboolean get_battery_estimated_time (gdouble remaining_capacity, gdouble y, gint *time);
static void reset_estimated_vars (void);

static GtkStatusIcon* create_tray_icon (void);
static gboolean update_tray_icon (GtkStatusIcon *tray_icon);
static void update_tray_icon_state (GtkStatusIcon *tray_icon);
static void create_power_notify();
static void notify_message (gchar *message);
static void notify_battery_information (gint state, gint percentage, gchar *time);
static void set_tooltip_and_icon (GtkStatusIcon *tray_icon, gint state, gint percentage, gchar *time);
static gchar* get_time_string (gint minutes);
static gchar* get_icon_name (gint state, gint percentage);

#define STR_LTH 256
#define Max_length  256
#define ERROR_TIME -1

#define HAS_STANDARD_ICON_TYPE gtk_icon_theme_has_icon (gtk_icon_theme_get_default (), "battery-full")
#define HAS_NOTIFICATION_ICON_TYPE gtk_icon_theme_has_icon (gtk_icon_theme_get_default (), "notification-battery-100")
#define HAS_SYMBOLIC_ICON_TYPE gtk_icon_theme_has_icon (gtk_icon_theme_get_default (), "battery-full-symbolic")

#define DEFAULT_INTERVAL 3

enum {
UNKNOWN_ICON = 0,
BATTERY_ICON,
BATTERY_ICON_SYMBOLIC,
BATTERY_ICON_NOTIFICATION
};

enum {
MISSING = 0,
CHARGING,
DISCHARGING,
NOT_CHARGING,
CHARGED,
UNKNOWN,
LOW_POWER
};

static gchar *battery_path = NULL;
static gint icon_type = UNKNOWN_ICON;
static gint update_interval = DEFAULT_INTERVAL;

int is_rate_possible = TRUE;
gdouble prev_remaining_capacity = -1;
gint prev_time = ERROR_TIME;
glong secs_last_time_change = 0;



