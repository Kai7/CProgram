#include "iostream"
#include "iomanip"
#include "cmath"
using namespace std;

int main(){
    double amount, principal = 1000.0, rate = .05;

    cout << "Year" << setw(21) << "Amount on deposit" << endl;
    cout << fixed << setprecision(2);

    for (int year = 1; year <= 10; year++){
        amount = principal * powl(1.0 + rate, year);
        cout << setw(4) << year << setw(21) << amount << endl;
    }
    return 0;
}
