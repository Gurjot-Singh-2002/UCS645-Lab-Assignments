#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, local_value, global_sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Each process has a unique value (e.g., its rank + 1)
    local_value = rank + 1;

    // Perform the reduction operation (sum) to rank 0
    MPI_Reduce(&local_value, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Rank 0 prints the final result
    if (rank == 0) {
        printf("Total Sum using MPI_Reduce: %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}
