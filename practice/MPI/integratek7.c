#include  <stdio.h>
#include  <math.h>
#include "mpi.h"

#define  PI  3.1415926535

int  main(int argc , char **argv)
{
    int my_rank, num_tasks;
    long long i, num_intervals;
    double rect_width , area , sum, par_sum , x_middle;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD,&num_tasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

    sscanf(argv[1],"%llu",&num_intervals);

    rect_width = PI / num_intervals;

    par_sum = 0;
    for(i = my_rank + 1; i < num_intervals + 1; i += num_tasks) {
        /* find  the  middle  of the  interval  on the X-axis. */
        x_middle = (i - 0.5) * rect_width;
        area = sin(x_middle) * rect_width;
        par_sum += area;
    }

    MPI_Reduce(&par_sum, &sum, 1, MPI_DOUBLE,
               MPI_SUM, 0, MPI_COMM_WORLD);

    if(my_rank == 0){
        printf("The  total  area is: %f\n", (float)sum);
    }

    MPI_Finalize();
}
