#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the rank and size of the processes
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int number_amount;
    
    if (world_rank == 0) {
        const int MAX_NUMBERS = 100;
        int numbers[MAX_NUMBERS];

        // Initialize random seed
        srand(time(NULL));

        // Pick a random amount of numbers to send (between 1 and MAX_NUMBERS)
        number_amount = (rand() % MAX_NUMBERS) + 1;

        // Fill the array with random numbers
        for (int i = 0; i < number_amount; i++) {
            numbers[i] = rand() % 1000;  // Random values between 0-999
        }

        // Send the random amount of numbers to process 1
        MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent %d numbers to process 1\n", number_amount);
    } 
    else if (world_rank == 1) {
        MPI_Status status;

        // Probe for an incoming message from process 0
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);

        // Get the number of elements in the message
        MPI_Get_count(&status, MPI_INT, &number_amount);

        // Dynamically allocate a buffer for incoming data
        int* number_buf = (int*)malloc(sizeof(int) * number_amount);

        // Receive the numbers
        MPI_Recv(number_buf, number_amount, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 dynamically received %d numbers from process 0.\n", number_amount);

        // Print received numbers for verification
        printf("Received numbers: ");
        for (int i = 0; i < number_amount; i++) {
            printf("%d ", number_buf[i]);
        }
        printf("\n");

        // Free dynamically allocated memory
        free(number_buf);
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}
