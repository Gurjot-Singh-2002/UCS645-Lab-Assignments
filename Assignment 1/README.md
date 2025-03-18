# ASSIGNMENT 1 Codes Desciption
**Prog 1:** hello.c  
MPI Hello World  
This is a simple MPI program that prints a "Hello World" message from each process in a distributed system.  

**Overview:**  
•	Initializes the MPI environment using MPI_Init.  
•	Retrieves process information, including: Total number of processes (MPI_Comm_size), Current process rank (MPI_Comm_rank), Processor name (MPI_Get_processor_name).  
•	Each process prints a greeting message, displaying its rank and total process count.  
•	Finalizes the MPI environment using MPI_Finalize.  

**Output:** For n=2  
Hello world from processor LAPTOP-IDKPRONM, rank 0 out of 2processors  
Hello world from processor LAPTOP-IDKPRONM, rank 1 out of 2processors  


**Prog 2:** send_recv.c  
MPI send/recv  
This MPI program demonstrates basic message passing between two processes using MPI_Send and MPI_Recv.  

**Overview:**  
•	Process 0 initializes an integer (-1) and sends it to Process 1.  
•	Process 1 receives the number and prints it.  
•	Uses point-to-point communication (MPI_Send and MPI_Recv).  

**Output:** For n=2  
Process 1 received number -1 from process 0  
Process 0 sent number -1 to process 1  

**Prog 3:** ping_pong.c  
MPI Ping-Pong Communication  
This MPI program demonstrates message passing between two processes using MPI_Send and MPI_Recv in a ping-pong fashion. The processes take turns sending and receiving a counter value until it reaches a defined limit.  

**Overview:**  
•	The program requires exactly two processes to execute.  
•	A variable ping_pong_count is passed back and forth between Process 0 and Process 1.  
•	Each time a process sends the value, it increments it.  
•	The process that has the value sends it to the other until the limit (PING_PONG_LIMIT) is reached.  

**Output:** For n=2  
Process 0 sent and incremented ping_pong_count 1 to process 1  
Process 0 received ping_pong_count 2 from process 1  
Process 0 sent and incremented ping_pong_count 3 to process 1  
Process 0 received ping_pong_count 4 from process 1  
Process 0 sent and incremented ping_pong_count 5 to process 1  
Process 0 received ping_pong_count 6 from process 1  
Process 0 sent and incremented ping_pong_count 7 to process 1  
Process 0 received ping_pong_count 8 from process 1  
Process 0 sent and incremented ping_pong_count 9 to process 1  
Process 0 received ping_pong_count 10 from process 1  
Process 1 received ping_pong_count 1 from process 0  
Process 1 sent and incremented ping_pong_count 2 to process 0  
Process 1 received ping_pong_count 3 from process 0  
Process 1 sent and incremented ping_pong_count 4 to process 0  
Process 1 received ping_pong_count 5 from process 0  
Process 1 sent and incremented ping_pong_count 6 to process 0  
Process 1 received ping_pong_count 7 from process 0  
Process 1 sent and incremented ping_pong_count 8 to process 0  
Process 1 received ping_pong_count 9 from process 0  
Process 1 sent and incremented ping_pong_count 10 to process 0  

**Prog 4:** ring.c  
MPI Token Ring Passing  
This MPI program demonstrates token passing in a ring topology using MPI_Send and MPI_Recv. The token is passed sequentially from Process 0 to Process (N-1) and then back to Process 0, forming a ring communication pattern.  

**Overview:**  
•	Process 0 initializes a token (value -1) and starts passing it.  
•	Each process receives the token from its previous process, prints it, and then forwards it to the next process.  
•	The last process sends the token back to Process 0, completing the ring.  

**Output:** n=2  
Process 0 received token -1 from process 1  
Process 1 received token -1 from process 0  

**Prog 5:** check_status.c  
MPI Random Number Communication  
This MPI program demonstrates point-to-point communication between two processes using MPI_Send and MPI_Recv.  

**Overview:**  
•	Process 0 generates a random number of integers (between 1 and 100) and fills an array with random values.  
•	It then sends the array to Process 1.  
•	Process 1 receives the array, retrieves the number of received elements, and prints them.   

**Output:** For n=2  
Process 0 sent 6 numbers to process 1  
Process 1 received 6 numbers from process 0. Source = 0, Tag = 0  
Received numbers: 407 815 630 252 775 116  

**Prog 6:** probe.c  
MPI Dynamic Message Receiving with Probe  
This MPI program demonstrates dynamic message reception using MPI_Probe and MPI_Get_count. Instead of assuming a fixed message size, the program dynamically allocates memory for the received data.  

**Overview:**  
Process 0 generates a random number of integers and sends them to Process 1.  
Process 1:  
•	Uses MPI_Probe to check the incoming message without receiving it immediately.  
•	Retrieves the exact number of elements in the message using MPI_Get_count.  
•	Dynamically allocates memory to store the received data.  
•	Receives and prints the numbers for verification.  

**Output:** For n=2  
Process 1 dynamically received 78 numbers from process 0.  
Received numbers: 931 990 124 364 585 83 467 57 466 133 389 471 655 825 814 424 852 519 788 997 934 703 544 276 514 515 153 884 919 801 701 997 215 949 106 171 762 332 492 509 268 859 264 176 24 753 560 354 613 666 751 620 152 974 680 479 986 489 906 314 267 428 455 202 494 972 677 396 831 242 508 119 979 955 361 366 559 193  
Process 0 sent 78 numbers to process 1  

**Prog 7:** random_walk.c  
MPI Random Walk Simulation  
This MPI program simulates a random walk process where multiple "walkers" take steps and get passed between processes in a ring topology. Each walker starts with a random number of steps and moves forward until it completes its journey.  

**Overview:**  
•	Each process starts with NUM_WALKERS walkers, each having a random step count (1 to WALKER_STEPS).  
•	Walkers decrease their step count at each iteration.  
•	When a walker completes its steps, it is sent to the next process in the ring.  
•	Walkers are received from the previous process using MPI_Iprobe to check for incoming data.  
•	A barrier synchronization (MPI_Barrier) ensures all processes stay in sync after each step.  

**Output:** For n=2  
Process 1: Initialized 5 walkers  
Process 0: Initialized 5 walkers   
Process 1: Sent walker 2 to Process 0  
Process 0: Sent walker 0 to Process 1  
Process 0: Received walker from Process 1  
Process 1: Received walker from Process 0  
Process 1: Sent walker 4 to Process 0  
Process 0: Received walker from Process 1  
Process 1: Sent walker 0 to Process 0  
Process 0: Received walker from Process 1  
Process 0: Sent walker 2 to Process 1  
Process 0: Sent walker 3 to Process 1  
Process 1: Received walker from Process 0  
Process 0: Sent walker 4 to Process 1  
Process 1: Sent walker 1 to Process 0  
Process 0: Received walker from Process 1  
Process 1: Received walker from Process 0  
Process 1: Received walker from Process 0  
Process 1: Finished execution!  
Process 0: Finished execution!  



