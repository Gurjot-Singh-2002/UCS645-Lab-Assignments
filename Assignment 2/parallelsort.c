#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 8  // Array size

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void odd_even_sort(int local_data[], int n) {
    for (int phase = 0; phase < n; phase++) {
        for (int i = (phase % 2 == 0) ? 0 : 1; i < n - 1; i += 2) {
            if (local_data[i] > local_data[i + 1]) {
                swap(&local_data[i], &local_data[i + 1]);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size, local_data[N / 2], global_data[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            global_data[i] = rand() % 100;
        }
        printf("Unsorted Array: ");
        for (int i = 0; i < N; i++) printf("%d ", global_data[i]);
        printf("\n");
    }

    MPI_Scatter(global_data, N / size, MPI_INT, local_data, N / size, MPI_INT, 0, MPI_COMM_WORLD);
    odd_even_sort(local_data, N / size);
    MPI_Gather(local_data, N / size, MPI_INT, global_data, N / size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Sorted Array: ");
        for (int i = 0; i < N; i++) printf("%d ", global_data[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
