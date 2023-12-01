# Advanced Computer Architecture

## Akhila Matathammal -2023801001

### 1. On Vector Instruction Sets

#### a. Write a scalar program to compute the dot product of two vectors

- Code File: `1a.c`

- Commands to run for executing the file in Ubuntu
  - Compile the file
    ```shell
    gcc -fopenmp -o 1a 1a.c```
  - Execute the Program
    ```shell
    ./1a```

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
      ./dot_product_sse```
      
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
      ./dot_product_sse```

  - Output:

    ![image](https://github.com/akhiha/aca_assignment/assets/24610167/7dac7347-98be-4751-b9aa-00a7d2325a7d)

 
  - 
