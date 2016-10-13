#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	8

using namespace std;

void *PrintHello(void *threadid)
{
    int taskid;

    taskid = *((int*) threadid);
    printf("Thread %d: do something... \n", taskid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int **ptr_taskids = new int*[NUM_THREADS];
    int rc, t;
    
    for(t=0;t<NUM_THREADS;t++) {
        *(ptr_taskids + t) = new int(t);
        printf("Creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *) *(ptr_taskids + t));
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    
    pthread_exit(NULL);
}

