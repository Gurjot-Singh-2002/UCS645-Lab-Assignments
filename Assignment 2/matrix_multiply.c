#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 70  // Matrix size

void multiply_serial(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void multiply_parallel(int A[N][N], int B[N][N], int C[N][N], int rank, int size) {
    int rows_per_proc = N / size;
    int local_A[rows_per_proc][N], local_C[rows_per_proc][N];

    // Scatter rows of matrix A
    MPI_Scatter(A, rows_per_proc * N, MPI_INT, local_A, rows_per_proc * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Broadcast matrix B to all processes
    MPI_Bcast(B, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Local matrix multiplication
    for (int i = 0; i < rows_per_proc; i++) {
        for (int j = 0; j < N; j++) {
            local_C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                local_C[i][j] += local_A[i][k] * B[k][j];
            }
        }
    }

    // Gather the local results into the final matrix C
    MPI_Gather(local_C, rows_per_proc * N, MPI_INT, C, rows_per_proc * N, MPI_INT, 0, MPI_COMM_WORLD);
}

int main(int argc, char *argv[]) {
    int rank, size;
    int A[N][N], B[N][N], C[N][N];
    double start_time, run_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize matrices at rank 0
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = i + j;
                B[i][j] = i - j;
            }
        }

        // Measure serial time at rank 0
        start_time = MPI_Wtime();
        multiply_serial(A, B, C);
        run_time = MPI_Wtime() - start_time;
        printf("Serial Execution Time: %f seconds\n", run_time);
    }

    // Synchronize all processes before measuring parallel time
    MPI_Barrier(MPI_COMM_WORLD);

    // Measure parallel time
    start_time = MPI_Wtime();
    multiply_parallel(A, B, C, rank, size);
    run_time = MPI_Wtime() - start_time;

    // Print parallel time only from rank 0
    if (rank == 0) {
        printf("Parallel Execution Time: %f seconds\n", run_time);
    }

    MPI_Finalize();
    return 0;
}
