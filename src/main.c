#include "main.h"
#include "response.h"
#include "route.h"

void http(int sockfd);
int send_msg(int fd, char *msg);

opt_p* getopts(int argc, char **argv, opt_p *opts) {
    int i, opt;
    opterr = 0;
    opts = malloc(sizeof(opt_p));
    opts->port = 0;

    while ((opt = getopt(argc, argv, "fgp:")) != -1) {
        switch (opt) {
        case 'f':
           continue;
        case 'g':
            break;
        case 'p':
            opts->port = atoi(optarg);
           break;
        default:
           break;
        }
    }
    return opts;
}

int main(int argc, char **argv) {
    int sockfd;
    int new_sockfd;
    int writer_len;
    struct sockaddr_in reader_addr;
    struct sockaddr_in writer_addr;
    opt_p *opt;

    if(!(opt = getopts(argc, argv, opt))) {
        fprintf(stderr, "invalid option¥n");
        exit(1);
    }

    memset(&reader_addr, 0, sizeof(reader_addr));
    memset(&writer_addr, 0, sizeof(writer_addr));

    reader_addr.sin_family      = AF_INET;
    reader_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (!opt->port) {
        reader_addr.sin_port        = htons(HTTP_TCP_PORT);
    }
    else {
        reader_addr.sin_port        = htons(opt->port);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "error: socket()\n");
        return 1;
    }

    if (bind(sockfd, (struct sockaddr *)&reader_addr, sizeof(reader_addr)) < 0) {
        fprintf(stderr, "error: bind()\n");
        fprintf(stderr, "%s\n", strerror(errno));
        close(sockfd);
        return 1;
    }

    if (listen(sockfd, 5) < 0) {
        fprintf(stderr, "error: listen()\n");
        close(sockfd);
        return 1;
    }

    while(1) {
        if ((new_sockfd = accept(sockfd, (struct sockaddr *)&writer_addr, (socklen_t *)&writer_len)) < 0) {
            fprintf(stderr, "error: accepting a socket.\n");
            break;
        }
        else {
            http(new_sockfd);
            close(new_sockfd);
        }
    }

    close(sockfd);
}
