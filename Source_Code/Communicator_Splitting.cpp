
#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int numprocs, org_rank, new_size, new_rank;
    MPI_Comm new_comm;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &org_rank);

    MPI_Comm_split(MPI_COMM_WORLD, org_rank % 2, 0, &new_comm);

    MPI_Comm_size(new_comm, &new_size);
    MPI_Comm_rank(new_comm, &new_rank);

    printf("World rank %d/%d -> new_comm rank %d/%d\n",
           org_rank, numprocs, new_rank, new_size);

    int sum_ranks = 0;

    MPI_Reduce(&new_rank, &sum_ranks, 1, MPI_INT, MPI_SUM, 0, new_comm);

    if (new_rank == 0)
    {
        printf("Sum of ranks in group %d = %d\n",
               (org_rank % 2), sum_ranks);
    }

    MPI_Comm_free(&new_comm);
    MPI_Finalize();

    return 0;
}
