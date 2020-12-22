#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    pid = fork();
    if(pid == -1)
        perror("fork");

    /* the child */
    if(!pid) {
       const char *args[] = {"cat", "./test.txt", NULL};
       int ret;

       ret = execv("/bin/cat", args);
       if(ret == -1) {
           perror("execv");
	   exit(1);
       }
    }

    /* in the parent process */
    sleep(5);
    printf("Bye!");
}
