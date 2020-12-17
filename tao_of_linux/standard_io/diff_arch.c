#include <stdio.h>

int main() {
  FILE *in, *out;
  struct private {
    char name[100];
    unsigned long booty;
    unsigned int beard_len;
  } p, blackbeard = {"hjiang heng", 950, 48};

  out = fopen("data", "w");
  if(!out) {
    perror("fopen");
    return 1;
  }

  if(!fwrite(&blackbeard, sizeof(struct private), 1, out)) {
    perror("fwrite");
    return 1;
  }

  return 0;
}
