#include <omp.h>
#include <iostream>
using namespace std ;

const int niters = 100 ;
float big_job(int i) {
    return (float)(i)* 2.0f;
}
float consume(float B) {
    return B + 1.0f;
}
int main ()
{
        float res;
        #pragma omp parallel
        {
                float B;  int i, id, nthrds;
                id = omp_get_thread_num();
                nthrds = omp_get_num_threads();
                for(i=id;i<niters;i+=nthrds){
                        B = big_job(i);
                #pragma omp critical
                      res += consume (B);
                }
        }
        cout<< " Result : " << res <<endl ;
        return 0 ;
}
