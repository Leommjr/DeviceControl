/**
 * @file device_control.c
 *
 * @brief Programa para desabilitar/habilitar os dispositivos usb de me	* mória no kernel linux
 *
 * @author Leonardo Marinho de Melo Junior
 * @date 08/11/2019
 * @bugs Nenhum atualmente
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/proot.h"

int disableUsb(char* caminho)
{
	size_t tam = 0;
	char root[] = "/root/usb-storage.ko";
	char buffer[BUFSIZ] = { '\0'};
	FILE* in = fopenRoot(caminho, "rb");
	FILE* out = fopenRoot(root, "wb");
	if( in == NULL){
		puts("USB já foi desabilitado!");
		in = out = 0;
		return 1;
	}else if(out == NULL){
		//fprintf(stderr, "ERRO ao acessar /root");
		in = out = 0;
		return 2;
	}else{
		while((tam = fread(buffer, BUFSIZ, 1, in))> 0){
			fwrite(buffer, BUFSIZ, 1, out);
		}
		fcloseRoot(in);
		fcloseRoot(out);
		if(removeRoot(caminho)){
			puts("Desabilitado com sucesso\n");
			return 0;
		}else{
			return 2;
		}
	}

}

int enableUsb(char* caminho)
{
	size_t tam = 0;
	char root[] = "/root/usb-storage.ko" ;
	char buffer[BUFSIZ] = { '\0'};
	FILE* in = fopenRoot(root, "rb");
	FILE* out = fopenRoot(caminho, "wb");
	if( in == NULL){
		puts("USB já foi habilitado!");
		in = out = 0;
		return 1;
	}else if(out == NULL){
		//fprintf(stderr, "ERRO ao acessar /root");
		in = out = 0;
		return 2;
	}else{
		while((tam = fread(buffer, BUFSIZ, 1, in))> 0){
			fwrite(buffer, BUFSIZ, 1, out);
		}
		fcloseRoot(in);
		fcloseRoot(out);
		if(removeRoot(caminho)){
			puts("Habilitado com sucesso\n");
			return 0;
		}else{
			return 2;
		}
	}



}
char* createFolder(char* uname, char* dir)
{
       	const char dir1[] = "/lib/modules/" ;
	const char dir2[] = "/kernel/drivers/usb/storage/usb-storage.ko" ;
	strcat(dir, dir1);
	strcat(dir, uname);
	strcat(dir, dir2);
	return dir;
}

int main(int argc, char *argv[]){
	char path[40];
	char dir[100];
	char ch = '\n';
	char* ret;
	FILE* fp;
	int result;
	if(argc < 2){
		puts("******* Argumentos não foram inseridos *******\n\
	-d: Disable USB -e: Enable USB\n");
		return 1;
	}	
	fp = popen("uname -r", "r");
	if(!fp){
		fprintf(stderr, "Popen error!\n");
		return -1;
	}
	while(fgets(path,40,fp)!=NULL)
		ret = strchr(path, ch);
		*ret = '\0';
	if(pclose(fp) == -1){
		fprintf(stderr, "PCLOSE error!\n");
		return -1;
	}else{
		if(strcmp(argv[1],"-d") == 0){
			result = disableUsb(createFolder(path,dir));
		}
       		else if(strcmp(argv[1],"-e") == 0){
			result = enableUsb(createFolder(path,dir));
		}
		else{
			puts("Argumento incorreto!\n -d: Disable USB -e: Enable USB");
			return 1;
		}
	}
	printf("%d\n", result);
	return 0;
}

