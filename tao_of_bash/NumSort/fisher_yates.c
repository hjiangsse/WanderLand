#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y);
void shuffle_array(int *arr, int arrlen);
void print_array(int *arr, int arrlen, const char *title);

int main() {
  int i;
  int iarr[] = {1,2,3,4,5,6,7};
  int len = sizeof(iarr)/sizeof(int);

  print_array(iarr, len, "The raw array is: ");
  shuffle_array(iarr, len);
  print_array(iarr, len, "The shuffled array is: ");
  
  return 0;
}

void swap(int *x, int *y) {
  int tmp;
  tmp = *x;
  *x = *y;
  *y = tmp;
}

void shuffle_array(int *arr, int arrlen)
{
  srand(time(NULL));
  int i = 0;
  int j = 0;
  for(i = arrlen - 1; i > 0; i--)
  {
    j = rand() % i;
    swap(arr + i, arr + j);
  }
}

void print_array(int *arr, int arrlen, const char *title)
{
  int i;
  printf("%s\n", title);
  for(i = 0; i < arrlen; i++)
  {
    printf("%d ", *(arr+i));
  }
  putchar('\n');
}
