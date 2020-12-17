#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10

char buf[1024];

int main() {
  /*create epoll instance*/
  int epfd;
  epfd = epoll_create1(0);
  if(epfd < 0) {
    perror("epoll_create1");
    return 1;
  }

  /*control epoll */
  int fd;
  fd = open("channel", O_RDONLY);
  if(fd < 0) {
    perror("open");
    return 1;
  }

  struct epoll_event event;
  int ret;

  event.data.fd = fd;      //file discriptor you want to watch
  event.events = EPOLLIN;  //check if data coming

  ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
  if(ret) {
    perror("epoll_ctl");
    return 1;
  }

  /*wait something to happen*/
  struct epoll_event *events;
  int nr_events, i;

  events = malloc(sizeof(struct epoll_event) * MAX_EVENTS);
  if(!events) {
    perror("malloc");
    return 1;
  }

  nr_events = epoll_wait(epfd, events, MAX_EVENTS, -1);
  if(nr_events < 0) {
    perror("epoll_wait");
    free(events);
    return 1;
  }

  for(i = 0; i < nr_events; i++) {
    printf("event=%ld on fd=%d\n",
           events[i].events,
           events[i].data.fd);
    memset(buf, 0x00, 1024);
    int nr = read(events[i].data.fd, buf, 1024);
    if(nr < 0) {
      perror("read");
      return 1;
    }
    printf("buf: %s\n", buf);
  }

  free(events);
  
  return 0;
}
