#include <stdio.h>
 
int main() {
    FILE *in;
    struct private {
        char name[100];
    unsigned long booty;
    unsigned int  beard_len;
    } p;
 
    in = fopen("data", "r");
    if(!in) {
    perror("fopen");
    return 1;
    }
 
    if(!fread(&p, sizeof(struct private), 1, in)) {
    perror("fread");
    return 1;
    }
 
    if(fclose(in)) {
    perror("fclose");
    return 1;
    }
 
    printf("name: %s\n", p.name);
    printf("booty: %lu\n", p.booty);
    printf("beard_len: %u\n", p.beard_len);
 
    return 0;
}
