# DeviceControl

## Linux DeviceControl

## Program to enable/disable usb storage module.

-e: enable
-d: disable

## TODO:
* Criar função de elevação de privilégios ao invés de elevar a cada operação. Criar função para derrubar privilégios.
* Enable abre o arquivo mas não escreve.
* Corrigir o \n no nome de forma mais adequada.

To compile: gcc -Wall -Wextra -O2 -g -o snippet snippet.c 

Tested: Elementary OS, Ubuntu 18.04.
