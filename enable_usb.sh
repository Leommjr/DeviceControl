#!/bin/bash

## Habilitando o USB-STORAGE

NAME="$(whoami)"

# Teste SU
if [ "$NAME" != "root" ]
then
	echo Necessario ser root do sistema
	exit 1
else
	# Movendo usb-storage para o local correto
	mv /root/usb-storage.ko /lib/modules/$(uname -r)/kernel/drivers/usb/storage
	if [ $? -eq 0 ]
	then
		sed -i 's/blacklist usb-storage//g' /etc/modprobe.d/blacklist.conf
		exit 0
	else
		clear
		echo Ja esta habilitado
		exit 2
	fi
fi
