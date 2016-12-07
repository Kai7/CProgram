#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    string filename = "simple.txt";
    ifstream fin;
    fin.open(filename.c_str());

    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }

    fin.clear();
    fin.seekg(0, fin.beg);

    cout << "second read ... " << endl;
    while (getline(fin, line)) {
        cout << line << endl;
    }

    return 0;
}
