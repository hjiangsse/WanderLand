#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define LINE_LEN 20

int main() {
  int fd;
  char buf[LINE_LEN + 1];
  
  fd = open("mmap.txt", O_RDWR);
  if(fd < 0) {
    perror("open");
    return 1;
  }

  void *p;
  p = mmap(0, LINE_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (p == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  /* modify the mapped memory */
  memset(buf, 0x00, LINE_LEN + 1);
  memcpy(buf, p, LINE_LEN);
  printf("buf: %s\n", buf);

  memcpy(p, "That", 4);

  if(msync(p, LINE_LEN, MS_SYNC) == -1) {
    perror("msync");
  }

  /* get the page size of current system */
  printf("The page size: %d\n", getpagesize());

  /* unmap the mapped memory */
  if(munmap(p, LINE_LEN) == -1)
    perror("munmap");

  close(fd);
  return 0;
}
