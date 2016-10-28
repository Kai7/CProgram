#include <stdio.h>
#include <stdlib.h>
#include "time.h"

int main(int argc, char *argv[]) {
    unsigned int g_seed = time(NULL);

    srand (g_seed);
    double x,y;
    for(int i = 1; i<=10;i++){
        x = (double)rand()/RAND_MAX;
        y = (double)rand()/RAND_MAX;
        printf("(x,y)=(%lf,%lf)\n",x, y);
    }

    return 0;
}
