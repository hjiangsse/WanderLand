#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* threadFunA(void *vargp) {
  FILE *pf = (FILE *)vargp;

  fputs("This is the first message from thread1!\n", pf);
  fputs("This is the second message from thread1!\n", pf);
  fputs("This is the third message from thread1!\n", pf);
}

void* threadFunB(void *vargp) {
  FILE *pf = (FILE *)vargp;

  fputs("This is the first message from thread2!\n", pf);
  fputs("This is the second message from thread2!\n", pf);
  fputs("This is the third message from thread2!\n", pf);
}

int main() {
  FILE *out;
  out = fopen("output", "w");
  if(!out) {
    perror("fopen");
    exit(1);
  }

  pthread_t thread_idA;
  pthread_t thread_idB;
  pthread_create(&thread_idA, NULL, threadFunA, (void *)out);
  pthread_create(&thread_idB, NULL, threadFunB, (void *)out);
  pthread_join(thread_idA, NULL);
  pthread_join(thread_idB, NULL);
  fclose(out);
  exit(0);
}
