#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Monte Carlo function to estimate the number of points inside the quarter-circle
int monte_carlo_pi(int num_samples) {
    int inside_circle = 0;
    for (int i = 0; i < num_samples; i++) {
        double x = (double)rand() / RAND_MAX;  // Random x in [0,1]
        double y = (double)rand() / RAND_MAX;  // Random y in [0,1]
        if (x * x + y * y <= 1.0) {
            inside_circle++;
        }
    }
    return inside_circle;
}

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);  // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int TOTAL_SAMPLES = 1000000;  // Total number of random points
    int local_samples = TOTAL_SAMPLES / size;  // Divide work across processes

    srand(time(NULL) + rank);  // Seed random number generator

    // Each process estimates Pi locally
    int local_inside = monte_carlo_pi(local_samples);

    int global_inside = 0;
    // Reduce all local results to rank 0 (master process)
    MPI_Reduce(&local_inside, &global_inside, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {  // Master process computes final Pi estimate
        double pi_estimate = 4.0 * global_inside / TOTAL_SAMPLES;
        printf("Estimated Pi: %f\n", pi_estimate);
    }

    MPI_Finalize();  // Cleanup MPI
    return 0;
}
