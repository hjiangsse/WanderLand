#include <stdio.h>

typedef struct _Node {
    int elem;
    struct _Node *next;
}Node;

int main() {
    printf("Sizeof Node: %d\n", sizeof(Node));
    return 0;
}
