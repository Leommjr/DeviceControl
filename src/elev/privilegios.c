#include "proot.h"
#include <errno.h>

FILE* fopenRoot(char* caminho, char* modo)
{
	uid_t ruid, euid, suid;
	gid_t rgid, egid, sgid;
	int uerr, gerr;
	FILE* fp;
	if(getresuid(&ruid, &euid, &suid) == -1){
		fprintf(stderr, "Nao foi possivel obter a identidade do usuario: %m.\n");
		return NULL;
	}
	if (getresgid(&rgid, &egid, &sgid) == -1){
		fprintf(stderr, "Nao foi possivel obter a identidade de grupo: %m.\n");
		return NULL;
	}
	if(ruid != (uid_t)TARGET_UID && ruid < (uid_t)MIN_UID){
		fprintf(stderr, "Usuario invalido. \n");
		return NULL;
	}
	if(rgid != (gid_t)TARGET_UID && rgid < (gid_t)MIN_GID){
		fprintf(stderr, "Grupo invalido. \n");
		return NULL;
	}
	//Target User
	if(seteuid((uid_t)TARGET_UID)== -1){
		fprintf(stderr, "Nao possui privilegios de usuario  suficientes.\n");
		return NULL;
	}
	//Target Group
	if(setegid((gid_t)TARGET_GID) ==-1){
		fprintf(stderr, "Nao possui privilegios de grupo suficientes.\n");
		return NULL;
	}

	fp = fopen(caminho, modo);
	if(fp == NULL){
		//fprintf(stderr, "Não foi possível abrir arquivo %s: %m.\n", caminho);
		return NULL;
	}
	//Removendo privilegios
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
		return NULL;
	}
	return fp;
}
//sudo install -o root -g root -m u=rxs,g=rx,o=x -t /usr/local/bin prog
int fcloseRoot(FILE* fp){
	uid_t ruid, euid, suid;
	gid_t rgid, egid, sgid;
	int uerr, gerr;
	if(getresuid(&ruid, &euid, &suid) == -1){
		fprintf(stderr, "Nao foi possivel obter a identidade do usuario: %m.\n");
		return 1;
	}
	if (getresgid(&rgid, &egid, &sgid) == -1){
		fprintf(stderr, "Nao foi possivel obter a identidade de grupo: %m.\n");
		return 1;
	}
	if(ruid != (uid_t)TARGET_UID && ruid < (uid_t)MIN_UID){
		fprintf(stderr, "Usuario invalido. \n");
		return 1;
	}
		if(ruid != (gid_t)TARGET_UID && rgid < (gid_t)MIN_GID){
		fprintf(stderr, "Grupo invalido. \n");
		return 1;
	}
	//Target User
	if(seteuid((uid_t)TARGET_UID)== -1){
		fprintf(stderr, "Nao possui privilegios de usuario  suficientes.\n");
		return 1;
	}
	//Target Group
	if(setegid((gid_t)TARGET_GID) ==-1){
		fprintf(stderr, "Nao possui privilegios de grupo suficientes.\n");
		return 1;
	}
	fclose(fp);
	//Removendo privilegios
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
		return 1;
	}
	return 0;

}
int removeRoot(char* caminho)
{
	uid_t ruid, euid, suid;
	gid_t rgid, egid, sgid;
	int uerr, gerr, flag;
	if(getresuid(&ruid, &euid, &suid) == -1){
		fprintf(stderr, "Nao foi possivel obter a identidade do usuario: %m.\n");
		return NULL;
	}
	if (getresgid(&rgid, &egid, &sgid) == -1){
		fprintf(stderr, "Nao foi possivel obter a identidade de grupo: %m.\n");
		return NULL;
	}
	if(ruid != (uid_t)TARGET_UID && ruid < (uid_t)MIN_UID){
		fprintf(stderr, "Usuario invalido. \n");
		return NULL;
	}
	if(rgid != (gid_t)TARGET_UID && rgid < (gid_t)MIN_GID){
		fprintf(stderr, "Grupo invalido. \n");
		return NULL;
	}
	//Target User
	if(seteuid((uid_t)TARGET_UID)== -1){
		fprintf(stderr, "Nao possui privilegios de usuario  suficientes.\n");
		return NULL;
	}
	//Target Group
	if(setegid((gid_t)TARGET_GID) ==-1){
		fprintf(stderr, "Nao possui privilegios de grupo suficientes.\n");
		return NULL;
	}
	flag = remove(caminho);
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
		return 1;
	}
	return flag;	
}

