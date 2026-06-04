#include <iostream>
#include <omp.h>
using namespace std ;
const int N = 20;

void NEST_STUFF(int i) {
    // prints the mapping of loop iterations to specific system threads
    #pragma omp critical
    {
        cout << "Thread " << omp_get_thread_num() << " processes iteration index: " << i << "\n";
    }
}

int main() {
    omp_set_num_threads(4);

    // Launch a parallel region
    #pragma omp parallel
    {
        // Work-sharing directive to distribute loop iterations among threads
        #pragma omp for
        for (int i = 0; i < N; i++) {
            NEST_STUFF(i);
        }
    }

    return 0;
}
