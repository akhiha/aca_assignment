#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10 // Original matrix size
#define P 16 // Padded matrix size (next power of 2)

int** allocateMatrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void addMatrix(int** a, int** b, int** result, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void subtractMatrix(int** a, int** b, int** result, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = a[i][j] - b[i][j];
        }
    }
}

void padMatrix(int original[N][N], int** padded) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < P; j++) {
            padded[i][j] = (i < N && j < N) ? original[i][j] : 0;
        }
    }
}

void extractResult(int** padded, int result[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = padded[i][j];
        }
    }
}

void strassen(int** a, int** b, int** c, int n) {
    if (n == 1) {
        c[0][0] = a[0][0] * b[0][0];
        return;
    }

    int halfSize = n / 2;
    int** a11 = allocateMatrix(halfSize);
    int** a12 = allocateMatrix(halfSize);
    int** a21 = allocateMatrix(halfSize);
    int** a22 = allocateMatrix(halfSize);
    int** b11 = allocateMatrix(halfSize);
    int** b12 = allocateMatrix(halfSize);
    int** b21 = allocateMatrix(halfSize);
    int** b22 = allocateMatrix(halfSize);

    int** c11 = allocateMatrix(halfSize);
    int** c12 = allocateMatrix(halfSize);
    int** c21 = allocateMatrix(halfSize);
    int** c22 = allocateMatrix(halfSize);

    int** p1 = allocateMatrix(halfSize);
    int** p2 = allocateMatrix(halfSize);
    int** p3 = allocateMatrix(halfSize);
    int** p4 = allocateMatrix(halfSize);
    int** p5 = allocateMatrix(halfSize);
    int** p6 = allocateMatrix(halfSize);
    int** p7 = allocateMatrix(halfSize);

    int** temp1 = allocateMatrix(halfSize);
    int** temp2 = allocateMatrix(halfSize);

    // Splitting matrices into 4 sub-matrices
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < halfSize; i++) {
        for (int j = 0; j < halfSize; j++) {
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][j + halfSize];
            a21[i][j] = a[i + halfSize][j];
            a22[i][j] = a[i + halfSize][j + halfSize];
            b11[i][j] = b[i][j];
            b12[i][j] = b[i][j + halfSize];
            b21[i][j] = b[i + halfSize][j];
            b22[i][j] = b[i + halfSize][j + halfSize];
        }
    }

    // Calculating p1 to p7 in parallel
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            addMatrix(a11, a22, temp1, halfSize);
            addMatrix(b11, b22, temp2, halfSize);
            strassen(temp1, temp2, p1, halfSize);
        }
        #pragma omp section
        {
            addMatrix(a21, a22, temp1, halfSize);
            strassen(temp1, b11, p2, halfSize);
        }
        #pragma omp section
        {
            subtractMatrix(b12, b22, temp2, halfSize);
            strassen(a11, temp2, p3, halfSize);
        }
        #pragma omp section
        {
            subtractMatrix(b21, b11, temp2, halfSize);
            strassen(a22, temp2, p4, halfSize);
        }
        #pragma omp section
        {
            addMatrix(a11, a12, temp1, halfSize);
            strassen(temp1, b22, p5, halfSize);
        }
        #pragma omp section
        {
            subtractMatrix(a21, a11, temp1, halfSize);
            addMatrix(b11, b12, temp2, halfSize);
            strassen(temp1, temp2, p6, halfSize);
        }
        #pragma omp section
        {
            subtractMatrix(a12, a22, temp1, halfSize);
            addMatrix(b21, b22, temp2, halfSize);
            strassen(temp1, temp2, p7, halfSize);
        }
    }

    // Constructing the result matrix c from submatrices
    addMatrix(p3, p5, c12, halfSize);
    addMatrix(p2, p4, c21, halfSize);
    addMatrix(p1, p4, temp1, halfSize);
    addMatrix(temp1, p7, temp2, halfSize);
    subtractMatrix(temp2, p5, c11, halfSize);
    addMatrix(p1, p3, temp1, halfSize);
    addMatrix(temp1, p6, temp2, halfSize);
    subtractMatrix(temp2, p2, c22, halfSize);

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < halfSize; i++) {
        for (int j = 0; j < halfSize; j++) {
            c[i][j] = c11[i][j];
            c[i][j + halfSize] = c12[i][j];
            c[i + halfSize][j] = c21[i][j];
            c[i + halfSize][j + halfSize] = c22[i][j];
        }
    }

    // Freeing allocated memory
    freeMatrix(a11, halfSize);
    freeMatrix(a12, halfSize);
    freeMatrix(a21, halfSize);
    freeMatrix(a22, halfSize);
    freeMatrix(b11, halfSize);
    freeMatrix(b12, halfSize);
    freeMatrix(b21, halfSize);
    freeMatrix(b22, halfSize);
    freeMatrix(c11, halfSize);
    freeMatrix(c12, halfSize);
    freeMatrix(c21, halfSize);
    freeMatrix(c22, halfSize);
    freeMatrix(p1, halfSize);
    freeMatrix(p2, halfSize);
    freeMatrix(p3, halfSize);
    freeMatrix(p4, halfSize);
    freeMatrix(p5, halfSize);
    freeMatrix(p6, halfSize);
    freeMatrix(p7, halfSize);
    freeMatrix(temp1, halfSize);
    freeMatrix(temp2, halfSize);
}


int main() {
    // Initialize 10x10 matrices with some values
    int A[N][N] = {
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
	{11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
	{21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {31, 32, 33, 34, 35, 36, 37, 38, 39, 40},
	{41, 42, 43, 44, 45, 46, 47, 48, 49, 50},
        {51, 52, 53, 54, 55, 56, 57, 58, 59, 60},
        {61, 62, 63, 64, 65, 66, 67, 68, 69, 70},
        {71, 72, 73, 74, 75, 76, 77, 78, 79, 80},
        {81, 82, 83, 84, 85, 86, 87, 88, 89, 90},
        {91, 92, 93, 94, 95, 96, 97, 98, 99, 100}
    };
    int B[N][N] = {
	{100, 99, 98, 97, 96, 95, 94, 93, 92, 91},
        {90, 89, 88, 87, 86, 85, 84, 83, 82, 81},
        {80, 79, 78, 77, 76, 75, 74, 73, 72, 71},
        {70, 69, 68, 67, 66, 65, 64, 63, 62, 61},
        {60, 59, 58, 57, 56, 55, 54, 53, 52, 51},
        {50, 49, 48, 47, 46, 45, 44, 43, 42, 41},
        {40, 39, 38, 37, 36, 35, 34, 33, 32, 31},
        {30, 29, 28, 27, 26, 25, 24, 23, 22, 21},
        {20, 19, 18, 17, 16, 15, 14, 13, 12, 11},
        {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}
    };
    int C[N][N]; // Result matrix

    // Allocate and pad matrices
    int** paddedA = allocateMatrix(P);
    int** paddedB = allocateMatrix(P);
    int** paddedC = allocateMatrix(P);

    padMatrix(A, paddedA);
    padMatrix(B, paddedB);

    // Perform Strassen multiplication on padded matrices
    strassen(paddedA, paddedB, paddedC, P);

    // Extract the result into C
    extractResult(paddedC, C);

    // Print result matrix C
    printf("Matrix C (Product):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Free memory
    freeMatrix(paddedA, P);
    freeMatrix(paddedB, P);
    freeMatrix(paddedC, P);

    return 0;
}
