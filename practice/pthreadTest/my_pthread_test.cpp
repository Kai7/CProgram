#include "stdio.h"
#include <unistd.h>
//#include "pthread.h"

void *sumOfArray(void *ptr){

}

int main(void){
    int numCPU = sysconf(_SC_NPROCESSORS_ONLN); 

    printf("There are %d cores in system.\n",numCPU);

    return 0;
}
