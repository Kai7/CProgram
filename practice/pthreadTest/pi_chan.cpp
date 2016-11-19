#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#define NUM_THREADS 4

void *Mote(void *t) {
    int *circle = new int(0);
    double pi = 0.0;
        for (int i = 0; i < *((long*)t); i ++) {
            double x = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
            double y = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
            if (x * x + y * y <= 1.0) (*circle) ++;
        }
    //pi = (double)circle/ *((long*)t) * 4.0;
    //printf("Thread %ld done. pi = %e\n", tid, pi);
   
    pthread_exit(circle);
}

int main(int argc, char *argv[]) {
    long  total_toss_num = atof(argv[1]);
	
	pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;
    int rc;
   
    //printf("thread number:%d\n",NUM_THREADS);
    //
	//scanf("%d",&total_toss_num);
	

    long toss_num = total_toss_num/NUM_THREADS;
    void *status;

    /* Initialize and set thread detached attribute */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (int t = 0; t < NUM_THREADS; t++) {
        //printf("Main: creating thread %ld\n", t);
        rc = pthread_create(&thread[t], &attr, Mote, &toss_num);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    /* Free attribute and wait for the other threads */
    int total_circle = 0;
    pthread_attr_destroy(&attr);
    for (int t = 0; t < NUM_THREADS; t++) {
        rc = pthread_join(thread[t], &status);
        total_circle += *((int*)status);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        /*printf("Main: completed join with thread %ld having a status of %ld\n",
               t, status); */ 
    }
    printf("pi=%lf\n", 4*static_cast<double>(total_circle) / static_cast<double>(total_toss_num));
    return(0);
    pthread_exit(NULL);
   
}
