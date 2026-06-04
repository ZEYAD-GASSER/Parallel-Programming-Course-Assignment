
#include <iostream>
#include <omp.h>
using namespace std ;
const int NUM_THREADS = 4;

int big_calc1(int id) {
    return id * 10;
}

int big_calc2(int id, int* shared_array) {
    int neighbor_id = (id + 1) % NUM_THREADS;
    return shared_array[id] + shared_array[neighbor_id];
}

int main() {
    int A[NUM_THREADS] = {0};
    int B[NUM_THREADS] = {0};

    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        A[id] = big_calc1(id);
        #pragma omp barrier
        B[id] = big_calc2(id, A);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        cout << "Thread " << i << "A: " << A[i] << " | B: " << B[i] << "\n";
    }
    return 0;
}
