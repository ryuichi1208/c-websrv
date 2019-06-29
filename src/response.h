#include "main.h"

void http(int sockfd);
int send_msg(int fd, char *msg);

typedef struct {
    char *header;
    char *body;
    int http_status;
} resp;
