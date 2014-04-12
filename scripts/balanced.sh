#!/bin/bash

#run as root
if [ ! $( id -u ) -eq 0 ]; then
	exec gksu "${0}" # call this script as root
	exit ${?}  # since we're 'execing' above, we wont reach this exit
               # unless something goes .
fi               
echo ON > /sys/kernel/debug/vgaswitcheroo/switch
echo 0 > /proc/sys/vm/laptop_mode

for sdevice in /sys/class/scsi_host/host*/link_power_management_policy; do
  echo max_performance > $sdevice
done


