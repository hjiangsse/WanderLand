#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd;
    char buf[256] = {0};

    if(argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDWR);
    if(fd < 0) 
    {
        printf("open %s file Failed!", argv[1]);
        printf("error no is: %d\n", errno);
        printf("error discription is: %s\n", strerror(errno));
    }

    unsigned long word;
    ssize_t nr;

    nr = read(fd, &word, sizeof(unsigned long));
    if (nr == -1)
    {
        printf("read file error!\n");
        printf("error discription is: %s\n", strerror(errno));
    }

    printf("The number of bytes readed: %d\n", nr);
    printf("The word is: %lu\n", word);
    return 0;
}
