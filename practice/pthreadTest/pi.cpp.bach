#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "math.h"

#ifdef _WIN32
#include <windows.h>
#elif MACOS
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#endif
 

int getNumberOfCores();

struct tossInfo {
    int id;
    unsigned long long idx_front;
    unsigned long long idx_end;
    unsigned int *seed;
};

void *rand_tossdarts(void *toss_info) {
    int t_id = ((tossInfo*)toss_info)->id;
    unsigned long long front = ((tossInfo*)toss_info) -> idx_front;
    unsigned long long end = ((tossInfo*)toss_info) -> idx_end;
    unsigned int *t_seed = ((tossInfo*)toss_info) -> seed;
    //t_seed = ((tossInfo*)toss_info)->seed;

    unsigned long long *num_hit = new unsigned long long;
    *num_hit = 0;
    unsigned long long i;
    for (i = front; i <= end; i++) {
        double x = static_cast<double>(rand()) / RAND_MAX;
        double y = static_cast<double>(rand()) / RAND_MAX;
        if ((x * x + y * y) <= 1.0) (*num_hit)++;
    }

    return num_hit;
}

int main(int argc, char *argv[]) {
    int num_thrds = getNumberOfCores();
    //printf("num of thrds is %d\n", num_thrds); 

    if (argc != 2) {
        printf("argument fault!\n");
        return 1;
    }

    pthread_t **thds = new pthread_t *[num_thrds];
    for (int i = 0; i < num_thrds; i++) {
        *(thds + i) = new pthread_t;
    }

    unsigned long long num_totaltoss;
    sscanf(argv[1], "%llu", &num_totaltoss);
    unsigned long long number_in_circle = 0;

    unsigned long long num_thdtoss = num_totaltoss / num_thrds;
    unsigned int *g_seed = new unsigned int;
    *g_seed = time(NULL);
    tossInfo **thdargs = new tossInfo *[num_thrds];
    for (int i = 0; i < num_thrds; i++) {
        *(thdargs + i) = new tossInfo;
        (*(thdargs + i))->id = i;
        (*(thdargs + i))->idx_front = i * num_thdtoss + 1;
        (*(thdargs + i))->seed = g_seed;
        if (i == num_thrds - 1)
            (*(thdargs + i))->idx_end = num_totaltoss;
        else
            (*(thdargs + i))->idx_end = (i + 1) * num_thdtoss;

        if (pthread_create(*(thds + i), NULL, rand_tossdarts,
                           (void *)*(thdargs + i))) {
            printf("ERROR: pthread_create fail.");
            exit(-1);
        }
    }

    void *t_num_hit;
    for (int i = 0; i < num_thrds; i++) {
        pthread_join(**(thds + i), &t_num_hit);
        number_in_circle += *((unsigned long long *)t_num_hit);
    }
    printf("%llf\n",
           4.0 * static_cast<long double>(number_in_circle) /
               static_cast<long double>(num_totaltoss));

    pthread_exit(NULL);
}

int getNumberOfCores() {
#ifdef WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#elif MACOS
    int nm[2];
    size_t len = 4;
    uint32_t count;
     
    nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
    sysctl(nm, 2, &count, &len, NULL, 0);
     
    if(count < 1) {
        nm[1] = HW_NCPU;
        sysctl(nm, 2, &count, &len, NULL, 0);
        if(count < 1) { count = 1; }
    }
    return count;
#else
    return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}
