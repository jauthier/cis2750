/*
    1_3.c
    Jessica Authier
    0849720
    2017/02/13
*/
#include "1_3.h"

int countInversions (int * A, int n){
    int count = 0;
    int i = 0;
    for (i=0;i<(n-1);i++){
        printf("i: %d\n", n);
        int j;
        for (j=i+1;j<n;j++){
            printf("j: %d\n", j);
            printf("A[i]: %d, A[j]: %d\n", A[i],A[j]);
            if (A[i]>A[j])
                count ++;
        }
    }
    return count;
}

int countInvMergesort (int *A, int n){
    int count = 0;
    if (n > 1){
        //make a new Array of size n/2
        int B[n/2];// = malloc(sizeof(int)*(n/2));
        int i = 0;
        for (i=0;i<(n/2);i++){
            B[i] = A[i];
        }
        int C[n/2]; //= malloc(sizeof(int)*(n-(n/2)));
        int j = 0;
        for (i=(n/2);i<n;i++){
            C[j] = A[i];
            j++;
        }
        count = countInvMergesort(B, n/2);
        count = count + countInvMergesort(C, n-(n/2));
        count = count + merge(B, C, A, n/2, n-(n/2));
    }
    return count;
}

int merge(int * B, int * C, int * A, int p, int q){

    int i = 0;
    int j = 0;
    int k = 0;
    int count = 0;

    while (i < p && j < q){
        if (B[i]<= C[j]){
            A[k] = B[i];
            i++;
        } else {
            A[k] = C[j];
            j++;
            count ++;
        }
        k++;
    }
    if (i == p){
        while (j < q){
            A[k] = C[j];
            k++;
            j++;
        }
    } else {
        while (i < p){
            A[k] = B[i];
            k++;
            i++;
        }
    }
    return count;
}
