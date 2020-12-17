#include <stdio.h>
#include <stdlib.h>
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

Foo *genFooStruct() {
  char buffer[] = "This is the end of the world";
  
  Foo *foo = (Foo *)malloc(sizeof(Foo));
  if(foo != NULL) {
    memcpy(foo->name, buffer, sizeof(buffer));
    foo->age = 30;
    return foo;
  }
  
  return NULL;
}

Bar *genBarStruct() {
  char buffer[] = "Bar the world";
  
  Bar *bar = (Bar *)malloc(sizeof(Bar));
  if(bar != NULL) {
    memcpy(bar->name, buffer, sizeof(buffer));
    bar->age = 30;
    return bar;
  }
  
  return NULL;
}

Yar *genYarStruct() {
  char buffer[] = "Yarhaah";
  
  Yar *yar = (Yar *)malloc(sizeof(Yar));
  if(yar != NULL) {
    memcpy(yar->name, buffer, sizeof(buffer));
    yar->age = 30;
    return yar;
  }
  
  return NULL;
}

int main() {
  struct iovec iov[3];
  ssize_t nr;
  int fd, i;

  fd = open("foobaryar.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if(fd == -1) {
    perror("fopen");
    return 1;
  }

  Foo *foo = genFooStruct();
  Bar *bar = genBarStruct();
  Yar *yar = genYarStruct();
  
  iov[0].iov_base = foo;
  iov[0].iov_len = sizeof(Foo);
  iov[1].iov_base = bar;
  iov[1].iov_len = sizeof(Bar);
  iov[2].iov_base = yar;
  iov[2].iov_len = sizeof(Yar);

  nr = writev(fd, iov, 3);
  if(nr == -1) {
    perror("writev");
    return 1;
  }

  printf("wrote %d bytes\n", nr);

  return 0;
}
