#include "main.h"

#define _OE_SOCKETS
#include <sys/types.h>
#include <sys/socket.h>

char *routing(char *uri);

struct __sockaddr_in {
     unsigned char  sin_len;
     unsigned char  sin_family;
     unsigned short sin_port;
     struct in_addr sin_addr;
     unsigned char  sin_zero[8];

};
