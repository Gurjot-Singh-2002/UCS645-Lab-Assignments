# ASSIGNMENT 4 Codes Description

**Prog 1:** sumofn.cu  
CUDA Sum of First N Integers (Different Thread Tasks)  
This CUDA program demonstrates how different GPU threads can perform distinct tasks in parallel. Specifically, it calculates the sum of the first 1024 integers using two methods—one using an iterative approach and the other using a mathematical formula.  

**Overview:**  

1. Initialization:  
• Host arrays are created to hold input and output data.  
• The input array is filled with values from 0 to 1023.  
• Device memory is allocated for both input and output arrays, and the input is copied from host to device.  
2. Parallel Execution (CUDA Kernel):  
• The kernel is launched with 1 block and 2 threads.  
• Thread 0 computes the sum iteratively using a loop.  
• Thread 1 computes the sum using the formula: N * (N - 1) / 2.  
• Both results are stored in different positions of the output array.  
3. Timing (GPU):  
• CUDA events (cudaEventRecord) are used to measure GPU kernel execution time in milliseconds.  
4. Result Output:  
• The final results from both threads are copied back to the host.  
• The program prints the iterative sum, formula sum, and GPU execution time.  

**Output:**  
Sum using Iteration (Thread 0): 523776  
Sum using Formula   (Thread 1): 523776  
GPU Kernel Execution Time: 0.147424 ms  

**Prog 2(a):** sumofn.cu  
Pipelined Merge Sort (CPU Parallelization Concept)  
This C program implements merge sort on an array of 1000 elements.  

**Overview:**  
1. Initialization:  
• An array arr of size N = 1000 is filled with random integers between 0 and 999.  
2. Recursive Merge Sort with Pipelined Logic:  
• The array is recursively divided into halves using the mergeSort() function.  
• Each half is independently sorted through recursive calls.  
• The merge() function is used to combine two sorted subarrays into one.  
• This recursive division and merging simulate the pipelining stages in a parallel system:  
  • Stage 1: Divide the array recursively.  
  • Stage 2: Process (sort) the smaller subarrays.  
  • Stage 3: Merge results from earlier stages into a sorted array.  
3. Timing (CPU):  
• Execution time is measured using clock() before and after sorting.  
• The time difference is converted to milliseconds and printed.  
4. Result Output:  
• The first 10 elements of the sorted array are displayed.  
• The total CPU execution time is printed for performance insight.  

**Output:**  
Sorted array (first 10):  
0 0 2 2 4 6 8 9 10 11   
CPU Execution Time: 0.2030 ms  

**Prog 2(b):** cuda_merge_sort.cu  
CUDA Parallel Merge Sort  
This CUDA program implements merge sort on a 1000-element array using GPU-based parallelism. It utilizes iterative merging with CUDA kernels to speed up the sorting process by processing subarrays concurrently on different threads.  

**Overview:**  
1. Initialization:  
• A host array h_arr of size N = 1000 is initialized with random integers.  
• Device memory (d_arr and d_temp) is allocated to hold the array and a temporary buffer on the GPU.  
• The host array is copied to device memory for processing.  
2. Parallel Merge Sort (CUDA):  
• Sorting is performed in log(N) stages, where each stage doubles the width of the subarrays being merged.  
• In each stage:  
  • A CUDA kernel mergeSortKernel is launched to sort pairs of subarrays in parallel.  
  • Each thread handles the merging of two adjacent sorted subarrays of size width.  
  • The kernel uses a device-side merge() function to perform the merge operation and stores intermediate results in a temporary device array d_temp.  
3. Timing (GPU):  
• CUDA events (cudaEventRecord) are used to measure GPU execution time.  
• The time taken for the entire merge sort process is computed and displayed in milliseconds.  
4. Result Output:  
• The sorted array is copied back from device to host.  
• The first 10 sorted values are printed for verification.  
• The total execution time on the GPU is displayed.  

**Output:**  
Sorted array (first 10):  
0 0 2 2 4 6 8 9 10 11   
Execution time (GPU): 1.2908 ms  

**Part (c):**  Performance Comparison  
Output Consistency:  
• Both implementations produce the same sorted output, confirming the correctness of both approaches.  
• Example (first 10 sorted elements): 0 0 2 2 4 6 8 9 10 11  

Execution Time:  
• CPU (Pipelined Merge Sort): 0.2030 ms  
• GPU (CUDA Merge Sort): 1.2908 ms  

Observation:  
• The CPU-based pipelined implementation outperformed the CUDA-based implementation for array size N = 1000.  
• This is likely due to:  
  • Small input size not fully utilizing GPU parallelism.  
  • Overhead of memory allocation, data transfer, and kernel launches on the GPU.  

Conclusion:  
• For smaller datasets, CPU-based merge sort may perform better due to lower overhead.  
• GPU-based merge sort is expected to scale better and outperform the CPU version for larger input sizes where parallelism can be effectively exploited.  
