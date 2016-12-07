#include <iostream>
#include <cstddef>
#include <list>

#define nullptr NULL;

using namespace std;

struct t_node{
    int item;
    t_node *next;

    t_node(){
        item = -1;
        next = nullptr;
    }

};

int main(){
    list<int> *trans;
    trans = new list<int>;

    trans->push_back(2);
    trans->push_back(6);
    trans->push_back(9);
    trans->push_back(6);


    while(!trans->empty()){
        int i = trans->front(); 
        cout << i << endl;

        trans->pop_front();
    }

    return 0;
}

