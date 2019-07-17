#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define PROGRAM_NAME "setnc"

#define MAX_THREADS 10
#define FILE_NAME_MAX 32
#define NAME_SPACES 3
#define SLEEP_TIME 1

const char *namespaces[] = {
    "mnt",
    "pid",
    "uts"
};

void func()
{
    int ret;
    char *cmd = "ls -lart";

    sleep(SLEEP_TIME);
    ret = system(cmd);

    fprintf(stdout, "%d\n", WIFEXITED(ret));
}

void exit_err(int err, const char *msg) {
    fprintf(stderr, "%s(%d).\n", msg, err);
    fprintf(stderr, "Usage : %s [PID] [THREAD_NUM\n", PROGRAM_NAME);
    exit(1);
}

int create_and_exec_threads(int tnum)
{
    int i = 0;
    pthread_t *thread;
    thread = malloc(sizeof(pthread_t) * tnum);

    // Create and wait for threads
    for (i = 0; i < tnum; i++){
        pthread_create((thread+i),NULL,(void *)func,NULL);
        pthread_join(*(thread+i),NULL);
    }

    return 0;
}

int set_namespace(int pid)
{
    int fd[NAME_SPACES];
    int i;
    char files[NAME_SPACES][FILE_NAME_MAX];

    for (i = 0; i < sizeof(namespaces)/sizeof(char *); i++) {
        sprintf(*(files+i), "/proc/%d/ns/%s", pid, *(namespaces+i));

        // open proc files and get fd
        fd[i] = open(*(files+i), O_RDONLY);
        if (fd[i] == -1)
            exit_err(errno, "Can't Open Files");

        // Join namespace
        if (setns(fd[i], 0) == -1)
            exit_err(errno, "setns failed");
    }

    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 3)
        exit_err(errno, "Invalid Argments");

    int pid = strtol(argv[1], NULL, 10);
    if (errno)
        exit_err(errno, "Invalid Argment: Argument is only numbers");

    int tnum = strtol(argv[2], NULL, 10);
    if (errno)
        exit_err(errno, "Invalid Argment: Argument is only numbers");

    set_namespace(pid);

    create_and_exec_threads(tnum);
}
