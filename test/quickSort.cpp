#include <iostream>
#include <vector>

using namespace std;

void sortTrans(int *trans, int front, int rear);

int main(){
   int[] a = {3, 2, 5, 7, 4, 8, 6, 9}; 
    
   sortTrans(&a, 0, 7);

}

void sortTrans(int *trans, int front, int rear){
    if(rear <= front)
       return;
    
    int pivot = (*trans)[front];
    int l = front;
    int c = front + 1;
    
    int tmp;
    while(c <= rear){
        if(compareItem(pivot, (*trans)[c], mapSup) < 0){
            tmp = (*trans)[c];
            l++;
            (*trans)[c] = (*trans)[l];
            (*trans)[l] = tmp;
        }
        c++;
    }
    tmp = (*trans)[l];
    (*trans)[l] = pivot;
    (*trans)[front] = tmp;

    sortTrans(trans, mapSup, front, l-1);
    sortTrans(trans, mapSup, l+1, rear);

    return;
}
