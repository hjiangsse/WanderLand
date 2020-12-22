#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void foo() {
   printf("You are a foolish guy!\n");
}

void bar() {
   printf("Go to somebar, have a drink!\n");
}

void yar() {
   printf("Yar! you are a handsome boy!\n");
}

int main() {
    atexit(foo);
    atexit(bar);
    atexit(yar);

    printf("You can at most define %ld exit functions in this system!\n",
           sysconf(_SC_ATEXIT_MAX));
    
    exit(0);
}
