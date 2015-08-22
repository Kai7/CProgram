#include "iostream"
#include "GradeBook.h"
using namespace std;

int main(){
    string nameOfCourse;
    GradeBook myGradeBook("abc");

    cout << "Initial course name is: " << myGradeBook.getCourseName() 
         << endl;

    cout << "\nPlease enter the course name: ";
    getline(cin, nameOfCourse);
    myGradeBook.setCourseName(nameOfCourse);
    cout << endl;
    myGradeBook.displayMessage();
}
