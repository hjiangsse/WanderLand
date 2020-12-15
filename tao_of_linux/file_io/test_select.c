#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>

#define TIMEOUT 3

int main()
{
    struct timeval tv;
    fd_set readfds;
    int ret;
    int fd;

    fd = open("./fifo_read", O_RDONLY | O_NONBLOCK);
    if(fd == -1)
    {
        perror("open error");
        return 1;
    }
    
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;

    ret = select(fd + 1,
                 &readfds,
                 NULL,
                 NULL,
                 &tv);
    if(ret == -1)
    {
        perror("select");
        return 1;
    }
    else if(!ret)
    {
        printf("%d seconds elapsed.\n", TIMEOUT);
        return 0;
    }

    /* Is the fd ready to be read? */
    if(FD_ISSET(fd, &readfds))
    {
        char buf[1024];
        int len;

        len = read(fd, buf, 1024);
        if(len == -1)
        {
            perror("read error");
            return 1;
        }

        if(len)
        {
            buf[len] = '\0';
            printf("read: %s\n", buf);
        }

        return 0;
    }
    
    return 0;
}
