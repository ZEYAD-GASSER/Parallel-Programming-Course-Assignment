
#include <iostream>
#include <omp.h>
using namespace std ;
const int N = 3;
const int M = 3;

int main() {
    omp_set_num_threads(4);

    // Fix: Collapse clause flattens nested loops; brackets should not surround the loops
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            #pragma omp critical
            {
                cout << "Thread " << omp_get_thread_num()
                          << " handles matrix element: [" << i << "][" << j << "]\n";
            }
        }
    }

    return 0;
}
