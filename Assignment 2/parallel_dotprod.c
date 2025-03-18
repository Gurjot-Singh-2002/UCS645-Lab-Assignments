#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 8  // Size of vectors

void print_vector(int *vec, int size, const char *msg) {
    printf("%s: ", msg);
    for (int i = 0; i < size; i++) {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int rank, size;
    int A[N], B[N], local_A[N], local_B[N];
    int local_dot = 0, global_dot = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int elements_per_proc = N / size;

    // Initialize vectors at process 0
    if (rank == 0) {
        printf("Vector A:\n");
        for (int i = 0; i < N; i++) {
            A[i] = i + 1;  // Example: {1, 2, 3, 4, 5, 6, 7, 8}
            printf("%d ", A[i]);
        }
        printf("\nVector B:\n");
        for (int i = 0; i < N; i++) {
            B[i] = N - i;  // Example: {8, 7, 6, 5, 4, 3, 2, 1}
            printf("%d ", B[i]);
        }
        printf("\n");
    }

    // Scatter vectors A and B among processes
    MPI_Scatter(A, elements_per_proc, MPI_INT, local_A, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(B, elements_per_proc, MPI_INT, local_B, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    // Compute local dot product
    for (int i = 0; i < elements_per_proc; i++) {
        local_dot += local_A[i] * local_B[i];
    }

    // Reduce partial dot products to get the final result
    MPI_Reduce(&local_dot, &global_dot, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print final result at process 0
    if (rank == 0) {
        printf("\nParallel Dot Product: %d\n", global_dot);
    }

    MPI_Finalize();
    return 0;
}
