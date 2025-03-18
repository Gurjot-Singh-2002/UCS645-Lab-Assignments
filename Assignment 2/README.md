# ASSIGNMENT 2 Codes Description

**Prog 1:** monte_pi.c  
Estimating π using Monte Carlo with MPI  
This program estimates the value of π (Pi) using the Monte Carlo method in parallel with MPI. Random points are generated inside a unit square, and the ratio of points inside a quarter-circle to the total points is used to approximate π.  

**Working:**  
Master Process (Rank 0):  
•	Distributes work among processes.
•	Collects results and computes the final estimate.  
Slave Processes:  
•	Generate random points and count points inside the circle.  
•	Return partial results to the master using MPI_Reduce.  

**Output:** For n=2  
Estimated Pi: 3.140604  

**Prog 2:** matrix_multiply.c  
MPI Matrix Multiplication  
This MPI program performs matrix multiplication on a 70x70 matrix and compares the serial and parallel execution times.   

**Working:**  
Serial Multiplication:  
•	Performed on rank 0 using a simple nested loop.  
•	Time measured using MPI_Wtime().  
Parallel Multiplication:  
•	Matrix rows are scattered across processes.  
•	Matrix B is broadcasted to all processes.  
•	Each process computes its portion and results are gathered back.  
•	Time measured after MPI_Barrier() for accurate synchronization.  
Final Output:  
•	Displays the execution time for both serial and parallel methods.  

**Output:** For n=2  
Serial Execution Time: 0.001765 seconds  
Parallel Execution Time: 0.000705 seconds   

**Prog 3:** parallel_sort.c  
Parallel Odd-Even Sort using MPI    
To Sort an array in parallel using the odd-even sort algorithm.     

**Working:**  
•	Initialize MPI: Split array among processes.  
•	Scatter Data: Distribute parts of the array to processes.  
•	Local Sorting: Each process sorts its local data.  
•	Gather Data: Collect sorted data from processes.  
•	Print Result: Rank 0 displays the sorted array.  

**Output:** For n=2  
Unsorted Array: 41 67 34 0 69 24 78 58  
Sorted Array: 0 34 41 67 24 58 69 78  

**Prog 4:** heat_distribute.c  
Heat Distribution Simulation using MPI  
This program simulates heat distribution along a 1D rod using MPI to parallelize the computation. The rod starts with fixed temperatures at the ends and distributes heat iteratively across the interior points.  

**Working:**  
Master Process (Rank 0):  
•	Initializes the temperature along the rod:  
•	Left end at 100.0°C  
•	Right end at 50.0°C  
•	Interior points set to 0.0°C initially  
•	Distributes sections of the rod to all processes using MPI_Scatter.  
All Processes:  
•	Each process receives a portion of the rod (local_chunk) to calculate heat diffusion.  
•	Boundary values are exchanged with neighboring processes using MPI_Send and MPI_Recv for smooth heat flow.  
Heat Iteration (100 iterations):  
•	Boundary values are averaged with neighboring values.  
•	Interior points update their temperature using the average of their adjacent values.  
•	Updated values are stored in new_chunk and copied back to local_chunk.  
Final Step:  
•	All processes send their updated chunks to the master using MPI_Gather.  
•	The master process prints the final temperature distribution of the rod.  

**Output:** For n=2  
Final Temperature Distribution:  
95.05 90.09 85.40 80.70 76.45 72.20 68.49 64.78 61.58 58.38 55.55 52.71  

**Prog 5:**  parallel_reduce.c  
Parallel Reduction using MPI  
This program demonstrates parallel reduction using MPI to compute the sum of values across multiple processes.  

**Working:**  
Initialization:  
•	MPI_Init() initializes the environment.  
•	Each process gets its rank and size using MPI_Comm_rank() and MPI_Comm_size().  
Local Value:  
•	Each process sets its local value as rank + 1.  
Reduction:  
•	MPI_Reduce() performs a sum reduction of all local values and sends the result to rank 0.  
Result Display:  
•	Rank 0 prints the total sum.  

**Output:** For n=2   
Total Sum using MPI_Reduce: 3  

**Prog 6:**  parallel_dotprod.c  
Parallel Dot Product using MPI  
This program computes the dot product of two vectors in parallel using MPI.  

**Working:**  
Initialization:  
•	MPI_Init() initializes MPI.  
•	Each process gets its rank and size using MPI_Comm_rank() and MPI_Comm_size().  
Vector Initialization (Rank 0):  
•	Vector A: {1, 2, 3, ..., N}  
•	Vector B: {8, 7, 6, ..., 1}  
Scatter Data:  
•	MPI_Scatter() distributes parts of vectors A and B to all processes.  
Local Dot Product Calculation:  
•	Each process computes the dot product of its assigned elements.  
Reduction:  
•	MPI_Reduce() sums up all partial dot products and sends the result to rank 0.  
Result:  
•	Rank 0 prints the final dot product.  

**Output:** For n=2  
Vector A:  
1 2 3 4 5 6 7 8  
Vector B:  
8 7 6 5 4 3 2 1  
Parallel Dot Product: 120  

**Prog 7:** parallel_prefixsum.c  
Parallel Prefix Sum (Scan) using MPI  
This program computes the prefix sum (cumulative sum) of an array in parallel using MPI.  

**Working:**  
Initialization:  
•	MPI_Init() starts MPI.  
•	Rank 0 initializes the array: {1, 2, 3, ..., N}  

Scatter and Local Prefix Sum:  
•	MPI_Scatter() splits the array across processes.  
•	Each process computes the prefix sum of its local segment.  

Correction Factor:  
•	Each process receives a correction factor from the previous process to adjust its prefix sum.  

Gather and Final Output:  
•	MPI_Gather() collects results at rank 0, which prints the final prefix sum.  

**Output:** For n=2  
Input Array:  
1 2 3 4 5 6 7 8  
Parallel Prefix Sum: 1 3 6 10 15 21 28 36  

**Prog 8:** parallel_matrixtranspose.c  
Parallel Matrix Transposition using MPI  
This program transposes a matrix in parallel using MPI.  

**Working:**  
Initialization:  
•	MPI_Init() starts MPI.  
•	Rank 0 initializes an N x N matrix  

Scatter Rows:  
•	MPI_Scatter() distributes matrix rows among processes.  

Local Transposition:  
•	Each process transposes its local rows and stores them as columns.  

Gather Transposed Rows:  
•	MPI_Gather() collects the transposed sub-matrices into the final matrix.  

Output Result:  
•	Rank 0 prints the transposed matrix  

**Output:**  For n=2
Original Matrix:  
1 2 3 4  
5 6 7 8  
9 10 11 12  
13 14 15 16   

Transposed Matrix:  
1 5 2 6  
3 7 4 8   
9 13 10 14   
11 15 12 16  


