#include <iostream>
#include <list>
#include <utility>

using namespace std;


void showTransList(list<pair<int, list<int> > > *translist);
void showTrans(list<int> *trans);
    
int main(){
    list<pair<int, list<int> > > TransList;

    for(int i = 0; i<5; i++){
        list<int> Trans;
        for(int j = i; j < i+10; j += 2){
            Trans.push_back(j);
        }
        TransList.push_back(make_pair(i, Trans));
    }

    showTransList(&TransList);

    for(int i = 0; i<5; i++){
        list<int> trans;

        trans.push_back(i);
        showTrans(&trans);
    }
    return 0;
}

void showTransList(list<pair<int, list<int> > > *translist){
    list<pair<int, list<int> > >::iterator it = translist->begin();
    for(; it != translist->end(); it++){
        int sup = it->first;
        cout << "< " << sup << ", ";
        showTrans(&(it->second));
        cout << ">" << endl;
    }
}

void showTrans(list<int> *trans){
    list<int>::iterator it = trans->begin();
    cout << "[ ";
    for(;it != --trans->end(); it++){
        cout << *it << ", ";
    }
    cout << (*it) << " ] ";
}
