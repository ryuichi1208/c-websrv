#include "response.h"

void http(int sockfd) {
    int len;
    int read_fd;
    char buf[1024];
    char method[16];
    char uri_addr[256];
    char http_ver[64];
    char *uri_file;

    if (read(sockfd, buf, 1024) <= 0) {
        fprintf(stderr, "error: reading a request.\n");
    }
    else {
        sscanf(buf, "%s %s %s", method, uri_addr, http_ver);

        if (strcmp(method, "GET") != 0) {
            send_msg(sockfd, "501 Not implemented.");
            close(read_fd);
        }

        uri_file = uri_addr + 1;
        fprintf(stdout, "uri_file:%s",uri_file);

        if ((read_fd = open("../index.html", O_RDONLY, 0666)) == -1) {
             send_msg(sockfd, "404 Not Found");
             close(read_fd);
        }

        send_msg(sockfd, "HTTP/1.0 200 OK\r\n");
        send_msg(sockfd, "Content-Type: text/html\r\n");
        send_msg(sockfd, "\r\n");

        while((len = read(read_fd, buf, 1024)) > 0) {
            if (write(sockfd, buf, len) != len) {
                fprintf(stderr, "error: writing a response.\n");
                break;
            }
        }

        close(read_fd);
    }
}

int send_msg(int fd, char *msg) {
    int len;
    len = strlen(msg);

    if (write(fd, msg, len) != len) {
        fprintf(stderr, "error: writing.");
    }

    return len;
}
