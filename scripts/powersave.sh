#!/bin/bash

#run as root
if [ ! $( id -u ) -eq 0 ]; then
	exec gksu "${0}" # call this script as root
	exit ${?}  # since we're 'execing' above, we wont reach this exit
               # unless something goes .
fi               
echo OFF > /sys/kernel/debug/vgaswitcheroo/switch
/dev/sdb { spindown_time = 60 } > /etc/hdparm.conf
/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_min_freq > /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq
rfkill block wifi
echo 5 > /proc/sys/vm/laptop_mode
echo 40 > /proc/sys/vm/dirty_ratio
echo 10 > /proc/sys/vm/dirty_background_ratio
echo 1500 > /proc/sys/vm/dirty_writeback_centisecs
echo min_power > /sys/class/scsi_host/host0/link_power_management_policy
hdparm -B 1 -S 4 /dev/sda

echo 1 > /sys/module/snd_hda_intel/parameters/power_save

echo 1 > /sys/devices/system/cpu/sched_mc_power_savings
echo 0 > /proc/sys/kernel/nmi_watchdog
echo 1 > /sys/devices/system/cpu/sched_smt_power_savings

###  Radeon Driver power management
echo low > /sys/class/drm/card0/device/power_profile


#automatic devie management
### Automatic device power management management
for fdevice in /sys/bus/{pci,spi,i2c}/devices/*/power/control; do
  echo auto > $fdevice
done

for sdevice in /sys/class/scsi_host/host*/link_power_management_policy; do
  echo min_power > $sdevice
done

for usb in /sys/bus/usb/devices/*/power/autosuspend; do
  echo 1 > $usb;
done

sed "s/\(GRUB_CMDLINE_LINUX=\)\"\"/\1\"acpi_osi=Linux acpi_backlight=vendor\"/" /etc/default/grub -i 
sudo update-grub

