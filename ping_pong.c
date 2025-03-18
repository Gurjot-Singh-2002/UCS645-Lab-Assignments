#include <mpi.h>
#include <stdio.h>

#define PING_PONG_LIMIT 10  // Define the number of exchanges

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank and size of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Ensure only two processes are used
    if (world_size != 2) {
        fprintf(stderr, "This program requires exactly two processes\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int ping_pong_count = 0;
    int partner_rank = (world_rank + 1) % 2; // Determine the other process

    while (ping_pong_count < PING_PONG_LIMIT) {
        if (world_rank == ping_pong_count % 2) {
            // Increment and send the ping-pong count
            ping_pong_count++;
            MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            printf("Process %d sent and incremented ping_pong_count %d to process %d\n",
                   world_rank, ping_pong_count, partner_rank);
        } else {
            // Receive the ping-pong count
            MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process %d received ping_pong_count %d from process %d\n",
                   world_rank, ping_pong_count, partner_rank);
        }
    }

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
