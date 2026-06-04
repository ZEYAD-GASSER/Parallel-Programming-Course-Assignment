
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int numprocs, rank, tag = 100, msg_size = 64;
    char *buf;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if (numprocs != 2)
    {
        printf("The number of processes must be two!!\n");
        MPI_Finalize();
        return 0;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("MPI process %d started...\n", rank);
    fflush(stdout);

    while (msg_size < 10000000)
    {
        msg_size *= 2;

        buf = (char *)malloc(msg_size * sizeof(char));

        if (rank == 0)
        {
            MPI_Send(buf, msg_size, MPI_BYTE, 1, tag, MPI_COMM_WORLD);
            printf("P0 sent message size %d to P1\n", msg_size);
            fflush(stdout);

            MPI_Recv(buf, msg_size, MPI_BYTE, 1, tag, MPI_COMM_WORLD, &status);
        }

        else if (rank == 1)
        {
            MPI_Recv(buf, msg_size, MPI_BYTE, 0, tag, MPI_COMM_WORLD, &status);
            MPI_Send(buf, msg_size, MPI_BYTE, 0, tag, MPI_COMM_WORLD);

            printf("P1 exchanged message size %d with P0\n", msg_size);
            fflush(stdout);
        }

        free(buf);
    }

    MPI_Finalize();
    return 0;
}
