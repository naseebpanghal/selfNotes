#!/bin/bash

ifaceList=`ls /sys/class/net`
devFound=false

for i in $ifaceList 
do
	iFaceName_2char=${i:0:2}
	if [ "$iFaceName_2char" = "wl" ] 
	then
		devFile="/sys/class/net/$i/device/interface"
		if [ -e $devFile ] 
		then
			devName=`cat $devFile`
			if [ "$devName" = "WUSB6300 V2" ]
			then
				devFound=true
				echo $i > /home/Collab8/config/wifidirectsupported.txt
			fi
		fi
	fi
done

if [ "$devFound" = false ]
then
	rm -f /home/Collab8/config/wifidirectsupported.txt
fi
