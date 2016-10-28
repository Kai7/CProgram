#include <stdio.h>

int main(int argc, char *argv[]) {
    unsigned long long example;
    int i;
    for (i = 1; i < argc; i++) {
        sscanf(argv[i], "%llu", &example);
        printf("Argument: %llu\n", example);
    }
    return 0;
}
