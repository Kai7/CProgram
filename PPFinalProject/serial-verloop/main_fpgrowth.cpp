#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "fptree.h"

using namespace std;

const bool WRITE_TO_FILE = false;
const bool SAVE_TO_MEMORY = false;
const bool SHOW_FP = true;

int main(){
    //string inputFile = "dataset/simple.txt";
    //double minsup = 0.5;
    //string inputFile = "dataset/simple2.txt";
    //double minsup = 0.3;
    //string inputFile = "dataset/D1kT10N500.txt";
    string inputFile = "dataset/D100kT10N1k.txt";
    double minsup = 0.0002;
    
    fptree *fpt = new fptree();

    fpt->buildTree(inputFile, minsup);
    fpt->mining();
    
    return 0;
}
