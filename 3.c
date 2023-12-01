#include <stdio.h>
#include <stdlib.h>

void compute(double *A, double **B, double *X, int n) {
    for (int i = 0; i < n - 1; i++) {
        A[i] = 0;
        for (int j = 1; j < n - 1; j++) {
            A[i] += 0.33 * (B[i][j] * X[j]);
        }
    }
}

int main() {
    int n = 4000;
    double *A = malloc((n - 1) * sizeof(double));
    double **B = malloc((n - 1) * sizeof(double *));
    double *X = malloc((n - 1) * sizeof(double));

    for (int i = 0; i < n - 1; i++) {
        B[i] = malloc((n - 1) * sizeof(double));
        X[i] = i;
    }

    compute(A, B, X, n);

    free(A);
    free(X);
    for (int i = 0; i < n - 1; i++) {
        free(B[i]);
    }
    free(B);

    return 0;
}
