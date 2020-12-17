#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/uio.h>

typedef struct _Foo {
  char name[100];
  int  age;
}Foo;

typedef struct _Bar {
  char name[20];
  int  age;
}Bar;

typedef struct _Yar {
  char name[50];
  int  age;
}Yar;

int main() {
  Foo foo;
  Bar bar;
  Yar yar;

  struct iovec iov[3];
  ssize_t nr;
  int fd, i;

  fd = open("foobaryar.txt", O_RDONLY);
  if(fd == -1) {
    perror("open");
    return 1;
  }

  iov[0].iov_base = &foo;
  iov[0].iov_len = sizeof(Foo);
  iov[1].iov_base = &bar;
  iov[1].iov_len = sizeof(Bar);
  iov[2].iov_base = &yar;
  iov[2].iov_len = sizeof(Yar);

  nr = readv(fd, iov, 3);
  if(nr == -1) {
    perror("readv");
    return 1;
  }

  printf("foo.name = %s\n", foo.name);
  printf("foo.age = %d\n", foo.age);
  printf("bar.name = %s\n", bar.name);
  printf("bar.age = %d\n", bar.age);
  printf("yar.name = %s\n", yar.name);
  printf("yar.age = %d\n", yar.age);
   
  return 0;
}

void no_use() {
  /*
  char foo[48], bar[51], yar[48];
  
  memset(foo, 0x00, 48);
  memset(bar, 0x00, 51);
  memset(yar, 0x00, 48);
  
  struct iovec iov[3];
  ssize_t nr;
  int fd, i;

  fd = open("bucc.txt", O_RDONLY);
  if(fd == -1) {
    perror("open");
    return 1;
  }

  iov[0].iov_base = foo;
  iov[0].iov_len = sizeof(foo)-1;
  iov[1].iov_base = bar;
  iov[1].iov_len = sizeof(bar)-1;
  iov[2].iov_base = yar;
  iov[2].iov_len = sizeof(yar)-1;

  nr = readv(fd, iov, 3);
  if(nr == -1) {
    perror("readv");
    return 1;
  }

  printf("foo: %s", foo);
  printf("bar: %s", bar);
  printf("yar: %s", yar);
  */
}
