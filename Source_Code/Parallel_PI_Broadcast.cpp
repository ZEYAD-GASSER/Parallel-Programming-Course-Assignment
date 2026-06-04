
#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int done = 0, n = 0, myid, numprocs, i;
    double PI25DT = 3.141592653589793238462643;
    double pi = 0.0, h, sum, x, start = 0.0, finish;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    while (!done)
    {
        if (myid == 0)
        {
            printf("Enter the number of intervals (0 quits): ");
            fflush(stdout);

            if (scanf("%d", &n) != 1)
                n = 0;

            start = MPI_Wtime();
        }

        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

        if (n == 0)
        {
            done = 1;
        }
        else
        {
            h = 1.0 / (double)n;
            sum = 0.0;

            for (i = myid + 1; i <= n; i += numprocs)
            {
                x = h * ((double)i - 0.5);
                sum += 4.0 / (1.0 + x * x);  
            }

            MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

            if (myid == 0)
            {
                finish = MPI_Wtime();
                printf("Pi is approx. %.16f, Error is %.16f\n",
                       pi * h, fabs(pi * h - PI25DT));

                printf("Elapsed time: %f seconds\n", finish - start);
            }
        }
    }

    MPI_Finalize();
    return 0;
}
