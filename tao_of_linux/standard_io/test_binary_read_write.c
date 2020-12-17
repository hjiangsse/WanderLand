#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <ctype.h>

void write_file();
void read_file();

int main() {
  read_file();
}

void read_file() {
  FILE *pf = fopen("./binary_file", "r+");
  if(!pf) {
    perror("open file error");
  }

  int arr[4] = {0};
  int i;
  int nr = 0;
  nr = fread(arr, sizeof(arr[0]), sizeof(arr)/sizeof(arr[0]), pf);
  if(nr == 0) {
    perror("fread error");
  }
  for(i = 0; i < 4; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  fclose(pf);
}  

void write_file() {
  FILE *pf = fopen("./binary_file", "w+");
  if(!pf) {
    perror("open file error");
  }

  int arr[] = {1,2,3};
  fwrite(arr, sizeof(arr[0]), sizeof(arr)/sizeof(arr[0]), pf);

  fclose(pf);
}
