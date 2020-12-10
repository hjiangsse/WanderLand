#include <stdio.h>
#include "bitmap.h"

#define MAX_RECORD_NUM 10000000
#define FIRST_SCAN 7000000
#define SECOND_SCAN 3000000

int main(int argc, char **argv)
{
  word_t* bitmap = alloc_bit(FIRST_SCAN);

  FILE *fp;
  FILE *fo;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int i;

  fp = fopen("./shuffle.txt", "r");
  if (fp == NULL)
  {
    exit(EXIT_FAILURE);
  }

  fo = fopen("shuffle.bitmap.twoscan.txt", "w+");
  if (fo == NULL)
  {
    exit(EXIT_FAILURE);
  }
  
  while((read = getline(&line, &len, fp)) != -1)
  {
    if(atoi(line) <= FIRST_SCAN)
    {
      set_bit(bitmap, atoi(line));
    }
  }
  
  for(i = 1; i <= FIRST_SCAN; i++)
  {
    if(get_bit(bitmap, i))
    {
      fprintf(fo,"%d\n", i);
    }
  }

  rewind(fp);
  free_map(bitmap);
  bitmap = alloc_bit(SECOND_SCAN);
 
  while((read = getline(&line, &len, fp)) != -1)
  {
    if(atoi(line) > FIRST_SCAN)
    {
      set_bit(bitmap, atoi(line) - FIRST_SCAN);
    }
  }

  for(i = 1; i <= SECOND_SCAN; i++)
  {
    if(get_bit(bitmap, i))
    {
      fprintf(fo,"%d\n", i + FIRST_SCAN);
    }
  }
  
  fclose(fp);
  fclose(fo);
  free_map(bitmap);
  return 0;
}
