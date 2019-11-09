#!/bin/bash

## Desabilitando o USB-STORAGE

NAME="$(whoami)"
DIR="$(pwd)"
if [ "$NAME" != "root" ]
then
 	echo Necessario ser root do sistema
	exit 1
else
	# Movendo usb-storage para /root
	mv /lib/modules/$(uname -r)/kernel/drivers/usb/storage/usb-storage.ko /root
	if [ $? -eq 0 ]
	then

		echo "blacklist usb-storage" >> /etc/modprobe.d/blacklist.conf	
		exit 0
	
	else
		clear
		echo Ja foi feita a desabilitacao
		exit 2
	fi

fi

