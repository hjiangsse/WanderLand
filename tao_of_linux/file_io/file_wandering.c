#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd;
    int fd_create;
    int fd_use_creat;
    ssize_t nr;
    const char *buff = "This is the end of the world";

    fd = open("./test.txt", O_WRONLY | O_TRUNC);
    if (fd == -1) {
        exit(1);
    }

    nr = write(fd, buff, strlen(buff));
    if(nr == -1)
    {
        exit(1);
    }

    fd_create = open("./create.txt", O_CREAT | O_EXCL | O_RDWR, 0664);
    if(fd_create == -1)
    {
        exit(1);
    }

    nr = write(fd_create, buff, strlen(buff));
    if(nr == -1)
    {
        exit(1);
    }

    fd_use_creat = creat("./real_create.txt", 0644);
    if(fd_use_creat == -1)
    {
        exit(1);
    }

    nr = write(fd_use_creat, buff, strlen(buff));
    if(nr == -1)
    {
        exit(1);
    }

    return 0;
}
