#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "math.h"
#define NUMTHRDS 4

struct tossInfo {
    int id;
    unsigned long long idx_front;
    unsigned long long idx_end;
    unsigned int *seed;
};

void *rand_tossdarts(void *toss_info) {
    int t_id = ((tossInfo*)toss_info)->id;
    unsigned long long front = ((tossInfo*)toss_info)->idx_front;
    unsigned long long end = ((tossInfo*)toss_info)->idx_end;
    unsigned int *t_seed = ((tossInfo*)toss_info) ->seed;
    //t_seed = ((tossInfo*)toss_info)->seed;

    unsigned long long *num_hit = new unsigned long long;
    *num_hit = 0;
    unsigned long long i;
    double x, y;
    for(i = front; i<=end;i++){
        x = static_cast<double>(rand())/RAND_MAX;
        y = static_cast<double>(rand())/RAND_MAX;
        // printf("(x,y)=(%lf,%lf)\n",x,y);
        if ((x * x + y * y) <= 1.0) (*num_hit)++;
    }
    printf("thd_%d complete! (%llu - %llu)\n %llu toss, %llu hits.\n hit-ratio: %lf\n", 
            t_id, front, end, (end-front+1), *num_hit, static_cast<double>(*num_hit)/static_cast<double>(end-front+1));

    return num_hit;
}

int main(int argc, char *argv[]) {
    if(argc != 2){
        printf("argument fault!\n");
        return 1;
    }

    pthread_t **thds = new pthread_t *[NUMTHRDS];
    for (int i = 0; i < NUMTHRDS; i++) {
        *(thds + i) = new pthread_t;
    }
    // pthread_mutex_t *mutexsum = new pthread_mutex_t;

    unsigned long long num_totaltoss;
    sscanf(argv[1], "%llu", &num_totaltoss);
    unsigned long long number_in_circle = 0;

    unsigned long long num_thdtoss = num_totaltoss / NUMTHRDS;
    unsigned int *g_seed = new unsigned int;
    *g_seed = time(NULL);
    tossInfo **thdargs = new tossInfo *[NUMTHRDS];
    for (int i = 0; i < NUMTHRDS; i++) {
        *(thdargs + i) = new tossInfo;
        (*(thdargs + i)) ->id = i;
        (*(thdargs + i)) ->idx_front = i*num_thdtoss+1;
        (*(thdargs + i)) ->seed = g_seed;
        if(i == NUMTHRDS - 1)
            (*(thdargs + i))->idx_end = num_totaltoss;
        else
            (*(thdargs + i))->idx_end = (i+1)*num_thdtoss;
            
        if (pthread_create(*(thds + i), NULL, rand_tossdarts, (void *)*(thdargs + i))) {
            printf("ERROR: pthread_create fail.");
            exit(-1);
        }
    }

    void *t_num_hit;
    for (int i = 0; i < NUMTHRDS; i++) {
        pthread_join(**(thds+i), &t_num_hit);
        number_in_circle += *((unsigned long long*)t_num_hit);
    }
    printf("======================================================\n");
    printf("%llu toss, %llu hits.\npi = %lf\n",
            num_totaltoss, number_in_circle, 4.0*static_cast<double>(number_in_circle)/static_cast<double>(num_totaltoss));

    pthread_exit(NULL);
}
