#include <iostream>
using namespace std;

struct ss{
    int aa;
    int bb;
};

int main(int argc, char *argv[])
{
    ss **ptr_ssarr= new ss*[8];
    /*
    int *ptr_int;
    ptr_int = new int(1);
    printf("ptr_int = %d\n", (*ptr_int));
    */

    for(int t = 0; t < 8; t++) {
        *(ptr_ssarr + t) = new ss;
        /* following code is fail 
        *(ptr_ssarr + t) -> aa = 11;
        *(ptr_ssarr + t) -> bb = 22;
        */
        (*(ptr_ssarr + t)) -> aa = 11;
        (*(ptr_ssarr + t)) -> bb = 22;
    }
    
}

