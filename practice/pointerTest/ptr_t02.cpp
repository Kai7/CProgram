#include "iostream"

using namespace std;

struct my_struct{
    int a;
    double b;
};

int main(){
    my_struct s1;

    cout << "s1.a = " << s1.a << endl
         << "s1.b = " << s1.b << endl;

    my_struct s2 = my_struct();

    cout << "s2.a = " << s2.a << endl
         << "s2.b = " << s2.b << endl;

    my_struct *s3 = new my_struct;

    cout << "s3 -> a = " << s3 -> a << endl
         << "s3 -> b = " << s3 -> b << endl;

    my_struct *s4;
    s4 = new my_struct();

    cout << "s4 -> a = " << s4 -> a << endl
         << "s4 -> b = " << s4 -> b << endl;

}

