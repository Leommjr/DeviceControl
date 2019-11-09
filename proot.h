#ifndef PROOT_H
#define PROOT_H
#endif
#define _GNU_SOURCE
//man7.org
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#ifndef TARGET_UID
#define TARGET_UID 0
#endif

#ifndef TARGET_GID
#define TARGET_GID 0
#endif

#ifndef MIN_UID
#define MIN_UID 500
#endif

#ifndef MIN_GID
#define MIN_GID 500
#endif


FILE* fopenRoot(char* caminho, char* modo);
int fcloseRoot(FILE* fp);
int removeRoot(char* caminho);
