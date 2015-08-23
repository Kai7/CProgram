#include "iostream"
#include "stdio.h"
#include "string"
using namespace std;
#define DATA_SIZE 12

string floatCommaFormat(double num);

int main(){
    int dataSetNum;
    double avg, sum;
    double *datas = new double[DATA_SIZE];

    cin >> dataSetNum;
    int t = 1, i;
    while(t <= dataSetNum){
        sum = 0.0;
        for (i = 0; i < DATA_SIZE; ++i) {
            cin >> datas[i];
            sum += datas[i];
        }
        avg = sum / 12;

        printf("%d $%.2f\n", avg);
    }
}

string floatCommaFormat(double num){
    string commaFormat;

    return commaFormat;
}
