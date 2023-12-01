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
