#include <stdio.h>
#include <stdlib.h>

extern int fee_count, fie_count, foe_count, fum_count;
extern int yylex(void);

int main(int argc, char **argv) 
{
    yylex();
    printf("fee_count: %d\n", fee_count);
    printf("fie_count: %d\n", fie_count);
    printf("foe_count: %d\n", foe_count);
    printf("fum_count: %d\n", fum_count);
    exit(0);
}
