#include "omp.h"
#include <stdio.h>
void pooh(int thread_id, double *array) {
    // A sample implementation of the lecture's dummy function
    printf("Thread %d processing array A at address: %p\n", thread_id, (void*)array);
}
int main()
{
        // here I set the max number of threads to 4
        double A[1000] ;
        omp_set_num_threads(4);
        #pragma omp parallel
        {
                int ID = omp_get_thread_num();
                pooh(ID, A);
        }
        return 0 ;
}
