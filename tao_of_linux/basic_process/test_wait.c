#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int status;
    pid_t pid;

    pid = fork();
    if(pid == -1)
        perror("fork");

    /* the child */
    if(!pid) {
       const char *args[] = {"less", "./test.txt", NULL};
       int ret;

       ret = execv("/usr/bin/less", args);
       if(ret == -1) {
           perror("execv");
	   exit(1);
       }
    }

    /* wait for the status of child process */
    /*
    pid = wait(&status);
    if(pid == -1) {
        perror("wait");
    }
    */
    
    pid = waitpid(pid, &status, 0);
    if(pid == -1) {
        perror("waitpid");
    }

    printf("pid of child process: %d\n", pid);

    if(WIFEXITED(status)) {
      printf("Normal termination with exit status=%d\n",
             WEXITSTATUS(status));
    }

    if(WIFSIGNALED(status)) {
      printf("Killed by signal=%d%s\n",
             WTERMSIG(status),
             WCOREDUMP(status)? "(dumped core)": "");
    }
}
