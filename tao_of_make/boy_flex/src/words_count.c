#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "counter.h"

extern int fee_count, fie_count, foe_count, fum_count;
extern int yylex(void);

int main(int argc, char **argv) 
{
    int counts[4] = {0};
    counter(counts);

    printf("the number of fee: %d\n", fee_count);
    printf("the number of fie: %d\n", fie_count);
    printf("the number of foe: %d\n", foe_count);
    printf("the number of fum: %d\n", fum_count);
    exit(0);
}
