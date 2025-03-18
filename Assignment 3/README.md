# ASSIGNMENT 3 Codes Desciption

**Prog 1:** daxpy_prog.c  
MPI DAXPY Operation  
This MPI program performs the DAXPY operation in parallel:  
X=a⋅X+Y  
where a is a scalar, and X and Y are vectors. The computation is distributed across multiple MPI processes for improved performance.  

**Overview:**  
1. Initialization:  
•	MPI is initialized, and the number of processes (size) and rank (rank) are determined.  
•	Vector size (N = 2^16) is divided equally among all processes.  
2. Parallel DAXPY (MPI):  
•	Each process performs the DAXPY operation (X = a * X + Y) on its local portion.  
•	Time is measured using MPI_Wtime() and synchronized with MPI_Barrier().  
3. Serial DAXPY (Uniprocessor):  
•	Only process 0 performs the same DAXPY operation on the entire vector.  
•	Time is measured using clock_gettime().  
4. Speedup Calculation:  
•	Speedup is calculated as: Speedup=Serial Time/MPI Time   
•	Results are printed by rank 0.  

**Output:** For n=2  
MPI DAXPY time: 0.000120 seconds  
Uniprocessor DAXPY time: 0.000157 seconds  
Speedup (Serial/MPI): 1.30  

**Prog 2:** pi.c  
Calculation of pi using MPI_Bcast and MPI_Reduce  
This program is a parallel implementation of the numerical integration method to approximate the value of π using MPI (Message Passing Interface). The serial version computes π using the Midpoint Rule, but in this version, multiple processes will collaborate to compute the final result using MPI_Bcast and MPI_Reduce.  

**Working:**  
1.	Broadcasting Total Steps (MPI_Bcast)  
•	The total number of steps (num_steps) is broadcasted from process 0 to all other processes using MPI_Bcast.  
•	This ensures that all processes have the same value for computation.  

2.	Parallel Computation of Partial Sums  
•	Each process computes a portion of the summation independently.  
•	Instead of a single loop, each process iterates over its assigned indices (i = rank, i < num_steps, i += size).  
•	This distributes the computational load across available processes.  

3.	Reduction of Partial Results (MPI_Reduce)  
•	Each process computes a partial sum of the integral and sends it to process 0 using MPI_Reduce.  
•	The final summation and multiplication by the step size are performed in process 0 to obtain the approximate value of π.  

4.	Execution Time Measurement  
•	The program measures execution time using MPI_Wtime() to analyze performance improvements.

**Output:** For n=2  
Approximate value of pi: 3.1415926535981016  
Time taken: 0.000616 seconds  

**Prog 3:** findprime.c  
Finding Prime Numbers using MPI_Send and MPI_Recv  
This MPI-based parallel program finds all prime numbers up to a given maximum value using a Master-Slave model. The master process assigns numbers to be tested, and the slave processes check whether the numbers are prime and return results.    
The communication between master and slaves is handled using MPI_Send and MPI_Recv:  
•	Slaves request numbers to test by sending 0 to the master.  
•	The master assigns numbers to slaves and waits for results.  
•	If the number is prime, the slave sends it back as a positive number.  
•	If the number is not prime, the slave sends back its negative value.  
•	Once all numbers are tested, the master sends a termination signal (-1) to all slaves.  

**Working:**
Master Process (Rank 0)  
1.	Starts from 2 (since 1 is not prime).  
2.	Waits for requests from any slave using MPI_Recv (MPI_ANY_SOURCE).  
3.	If a request is received:  
•	If the message is 0, the slave is asking for a number, then send the next number.  
•	If the message is positive, it means the number is prime, then print it.  
•	If the message is negative, the number is not prime, then ignore it.  
4.	After testing all numbers, sends a termination signal (-1) to all slaves.  
5.	Prints total prime count after collecting results from all processes.  
Slave Processes (Rank ≥ 1)  
1.	Send 0 to the master to request a number.  
2.	Receive a number to test from the master.  
3.	If the received number is -1, exit (termination signal).  
4.	Check if the number is prime:  
•	If prime, send it back as positive.  
•	If not prime, send it back as negative.  
5.	Repeat steps 1–4 until the termination signal is received.

**Output:** For n=2  
2 is prime  
3 is prime  
5 is prime  
7 is prime   
11 is prime  
13 is prime  
17 is prime  
19 is prime  
23 is prime  
29 is prime  
31 is prime  
37 is prime  
41 is prime  
43 is prime  
47 is prime  
53 is prime    
59 is prime  
61 is prime  
67 is prime  
71 is prime  
73 is prime  
79 is prime  
83 is prime  
89 is prime  
97 is prime  
Total primes found: 25  



 
