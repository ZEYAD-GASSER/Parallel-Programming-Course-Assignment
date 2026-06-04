#include <iostream>
#include <omp.h>
using namespace std ;
// Shared global accumulator variable
double X = 0.0;

double DOIT() {
    return 1.5;
}

double big_ugly(double B) {
    return B * 2.5;
}

int main() {
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        // Local private variables for each thread
        double tmp, B;

        B = DOIT();
        tmp = big_ugly(B);

        // Atomic synchronization: Safely update shared variable X
        #pragma omp atomic
        X += tmp;
    }

    cout << "Result (X): " << X << "\n";
    return 0;
}
