#include "../../lib/proot.h"
#include <errno.h>

#ifndef ERROR
#define ERROR -1
#endif

uid_t ruid, euid, suid;
gid_t rgid, egid, sgid;
int uerr, gerr;

int remoRoot(void)
{
	gerr = 0;
	if(setresgid(rgid, rgid, rgid) == -1){
		gerr = errno;
		if(!gerr)
			gerr = EINVAL;
	}
	uerr = 0;
	if(setresuid(ruid, ruid, ruid) == -1){
		uerr = errno;
		if(!uerr)
			uerr = EINVAL;
	}
	if(uerr || gerr){
		if(uerr)
			fprintf(stderr, "Nao foi possivel diminuir os privilegios do user: %s.\n", strerror(uerr));
		if(gerr)
			fprintf(stderr, "Nao foi possivel diminuir os privilegios do grupo: %s.\n", strerror(gerr));
		return ERROR;
	}
	return 0;
}

int elevRoot(void)
{
	if(getresuid(&ruid, &euid, &suid) == -1){
		fprintf(stderr, "Nao foi possivel obter a identidade do usuario: %m.\n");
		return ERROR;
	}
	if (getresgid(&rgid, &egid, &sgid) == -1){
		fprintf(stderr, "Nao foi possivel obter a identidade de grupo: %m.\n");
		return ERROR;
	}
	if(ruid != (uid_t)TARGET_UID && ruid < (uid_t)MIN_UID){
		fprintf(stderr, "Usuario invalido. \n");
		return ERROR;
	}
	if(rgid != (gid_t)TARGET_UID && rgid < (gid_t)MIN_GID){
		fprintf(stderr, "Grupo invalido. \n");
		return ERROR;
	}
	//Target User
	if(seteuid((uid_t)TARGET_UID)== -1){
		fprintf(stderr, "Nao possui privilegios de usuario  suficientes.\n");
		return ERROR;
	}
	//Target Group
	if(setegid((gid_t)TARGET_GID) ==-1){
		fprintf(stderr, "Nao possui privilegios de grupo suficientes.\n");
		return ERROR;
	}
	return 0;
}

FILE* fopenRoot(char* caminho, char* modo)
{
   FILE* fp;
   if(elevRoot() == 0){	   
	fp = fopen(caminho, modo);
	if(fp == NULL){
		//fprintf(stderr, "Não foi possível abrir arquivo %s: %m.\n", caminho);
		return NULL;
	}
	if(remoRoot()!= 0) return NULL;
   }
	return fp;
}
//sudo install -o root -g root -m u=rxs,g=rx,o=x -t /usr/local/bin prog
int fcloseRoot(FILE* fp){
   if(elevRoot()==0){
	fclose(fp);
	if(remoRoot != 0) return ERROR;
   }
   return 0;

}
int removeRoot(char* caminho)
{
   if(elevRoot() == 0){
	flag = remove(caminho);
	if(remoRoot() != 0) return ERROR;
   }
	return flag;	
}

