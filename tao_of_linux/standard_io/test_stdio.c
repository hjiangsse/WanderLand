#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <ctype.h>

void test_fgetc_and_ingetc();
void test_fgets();
FILE *get_next_word(FILE *pf);
void test_write();

int main()
{
  //test_fgetc_and_ingetc();
  //test_fgets();
  /*
  FILE *pf = fopen("test.txt", "r");
  if(!pf)
    perror("Open file error!");

  pf = get_next_word(pf);
  pf = get_next_word(pf);
  pf = get_next_word(pf);
  */
  test_write();
  return 0;
}

void test_write() {
  FILE *pf = fopen("./test.txt", "a+");
  if(!pf)
    perror("open file error!");

  fseek(pf, 0, SEEK_END);

  //first test fputc
  fputc('\n', pf);
  int i = 0;
  for(i = 'a'; i < 'z'; i++) {
    fputc(i, pf);
  }
  fputc('\n', pf);

  //second, test fputs
  fputs("This is a test line.\n", pf);

  //last, test fwrite
  int arr[] = {1,2,3};
  fwrite(arr, sizeof(arr[0]), sizeof(arr)/sizeof(arr[0]), pf);

  fclose(pf);
} 

FILE *get_next_word(FILE *pf) {
  //trim the leading spaces
  int c;
  char word[1024] = {0};
  int  inword = 0;
  char *widx = word;
  
  while((c = fgetc(pf)) != EOF) {
      if(isspace(c) && !inword)
        continue;
      if(isspace(c) && inword) {
        printf("%s\n", word);
        break;
      }
      *widx++ = c;
      inword = 1;
  }

  return pf;
}

void test_fgets() {
  FILE *pf;
  char buf[100];

  pf = fopen("./test.txt", "r");
  if(pf == NULL)
    perror("open file error!");

  if(!fgets(buf, 100, pf))
    perror("read string to buffer error");

  printf("%s\n", buf);
}

void test_fgetc_and_ingetc() {
  FILE *pf;
  int c;
  
  pf = fopen("./test.txt", "r");
  if(pf == NULL)
    perror("open file error!");

  /* read a character each time */
  while((c = fgetc(pf)) != EOF)
  {
    printf("%c", c);
  }

  //use ungetc push character back to the io buffer
  ungetc('\n', pf);
  ungetc('h', pf);
  ungetc('e', pf);
  ungetc('l', pf);
  ungetc('l', pf);
  ungetc('o', pf);
  
  while((c = fgetc(pf)) != '\n')
  {
    printf("%c", c);
  }
  putchar('\n');

  //use ungetc and seek
  ungetc('\n', pf);
  ungetc('o', pf);
  ungetc('l', pf);
  ungetc('l', pf);
  ungetc('e', pf);
  ungetc('h', pf);

  fseek(pf, 0, SEEK_END);

  while((c = fgetc(pf)) != EOF)
  {
    printf("%c", c);
  }
  putchar('\n');
  
}

