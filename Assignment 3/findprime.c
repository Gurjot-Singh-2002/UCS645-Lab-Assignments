#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Function to check if a number is prime
int is_prime(int n) {
    if (n < 2) return 0; // Numbers less than 2 are not prime
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0; // Not prime if divisible by any number
    }
    return 1; // Prime
}

int main(int argc, char **argv) {
    int rank, size;
    int max_value = 100; // Maximum value to test for primes
    int num_primes = 0;  // Count of primes found

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Master process
        int next_number = 2; // Start testing from 2
        int received_number;
        MPI_Status status;

        while (next_number <= max_value) {
            // Receive a request from any slave
            MPI_Recv(&received_number, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

            if (received_number == 0) {
                // Slave is requesting a new number to test
                MPI_Send(&next_number, 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
                next_number++;
            } else {
                // Slave is returning a result
                if (received_number > 0) {
                    printf("%d is prime\n", received_number);
                    num_primes++;
                }
            }
        }

        // Send termination signal to all slaves
        int terminate = -1;
        for (int i = 1; i < size; i++) {
            MPI_Send(&terminate, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        printf("Total primes found: %d\n", num_primes);
    } else {
        // Slave process
        int number_to_test;
        MPI_Status status;

        while (1) {
            // Request a number to test from the master
            int request = 0;
            MPI_Send(&request, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

            // Receive a number to test
            MPI_Recv(&number_to_test, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

            if (number_to_test == -1) {
                // Termination signal received
                break;
            }

            // Test the number for primality
            if (is_prime(number_to_test)) {
                // Send the number back if it is prime
                MPI_Send(&number_to_test, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            } else {
                // Send the negative of the number if it is not prime
                number_to_test = -number_to_test;
                MPI_Send(&number_to_test, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            }
        }
    }

    MPI_Finalize();
    return 0;
}