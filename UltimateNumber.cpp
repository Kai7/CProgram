#include "iostream"
#include "cstdlib"
#include "ctime"
using namespace std;

enum hitStatus {LESSTHAN = -1, EQUAL, LARGERTHAN};

bool inputLegitimateChecking(int inputNum);
hitStatus hitUltimateNumCheching(int inputNum);

int ultimateNum;
int frontNum, rearNum;

int main(){
    int userInputNum;
    hitStatus compareResult;

    while(true){
        frontNum = 1;
        rearNum = 100;

        cout << "\033[1;33m*** Welcome to Ultimate Number Game *** \033[0m" << endl;
        cout << "\033[1mPlease input an integer(1~100): \033[0m";
        cin >> userInputNum;
        cin.ignore();
        if(!inputLegitimateChecking(userInputNum)){
            cout << "\033[1;31mIllegal number ! \033[0m" << endl;
            continue;
        }
        srand(time(0));
        ultimateNum = rand() % 100 + 1;
        cout << "ultimateNum is " << ultimateNum << endl;

        while(true){
            compareResult = hitUltimateNumCheching(userInputNum);
            if(compareResult == 0){
                cout << "\033[1;32mCongratulations ! \033[0m" << endl;
                cout << "========================================" 
                     << endl << endl;
                break;
            }
            else if(compareResult < 0)
                frontNum = userInputNum + 1;
            else
                rearNum = userInputNum - 1; 
            cout << "\033[0;33mUltimateNumber is between " 
                 << frontNum << " and " << rearNum << "\033[0m"
                 << endl << endl;

            while(true){
                cout << "\033[1mPlease input your next number(" 
                     << frontNum << "~" << rearNum << "): \033[0m";
                cin >> userInputNum;
                cin.ignore();
                if(inputLegitimateChecking(userInputNum))
                    break;
                cout << "Illegal number !" << endl;
            }
        }
    }
}

bool inputLegitimateChecking(int inputNum){
    if(inputNum < frontNum || inputNum > rearNum)
        return false;
    return true;
}

hitStatus hitUltimateNumCheching(int inputNum){
    if(inputNum == ultimateNum)
        return EQUAL;
    else if(inputNum < ultimateNum)
        return LESSTHAN;
    else
        return LARGERTHAN;
}

