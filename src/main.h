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

#define HTTP_TCP_PORT 80
#define HTTPS_TCP_PORT 443

#ifndef __MAIN
typedef struct {
    int port;
    int addr;
} opt_p;
#endif
#define __MAIN 1

