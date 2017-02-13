/*
    2_3.c
    Jessica Authier
    0849720
    2017/02/13
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <string.h>
#include "1_3.h"

int main (int argc, char *argv[]){
    
    char * file1 = malloc(sizeof(char)*strlen("data_1.txt"));
    char * file2 = malloc(sizeof(char)*strlen("data_2.txt"));
    strcpy(file1,"data_3.txt");
    strcpy(file2,"data_2.txt");
    FILE * fp1 = fopen(file1,"r");
    if (fp1 == NULL) {
        printf("file data_1.txt could not be opened.\n");
        return 0;
    }

    int A[50000];
    char buffer[60];
    char * temp;
    int i = 0;
    while (fgets(buffer, 60, fp1) != NULL){
        char * token; 
        token = strtok(buffer," \n");
        while (token != NULL){
            A[i] = strtol(token,&temp,10);
            token = strtok(NULL, " \n");
            i++;
        }
    }

    struct timeb start, end;
    ftime (&start);
    int num = countInversions(A, i);
    ftime (&end);
    printf("Brute force:\nNumber of inversions: %d\nTime: %d:%d\n", num, end.time - start.time, end.millitm - start.millitm);

    ftime (&start);
    num = countInvMergesort(A, i);
    ftime (&end);
    printf("Divide and Conquer:\nNumber of inversions: %d\nTime: %d:%d\n", num, end.time - start.time, end.millitm - start.millitm);
    return 0;
}
