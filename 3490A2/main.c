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
    strcpy(file1,"data_1.txt");
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
    printf("before file\n");
    while (fgets(buffer, 60, fp1) != NULL){
        char * token; 
        token = strtok(buffer," \n");
        while (token != NULL){
            A[i] = strtol(token,&temp,10);
            token = strtok(NULL, " \n");
            i++;
        }
    }
    printf("after file\n");

    struct timeb start, end;
    ftime (&start);
    printf("before first count\n");
    countInversions(A, i+1);
    printf("afterfirst count\n");
    ftime (&end);
    printf("Brute force: %d:%d\n", end.time - start.time, end.millitm - start.millitm);

    ftime (&start);
    printf("before second count\n");
    countInvMergesort(A, i+1);
    printf("aftersecond count\n");
    ftime (&end);
    printf("Divide and Conquer: %d:%d\n", end.time - start.time, end.millitm - start.millitm);
    return 0;
}
