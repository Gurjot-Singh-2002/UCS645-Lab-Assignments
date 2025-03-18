#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 4 // Define the size of the matrix (NxN)

void print_matrix(int *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    int matrix[N][N], transposed[N][N], local_rows[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_process = N / size;

    if (rank == 0) {
        // Initialize the matrix with values
        printf("Original Matrix:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matrix[i][j] = i * N + j + 1;
            }
        }
        print_matrix((int *)matrix, N, N);
    }

    // Scatter rows to processes
    MPI_Scatter(matrix, rows_per_process * N, MPI_INT, local_rows, rows_per_process * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Local transposition
    int local_transpose[N][rows_per_process];
    for (int i = 0; i < rows_per_process; i++) {
        for (int j = 0; j < N; j++) {
            local_transpose[j][i] = local_rows[i * N + j];
        }
    }

    // Gather the transposed sub-matrices
    MPI_Gather(local_transpose, rows_per_process * N, MPI_INT, transposed, rows_per_process * N, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nTransposed Matrix:\n");
        print_matrix((int *)transposed, N, N);
    }

    MPI_Finalize();
    return 0;
}
