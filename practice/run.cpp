#include "iostream"
#include "GradeBook.h"
using namespace std;

int main(){
    GradeBook myGradeBook("C++ Programming Practice");

    cout << "Initial course name is: " << myGradeBook.getCourseName() << endl;

    myGradeBook.displayMessage();
    myGradeBook.determineClassAverage();
}
