#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, size;
    long num_steps = 100000; // Total number of steps
    double step, x, pi, sum = 0.0;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Broadcast the total number of steps to all processes
    MPI_Bcast(&num_steps, 1, MPI_LONG, 0, MPI_COMM_WORLD);

    step = 1.0 / (double)num_steps; // Step size

    // Start timing
    if (rank == 0) {
        start_time = MPI_Wtime();
    }

    // Each process computes its partial sum
    double partial_sum = 0.0;
    for (int i = rank; i < num_steps; i += size) {
        x = (i + 0.5) * step;
        partial_sum += 4.0 / (1.0 + x * x);
    }

    // Reduce all partial sums to the root process (rank 0)
    MPI_Reduce(&partial_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Root process computes the final value of π
    if (rank == 0) {
        pi = step * sum;
        end_time = MPI_Wtime();
        printf("Approximate value of pi: %.16f\n", pi);
        printf("Time taken: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}