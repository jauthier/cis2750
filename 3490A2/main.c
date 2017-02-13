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
        printf("in file\n");
        char * token; 
        token = strtok(buffer," \n");
        while (token != NULL){
            A[i] = strtol(token,&temp,10);
            token = strtok(NULL, " \n");
            i++;
        }
    }

    struct timeb *t;
    ftime (t);
    int start1 = t->millitm;
    printf("before first count\n");
    countInversions(A, i+1);
    printf("afterfirst count\n");
    ftime (t);
    int end1 = t->millitm;
    printf("Brute force: %d\n", end1-start1);

    ftime (t);
    int start2 = t->millitm;
    printf("before second count\n");
    countInvMergesort(A, i+1);
    printf("aftersecond count\n");
    ftime (t);
    int end2 = t->millitm;
    printf("Divide and conquer: %d\n", end2-start2);

    return 0;
}
