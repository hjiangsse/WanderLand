#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>

#define MAX_WRITE_TIME 1000000

int main()
{
    const char *msg = "This is the end of the world!\n";
    int fd;
    int nw;
    int fs;

    fd = creat("./nosync_write.txt", 0644);
    if(fd == -1)
    {
        perror("Open file failed!");
        return 1;
    }

    int i;
    for(i = 0; i < MAX_WRITE_TIME; i++)
    {
        nw = write(fd, msg, strlen(msg));
        if(nw == -1)
        {
            perror("Write file error!");
            return 1;
        }
        
    }

    //fsync
    fs = fsync(fd);
    if(fs == -1)
        perror("fsync error");
    
    return 0;
}
