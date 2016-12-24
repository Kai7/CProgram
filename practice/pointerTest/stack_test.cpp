#include <iostream>
#include <stack>

using namespace std;

int main(){
    stack<int*> s; 
    
    int na = 1;
    int nb = 2;
    int nc = 3;

    int *a = &na;
    int *b = &nb;
    int *c = &nc;

    s.push(a);
    s.push(b);
    s.push(c);

    while(!s.empty()){
        int *i = s.top();

        cout << (*i) << endl;

        s.pop();
    }
}
