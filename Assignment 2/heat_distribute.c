#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 12      // Number of points in the rod
#define ITER 100  // Number of iterations
#define LEFT_TEMP 100.0   // Fixed temperature at the left end
#define RIGHT_TEMP 50.0   // Fixed temperature at the right end

int main(int argc, char *argv[]) {
    int rank, size, i, iter;
    double local_data[N], new_data[N], left_neighbor, right_neighbor;
    int chunk_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    chunk_size = N / size;  // Divide the rod among processes
    double local_chunk[chunk_size], new_chunk[chunk_size];

    // Initialize temperature distribution (0 everywhere except boundaries)
    if (rank == 0) {
        for (i = 0; i < N; i++) {
            if (i == 0) local_data[i] = LEFT_TEMP;
            else if (i == N - 1) local_data[i] = RIGHT_TEMP;
            else local_data[i] = 0.0;
        }
    }

    // Scatter the data to processes
    MPI_Scatter(local_data, chunk_size, MPI_DOUBLE, local_chunk, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Iterate for heat distribution
    for (iter = 0; iter < ITER; iter++) {
        left_neighbor = (rank == 0) ? LEFT_TEMP : 0.0;
        right_neighbor = (rank == size - 1) ? RIGHT_TEMP : 0.0;

        // Exchange boundary values with neighboring processes
        if (rank > 0) {
            MPI_Send(&local_chunk[0], 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&left_neighbor, 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if (rank < size - 1) {
            MPI_Send(&local_chunk[chunk_size - 1], 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&right_neighbor, 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        // Update temperatures using the average of neighboring values
        new_chunk[0] = (left_neighbor + local_chunk[1]) / 2.0;
        for (i = 1; i < chunk_size - 1; i++) {
            new_chunk[i] = (local_chunk[i - 1] + local_chunk[i + 1]) / 2.0;
        }
        new_chunk[chunk_size - 1] = (local_chunk[chunk_size - 2] + right_neighbor) / 2.0;

        // Copy new values to local chunk
        for (i = 0; i < chunk_size; i++) {
            local_chunk[i] = new_chunk[i];
        }
    }

    // Gather the updated data
    MPI_Gather(local_chunk, chunk_size, MPI_DOUBLE, new_data, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Print final temperature distribution
    if (rank == 0) {
        printf("Final Temperature Distribution:\n");
        for (i = 0; i < N; i++) {
            printf("%.2f ", new_data[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
