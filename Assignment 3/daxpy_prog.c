#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define N (1 << 16) // Vector size: 2^16

// DAXPY operation: X = a * X + Y
void daxpy(double a, double *X, double *Y, int start, int end) {
    for (int i = start; i < end; i++) {
        X[i] = a * X[i] + Y[i];
    }
}

int main(int argc, char **argv) {
    int rank, size;
    double *X, *Y, a = 2.0;
    double mpi_start_time, mpi_end_time, mpi_time, serial_time, speedup;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_size = N / size; // Number of elements per process
    X = (double *)malloc(local_size * sizeof(double));
    Y = (double *)malloc(local_size * sizeof(double));

    // Initialize vectors X and Y for parallel computation
    for (int i = 0; i < local_size; i++) {
        X[i] = (double)(rank * local_size + i);
        Y[i] = (double)(rank * local_size + i);
    }

    // Synchronize all processes before timing
    MPI_Barrier(MPI_COMM_WORLD);
    mpi_start_time = MPI_Wtime();

    // Parallel DAXPY operation
    daxpy(a, X, Y, 0, local_size);

    // Synchronize all processes after computation
    MPI_Barrier(MPI_COMM_WORLD);
    mpi_end_time = MPI_Wtime();
    mpi_time = mpi_end_time - mpi_start_time;

    // Calculate and print MPI time only from rank 0
    if (rank == 0) {
        printf("MPI DAXPY time: %f seconds\n", mpi_time);
    }

    // Free allocated memory
    free(X);
    free(Y);

    // Serial DAXPY (only in rank 0)
    if (rank == 0) {
        X = (double *)malloc(N * sizeof(double));
        Y = (double *)malloc(N * sizeof(double));

        // Initialize vectors X and Y for serial computation
        for (int i = 0; i < N; i++) {
            X[i] = (double)i;
            Y[i] = (double)i;
        }

        // Measure start time for serial
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        // Serial DAXPY operation
        daxpy(a, X, Y, 0, N);

        // Measure end time for serial
        clock_gettime(CLOCK_MONOTONIC, &end);
        serial_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

        printf("Uniprocessor DAXPY time: %f seconds\n", serial_time);

        // Calculate and print speedup
        speedup = serial_time / mpi_time;
        printf("Speedup (Serial/MPI): %.2f\n", speedup);

        free(X);
        free(Y);
    }

    MPI_Finalize();
    return 0;
}
