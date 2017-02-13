/*
    2_3.c
    Jessica Authier
    0849720
    2017/02/13
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "1_3.c"

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
    int i = 0;
    while (fgets(buffer, 60, fp1) != NULL){
        char * token; 
        token = strtok(buffer," \n");
        while (token != NULL){
            A[i] = strtol(token);
            token = strtok(NULL, " \n");
            i++;
        }
    }

    struct timeb t;
    ftime (t);
    int start1 = t.millitm;
    countInversions(A, i+1);
    ftime (t);
    int end1 = t.millitm;
    printf("%d\n", end1-start1);

    return 0;
}
