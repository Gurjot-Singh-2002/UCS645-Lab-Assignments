#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 8  // Size of the input array

void print_array(int *arr, int size, const char *msg) {
    printf("%s: ", msg);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int rank, size;
    int arr[N], local_data[N], prefix_sum[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int elements_per_proc = N / size;

    // Initialize the input array in process 0
    if (rank == 0) {
        printf("Input Array:\n");
        for (int i = 0; i < N; i++) {
            arr[i] = i + 1;  // Example: {1, 2, 3, 4, 5, 6, 7, 8}
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    // Scatter data among processes
    MPI_Scatter(arr, elements_per_proc, MPI_INT, local_data, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    // Compute local prefix sum
    for (int i = 1; i < elements_per_proc; i++) {
        local_data[i] += local_data[i - 1];
    }

    // Send prefix sum to next process
    int correction_factor = 0;
    if (rank != 0) {
        MPI_Recv(&correction_factor, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i < elements_per_proc; i++) {
            local_data[i] += correction_factor;
        }
    }

    if (rank != size - 1) {
        MPI_Send(&local_data[elements_per_proc - 1], 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    // Gather results back at process 0
    MPI_Gather(local_data, elements_per_proc, MPI_INT, prefix_sum, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    // Print final result
    if (rank == 0) {
        print_array(prefix_sum, N, "Parallel Prefix Sum");
    }

    MPI_Finalize();
    return 0;
}
