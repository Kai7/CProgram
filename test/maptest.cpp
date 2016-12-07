#include <iostream>
#include <map>

using namespace std;

int main(){
    map<int, int> tm;
    tm.clear();

    tm[1] = 1;
    tm[2] = 2;
    tm[3] = 3;

    map<int, int>::iterator it;
    it = tm.find(2);

    if(it == tm.end()) return 1;

    it->second *= 100;

    cout << it->second << endl;

    return 0;
}
