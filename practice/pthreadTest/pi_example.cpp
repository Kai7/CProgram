#include <iostream>
#include <time.h>    // time
#include <stdlib.h>  // srand

using namespace std;

int main() {
    srand(time(NULL));
    cout.precision(10);
    cout << "HelloACM.com rocks!" << endl;
    const int N[] = {1e3, 1e4, 1e5, 1e6, 1e7, 1e8};
    for (int j = 0; j < (sizeof(N) / sizeof(N[0])); j++) {
        int circle = 0;
        for (int i = 0; i < N[j]; i++) {
            double x =
                static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
            double y =
                static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
            if (x * x + y * y <= 1.0) circle++;
        }

        cout << N[j] << (char)9 << (char)9 << (double)circle / N[j] * 4.0
             << endl;
    }
    return 0;
}
