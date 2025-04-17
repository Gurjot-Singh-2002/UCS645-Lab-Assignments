# ASSIGNMENT 5 Codes Description  

**Prog 1:** vector_add.cu  
Vector Addition Using CUDA with Performance Profiling    
This program performs element-wise vector addition of two arrays A and B using CUDA and calculates both theoretical and measured memory bandwidth. It also records and displays the kernel execution time using CUDA events. The implementation uses statically defined global memory accessible from both host and device via unified memory.   

**Working:**   
1. Statically Defined Global Memory  
• Vectors A, B, and C are declared using __device__ __managed__, allowing access from both host and device without the need for explicit cudaMalloc or cudaMemcpy.  
• The size N is fixed at compile time (#define N 1024), satisfying the requirement for static memory.  
2. Kernel Launch for Vector Addition  
• A CUDA kernel vectorAdd is launched with a grid-stride loop where each thread computes a single element of the result vector C[i] = A[i] + B[i].  
• Threads and blocks are calculated to ensure full coverage of the vector size.  
3. Kernel Execution Time Measurement  
• CUDA events (cudaEvent_t) are used to time only the kernel execution.  
• The time in milliseconds is calculated using cudaEventElapsedTime() and printed to the console.  
4. Theoretical Bandwidth Calculation  
• Device properties such as memoryClockRate and memoryBusWidth are queried using cudaGetDeviceProperties.  
• The theoretical bandwidth is calculated using the formula:  
theoreticalBW= (2*memoryClockRate (Hz)*memoryBusWidth (bits))/8*10^9  GB/s  
• This value is printed to indicate the maximum bandwidth the GPU could theoretically achieve.  
5. Measured Bandwidth Calculation  
• The kernel reads vectors A and B (2 reads) and writes to C (1 write).  
• Total data moved is: 2 * N * sizeof(float) + N * sizeof(float).  
• Measured bandwidth is computed using the formula:  
measuredBW= (totalBytes/executionTime(s)) / 10^9 GB/s  
• This provides the effective bandwidth utilized by the kernel, allowing comparison with the theoretical value.  

**Output:**  
C = [0.0 3.0 6.0 9.0 12.0 ...]    
Theoretical Bandwidth: 320.06 GB/s  
Measured Bandwidth: 0.01 GB/s   
Execution Time: 1.2886 ms  
