#include <stdlib.h>
#include <stdio.h>
#include "globals.h"
#include <memory.h>
#include "../sysdetails/sysdetails.h"


//    COPY:       a(i) = b(i)                 16              0
//    SCALE:      a(i) = q*b(i)               16              1
//    SUM:        a(i) = b(i) + c(i)          24              1
//    TRIAD:      a(i) = b(i) + q*c(i)        24              2

void copy(float* A, float* B, size_t len)
{
    memcpy(A, B, sizeof(float) * len);
}

void scale(float* A, float* B, float q, size_t len)
{
    for(size_t n=0; n < len; n++)
        A[n] = B[n]*q; 
}

void sum(float* A, float* B, float* C, size_t len)
{
    for(size_t n=0; n < len; n++)
        A[n] = B[n] + C[n];
}

void triad(float* A, float* B, float* C, float q, size_t len)
{
    for(size_t n=0; n < len; n++)
        A[n] = B[n] + q * C[n];
}

int main(int argc, char** argv)
{
    if(argc != 5) {
        printf("Usage: binary <size> <input1_file> <input2_file> <output_file>\n");
        return -1;
    }
    unsigned int size = atoi(argv[1]);
    float* a = loadMatrix(argv[2], 1, size);
    float* b = loadMatrix(argv[3], 1, size);
    float* m = (float*) malloc (sizeof(float)*size);

    sum(m, a, b, size);

    saveMatrix(argv[4], m, 1, size);
    free(a);
    free(b);
    free(m);
    systamp();
    return 0;
}

