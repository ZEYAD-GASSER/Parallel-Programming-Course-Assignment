
#include <omp.h>
#include <iostream>

const int MAX = 100;
using namespace std ;
int main() {
    double ave = 0.0;
    double A[MAX];

    // initialize the array elements with dummy data
    for (int i = 0; i < MAX; i++) {
        A[i] = static_cast<double>(i + 1);
    }

    // parallel loop with an addition reduction on the 'ave' variable
    #pragma omp parallel for reduction(+:ave)
    for (int i = 0; i < MAX; i++) {
        ave += A[i];
    }

    // calculate the final average value
    ave = ave / MAX;

    cout << "Calculated Average (ave): " << ave << "\n";

    return 0;
}
