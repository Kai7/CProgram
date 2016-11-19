#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include "mpi.h"

int  isprime(int n) {
    int i,squareroot;
    if (n>10) {
        squareroot = (int) sqrt(n);
        for (i=3; i<= squareroot; i=i+2)
            if ((n%i)==0)
                return  0;
        return  1;
    }
    else
        return  0;
}

int  main(int argc , char *argv [])
{
    int my_rank, num_tasks;
    int pc , par_pc,             /*  prime  counter  */
        foundone, par_foundone;  /*  most  recent  prime  found */
    long  long  int n, limit;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD,&num_tasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    
    sscanf(argv[1],"%llu",&limit);

    if(my_rank == 0){
        printf("Starting. Numbers  to be  scanned= %lld\n",limit);
    }

    //pc=4;          /*  Assume  (2,3,5,7) are  counted  here */

    par_foundone = 7;
    par_pc = 0;
    for (n=11 + my_rank*2; n <= limit; n += 2 * num_tasks) {
        if (isprime(n)) {
            par_pc++;
            par_foundone = n;
        }
    }

    MPI_Reduce(&par_pc, &pc, 1, MPI_INT, MPI_SUM,
               0, MPI_COMM_WORLD);
    MPI_Reduce(&par_foundone, &foundone, 1, MPI_INT, MPI_MAX, 
               0, MPI_COMM_WORLD);

    if(my_rank == 0){
        pc += 4;            /*  Assume  (2,3,5,7) are  counted  here */
        printf("Done. Largest  prime is %d Total  primes %d\n",
                foundone , pc);
    }

    MPI_Finalize();
}
