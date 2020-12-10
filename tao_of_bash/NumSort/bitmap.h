#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint32_t word_t;
enum {
      BITS_PER_WORD = sizeof(word_t) * CHAR_BIT
};

#define WORD_OFFSET(b) ((b) / BITS_PER_WORD)
#define BIT_OFFSET(b)  ((b) % BITS_PER_WORD)

word_t *alloc_bit(int n) {
  if(BIT_OFFSET(n) == 0)
  {
    return (word_t *)(malloc(WORD_OFFSET(n) * sizeof(word_t)));
  }
  else
  {
    return (word_t *)(malloc((WORD_OFFSET(n) + 1) * sizeof(word_t)));
  }
}

void set_bit(word_t *words, int n)
{
  words[WORD_OFFSET(n)] |= (1 << BIT_OFFSET(n));
}

void clear_bit(word_t *words, int n)
{
  words[WORD_OFFSET(n)] &= ~(1 << BIT_OFFSET(n));
}

int get_bit(word_t *words, int n)
{
  word_t bit = words[WORD_OFFSET(n)] & (1 << BIT_OFFSET(n));
  return bit != 0;
}

void free_map(word_t *words)
{
  if(words != NULL)
  {
    free(words);
  }
}
