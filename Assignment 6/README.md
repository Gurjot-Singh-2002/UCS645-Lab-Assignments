# ASSIGNMENT 6 Code Description  

**Prog 1:** sqrt_cuda.cu  
Square Root Computation Using CUDA with Performance Profiling  
This program computes the square root of elements in a large array A and stores the result in array C using CUDA. It measures the kernel execution time for different input sizes using CUDA event profiling and outputs the performance results. The goal is to analyze the cost of a computationally expensive operation (square root) on the GPU for increasing data sizes.  

**Working:**   
1. Dynamic Memory Allocation  
• Arrays A and C are allocated on the host using malloc() and on the device using cudaMalloc().  
• Data is explicitly transferred between host and device using cudaMemcpy() for input and output arrays.  
• This approach allows handling large vectors whose sizes are not known at compile time.  

2. Kernel Launch for Square Root Operation  
• The CUDA kernel sqrtKernel is launched with one thread per element to compute C[i] = sqrtf(A[i]).  
• The number of blocks and threads per block are calculated dynamically to cover the full size of the array.  

3. Kernel Execution Time Measurement  
• CUDA events (cudaEvent_t) are used to record the start and end of kernel execution.  
• Elapsed time is computed using cudaEventElapsedTime() and printed in milliseconds.  
• This provides a precise measurement of only the kernel runtime, excluding memory allocation and transfers.  

4. Input Size Scaling and Testing  
• The kernel is tested with array sizes of 50,000, 500,000, 5,000,000, and 50,000,000 elements.  
• For each size, the program prints the execution time to help assess GPU scalability with computational complexity.  

5. Performance Visualization (External via CSV)  
• The output timings are saved to an Excel file and plotted using Excel to visualize performance trends.  
• This helps demonstrate the relationship between input size and GPU execution time for computational tasks like sqrt().

**Output:**  
N = 50000, Time = 0.1689 ms  
N = 500000, Time = 0.0274 ms  
N = 5000000, Time = 0.1908 ms  
N = 50000000, Time = 1.8307 ms  

**Graph:**  
![image](https://github.com/user-attachments/assets/b758161e-24d0-4b6f-8a91-1d4daa69759a)

