#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBERS 100  // Define max array size

int main(int argc, char** argv) {
    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank and size of processes
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int numbers[MAX_NUMBERS];
    int number_amount = 0;

    if (world_rank == 0) {
        // Initialize random seed
        srand(time(NULL));

        // Generate a random number of integers to send (between 1 and MAX_NUMBERS)
        number_amount = (rand() % MAX_NUMBERS) + 1;

        // Fill the array with random numbers
        for (int i = 0; i < number_amount; i++) {
            numbers[i] = rand() % 1000; // Random values between 0 and 999
        }

        // Send the numbers to process 1
        MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent %d numbers to process 1\n", number_amount);
    } else if (world_rank == 1) {
        MPI_Status status;

        // Receive at most MAX_NUMBERS from process 0
        MPI_Recv(numbers, MAX_NUMBERS, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        // Get the actual count of received numbers
        MPI_Get_count(&status, MPI_INT, &number_amount);

        // Print received details
        printf("Process 1 received %d numbers from process 0. Source = %d, Tag = %d\n",
               number_amount, status.MPI_SOURCE, status.MPI_TAG);

        // Print received numbers for verification
        printf("Received numbers: ");
        for (int i = 0; i < number_amount; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}
