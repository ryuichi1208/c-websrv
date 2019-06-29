#include "main.h"
#include "response.h"


// プロトタイプ
void http(int sockfd);
int send_msg(int fd, char *msg);

int main(int argc, char **argv) {

    int sockfd;
    int new_sockfd;
    int writer_len;
    struct sockaddr_in reader_addr;
    struct sockaddr_in writer_addr;

    memset(&reader_addr, 0, sizeof(reader_addr));
    memset(&writer_addr, 0, sizeof(writer_addr));

    reader_addr.sin_family      = AF_INET;
    reader_addr.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY = 0.0.0.0 = 誰からでも待ち受け
    reader_addr.sin_port        = htons(HTTP_TCP_PORT);

    // 待ち受け用にソケットを開く
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "error: socket()\n");
        return 1;
    }

    // 待ち受け用としてソケットをバインド
    if (bind(sockfd, (struct sockaddr *)&reader_addr, sizeof(reader_addr)) < 0) {
        fprintf(stderr, "error: bind()\n");
        fprintf(stderr, "%s", strerror(errno));
        close(sockfd);
        return 1;
    }

    // 待ち受け用ソケットで待ち受け（接続待ち・リッスン）
    if (listen(sockfd, 5) < 0) {
        fprintf(stderr, "error: listen()\n");
        close(sockfd);
        return 1;
    }

    // 接続を待ち続ける
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
