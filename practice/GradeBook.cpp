#include "iostream"
#include "GradeBook.h"
using namespace std;

GradeBook::GradeBook(string name){
    setCourseName(name);   
}

void GradeBook::setCourseName(string name){
    if (name.length() <= 25)
        courseName = name;
    else {
        courseName = name.substr(0, 25);

        cout << "Name \"" << name << "\" exceeds maximum length (25).\n"
             << "Limiting courseName to first 25 characters.\n" << endl;
    }
    courseName = name;
}

string GradeBook::getCourseName(){
    return courseName;
}

void GradeBook::displayMessage(){
    cout << "Welcome to the grade book for\n" << getCourseName() << "!" 
         << endl; 
}

void GradeBook::determineClassAverage(){
    int total = 0, gradeCounter = 1, grade, average;
    
}
