#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define MAXPENDING 5
#define HTTP_TCP_PORT 80
#define HTTPS_TCP_PORT 443
#define BUFLEN 1024
#define _XOPEN_SOURCE 600
#define _POSIX_C_SOURCE 200112L
#undef _REENTRANT
#define _GNU_SOURCE

#ifndef NET_ATM_SIGNALING_H
#define NET_ATM_SIGNALING_H

#ifndef __MAIN
typedef struct {
    int port;
    int addr;
} opt_p;

typedef struct {
        char method[16];
        char path[128];
        char version[16];
} HEAD_DATA;

struct ThreadArgs
{
    int clntSock;                      /* Socket descriptor for client */
};
#endif
#define __MAIN 1
