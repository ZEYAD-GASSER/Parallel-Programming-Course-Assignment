
#include <omp.h>
#include <iostream>

static long num_steps = 100000;
#define NUM_THREADS 2

int main()
{
    int i, nthreads;
    double pi, sum[NUM_THREADS];
    double step = 1.0 / (double)num_steps;

    omp_set_num_threads(NUM_THREADS);

#pragma omp parallel
    {
        int id, nthrds;
        double x;

        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();

        sum[id] = 0.0;

        for (int i = id; i < num_steps; i += nthrds)
        {
            x = (i + 0.5) * step;
            sum[id] += 4.0 / (1.0 + x * x);
        }

        if (id == 0)
            nthreads = nthrds;
    }

    pi = 0.0;

    for (i = 0; i < nthreads; i++)
        pi += sum[i];

    pi *= step;

    std::cout << "PI = " << pi << std::endl;

    return 0;
}
