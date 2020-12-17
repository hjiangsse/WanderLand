#include <stdio.h>

int main() {
  FILE *pf;
  pf = fopen("test.txt", "r");
  if(!pf) {
    perror("fopen");
    return 1;
  }

  int c;
  while((c = fgetc(pf)) != '|') {
    printf("%c", c);
    fseek(pf, 1, SEEK_CUR);
  }
  puts("\n");

  printf("position: %d\n", ftell(pf));
  rewind(pf);
  while((c = fgetc(pf)) != '|') {
    printf("%c", c);
  }
  puts("\n");

  if(!feof(pf)) {
    printf("arrive at eof!\n");
  }

  return 0;
}
