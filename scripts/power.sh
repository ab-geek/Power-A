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
