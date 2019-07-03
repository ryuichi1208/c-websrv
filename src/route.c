#include "route.h"

/*
struct file *sock_alloc_file(struct socket *sock, int flags, const char *dname)
{
	struct file *file;

	if (!dname)
		dname = sock->sk ? sock->sk->sk_prot_creator->name : "";

	file = alloc_file_pseudo(SOCK_INODE(sock), sock_mnt, dname,
				O_RDWR | (flags & O_NONBLOCK),
				&socket_file_ops);
	if (IS_ERR(file)) {
		sock_release(sock);
		return file;
	}

	sock->file = file;
	file->private_data = sock;
	return file;
}
*/

char *routing(char *uri)
{
    char *ret;

    if (strlen(uri) == 1) {
        ret = "index.html";
        return ret;
    }

    ret = uri + 1;
    return ret;
}

void cutcrLf( char *str )
{
        char *p;

        if     ((p = strchr(str, '\r')) != NULL) *p = '\0';
        else if((p = strchr(str, '\n')) != NULL) *p = '\0';
}

void gethtml( FILE *sock_fp, HEAD_DATA *data )
{
        FILE *fp;
        char *buf;
        struct stat st;

        if(stat(data->path + 1, &st) < 0){
                fprintf(stderr, "404error\n");
                exit(1);
        }

    if((buf = (char *)calloc(st.st_size, sizeof(char))) == NULL){
          fprintf(stderr, "calloc\n");
          exit(1);
    }

        fprintf(sock_fp, "%s 200 OK\r\n", data->version);
        fprintf(sock_fp, "Server:sample\r\n");
        fprintf(sock_fp, "Content-Type:text/html\r\n");
        fprintf(sock_fp, "Content-Length:%d\r\n", (int)st.st_size);
        fprintf(sock_fp, "\r\n");

        if((fp = fopen(data->path + 1, "r")) == NULL){
                fprintf(stderr, "fopen\n");
                exit(1);
        }

    fread(buf, 1, st.st_size, fp);
    fwrite(buf, 1, st.st_size, sock_fp);

        free(buf);
        fclose(fp);

}
