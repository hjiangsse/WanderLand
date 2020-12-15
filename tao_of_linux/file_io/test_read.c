#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>

int main()
{
    int fd;
    char buf[1024];
    int nr;
    
    memset(buf, 0x00, 1024);

    fd = open("./fifo", O_RDONLY | O_NONBLOCK);
    if(fd == -1)
    {
        puts("open fifo error!");
        return 1;
    }

start:
    nr = read(fd, buf, 1024);
    if(nr == -1)
    {
        if(errno == EINTR)
        {
            goto start;
        }
        
        if(errno == EAGAIN)
        {
            sleep(1);
            goto start;
        }

        puts("read fifo error");
        return 1;
    }

    if(nr == 0)
    {
        goto start;
    }

    printf("The number of byte: %d\n", nr);
    printf("The buf is: %s\n", buf);
    return 0;
    
    /*
    fd = open("./test.txt", O_RDONLY);
    if(fd == -1)
    {
        return 1;
    }

    const char *readerr = "read text from file error";
    nr = read(fd, buf, sizeof(buf));
    if(nr == -1)
    {
        write(3, readerr, strlen(readerr));
        return 1;
    }

    printf("buf: %s\n", buf);
    printf("just fetch out %d characters in the file\n", nr);
    */
}
