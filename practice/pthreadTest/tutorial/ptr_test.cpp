#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
    int **ptr_arr = new int*[8];
    /*
    int *ptr_int;
    ptr_int = new int(1);
    printf("ptr_int = %d\n", (*ptr_int));
    */

    for(int t = 0; t < 8; t++) {
        *(ptr_arr + t) = new int(t);
    }
    
    for(int t = 0; t < 8; t++){
        printf("arr[%d]=%d\n", t, **(ptr_arr + t));
    }
}

