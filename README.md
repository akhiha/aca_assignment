# Advanced Computer Architecture

## Akhila Matathammal -2023801001

### 1. On Vector Instruction Sets

#### a. Write a scalar program to compute the dot product of two vectors

- Code File: `1a.c`

- Commands to run for executing the file in Ubuntu
  - Compile the file
    ```shell
    gcc -fopenmp -o 1a 1a.c
    ```
  - Execute the Program
    ```shell
    ./1a
    ```

- Output
  
![image](https://github.com/akhiha/aca_assignment/assets/24610167/075faf06-c16c-48fd-9b30-41d61571a889)


#### b. Write a vectorized version of the dot product program.

- Performing the vectorized version of dot product using SSE(Streaming SIMD Extensions) and AVX(Advanced Vector Extensions) for x86 processors.
- SSE:
  - Code File: `1b_sse.c`
    
  - Commands to run:
    - Compile the file
      ```shell
      gcc -fopenmp -o dot_product_sse 1b_sse.c -msse
      ```
    - Execute the Program
      ```shell
      ./dot_product_sse
      ```
      
  - Output

    ![image](https://github.com/akhiha/aca_assignment/assets/24610167/62b851fd-a277-4969-bd99-8d8ff0ece030)

- AVX:
  - Code File: `1b_avx.c`
    
  - Commands to run:
    - Compile the file
      ```shell
      gcc -fopenmp -o dot_product_sse 1b_sse.c -msse
      ```
    - Execute the Program
      ```shell
      ./dot_product_sse
      ```

  - Output:

    ![image](https://github.com/akhiha/aca_assignment/assets/24610167/7dac7347-98be-4751-b9aa-00a7d2325a7d)


#### c. Write a program using vector instructions to compute the dot product of elements at even indices (Σn/2i=0x2i ∗ y2i).

- Code File: `1c.c`
  
- Commands to run:
  - Compile the file
    ```shell
    gcc -fopenmp -o dot_product_even_avx 1c.c -mavx
    ``` 
  - Execute the Program
    ```shell
    ./dot_product_even_avx
    ```

- Output

  ![image](https://github.com/akhiha/aca_assignment/assets/24610167/9d4f092c-1f49-46aa-871c-1a3e4afddaf9)


#### d. Write a program to compute the memory bandwidth of your system.

- Code File: `1d.c`

- Commands to run:
  - Compile the file using avx:
    ```shell
    gcc -o memory_bandwidth 1d.c -mavx -O3
    ```
  - Execute the program:
    ```shell
    ./memory_bandwidth
    ```

- Output

  ![image](https://github.com/akhiha/aca_assignment/assets/24610167/13e465f8-36ba-4ec6-99f9-47776185a575)


#### e. Compute peak GFlops/sec for your system

- Code File: `1e.c`

- Commands to run:
  - Compile the file using avx:
    ```shell
    gcc -o peak_gflops 1e.c -mavx2 -O3
    ```
  - Execute the program:
    ```shell
    ./peak_gflops 
    ```

- Output:

  ![image](https://github.com/akhiha/aca_assignment/assets/24610167/8dda03b7-6f3f-4c0e-bca0-bd67f5adf90d)


#### f. For the above problems a), b), c), check if the programs are memory bound or compute bound.

*a. Scalar Dot product *

- Code File: `1f_a.c`

- Commands to run:
  - Compile the file using avx:
    ```shell
    gcc -fopenmp -o scalar_dot_product_bound 1f_a.c
    ```
  - Execute the program:
    ```shell
    ./scalar_dot_product_bound
    
- Output:

  ![image](https://github.com/akhiha/aca_assignment/assets/24610167/985c255a-08c8-4180-9fc8-346c80fe6916)


*b. Vectorized Version of Dot Product *

- Code File: `1f_b.c`

- Commands to run:
  - Compile the file using avx:
    ```shell
    gcc -o vectorized_dot_product_bound 1f_b.c -mavx -O3
    ```
  - Execute the program:
    ```shell
    ./vectorized_dot_product_bound
    
- Output:

  ![image](https://github.com/akhiha/aca_assignment/assets/24610167/87b0baef-7a2a-4f14-b850-92433e865d6a)


*c. Even Indices *

- Code File: `1f_c.c`

- Commands to run:
  - Compile the file using avx:
    ```shell
    gcc -o vectorized_dot_product_avx_even 1f_c.c -mavx -O3
    ```
  - Execute the program:
    ```shell
    ./dot_product_avx_even
    
- Output:

  ![image](https://github.com/akhiha/aca_assignment/assets/24610167/c2f048ad-a42b-4c83-8aa4-7772418de4ff)


### 2. on memory hierarchies and performance counters

#### a. Write a matrix-matrix (N × N) multiplication program using the usual 3d-loop and recursive strassen multiplication.

** Standard 3d loop **

- Code File: `2a_standard_2d_loop.c`

- Commands to run:
  - Compile the file using avx:
    ```shell
    gcc -o 2a_standard_2d_loop 2a_standard_2d_loop.c
    ```
  - Execute the program:
    ```shell
    ./2a_standard_2d_loop

- Output:

  ![image](https://github.com/akhiha/aca_assignment/assets/24610167/60614b6a-3d1d-427d-ae84-31067df8639d)


** Recursive Strassen Multiplication **

- Code File: `2a_strassen.c`

- Commands to run:
  - Compile the file using avx:
    ```shell
    gcc -o 2a_strassen 2a_strassen.c
    ```
  - Execute the program:
    ```shell
    ./2a_strassen

- Output:

  ![image](https://github.com/akhiha/aca_assignment/assets/24610167/a6752464-957f-4f16-91b3-9d44761d26eb)


#### b. Using performance monitors compute the number of instructions executed, CPI, L1/L2/L3 cache hit ratios for various matrix dimensions N = 2k, 4 ≤ k ≤ 14.

- Code File: `2b.c`

- Commands to run:
  - Compile:
    ```shell
    gcc -o 2b 2b.c -O3
    ```
  - Execute the program:
    ```shell
    ./2b
    ```
  - Performance to meaure uing perf:
 
- Output:

  ![image](https://github.com/akhiha/aca_assignment/assets/24610167/d94f9550-9722-49a6-b925-cacbe5a4745e)


#### c. Write a tiled version of matrix multiplication. Using cache grind for 32 KB L1 cache, 1 MB L2 cache, line size64 bytes, find the best tile size which gives best hit ratio for matrix dimension N = 2048. Compare the hit ration using recursive matrix multiplication. Compare the instruction count in both the cases

- Code File: `2c.c`

- Commands to run:
  - Compile:
    ```shell
    gcc -o 2c 2c.c -O3
    ```
  - Execute the program:
    ```shell
    ./2c
    ```
  - Performance to meaure uing cachegrind:
    ```shell
    valgrind --tool=cachegrind --I1=32768,8,64 --D1=32768,8,64 --LL=1048576,16,64 ./2c
    ```

    ```shell
    valgrind --tool=cachegrind --I1=32768,8,64 --D1=32768,8,64 --LL=1048576,16,64 ./2a_strassen
    ```
    
- Output:

  ![image](https://github.com/akhiha/aca_assignment/assets/24610167/d1d4cd0b-9a22-4720-8fe2-5aabd68f0410)

  ![image](https://github.com/akhiha/aca_assignment/assets/24610167/5a4975af-6e05-4e2f-ab93-bc8b46c36376)

  ![image](https://github.com/akhiha/aca_assignment/assets/24610167/130b2a28-3029-4d06-9ec0-093f291fc1e9)


### 3. For the following C-program using cache grind find the optimal cache configuration for a 2-level inclusive fully-associative LRU cache hierarchy (default read and write policies) when input size n is 4000 the following input sizes (Line size: 64 Bytes) 
### for (i = 0; i < n - 1; i++) {
### S1: A[i] = 0
### for (j = 1; j < n - 1; j++)
### S2: A[i] += 0.33*(B[i][j] * X[j])
### }
### Plot a 3D graph with x-axis as L1 cache size, y-axis as L2 cache size and z-axis as miss ratio.

- Code File: `3.c`, `3.sh`, `script.py`, `script_plot.py`

- Commands to run:
  - ```shell
    gcc -o 3_cache 3.c -O2
    ```
  - ```shell
    python3 script.py
    ```
  - ```shell
    python3 script_plot.py
    ```
- Output:

  ![image](https://github.com/akhiha/aca_assignment/assets/24610167/bb61c5cf-d28a-4725-9638-ec3e9f73745e)
