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
#include "2_3.h"

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
    while (fgets(buffer, 60, fp1) != NULL){
        char * token; 
        token = strtok(buffer," \n");
        while (token != NULL){
            A[i] = strtol(token,&temp,10);
            token = strtok(NULL, " \n");
            i++;
        }
    }
    fclose(fp1);
    printf("1.3\n\n");
    struct timeb start, end;
    ftime (&start);
    int num = countInversions(A, i);
    ftime (&end);
    printf("Brute force:\nTime: %d:%d\n", num, end.time - start.time, end.millitm - start.millitm);

    ftime (&start);
    num = countInvMergesort(A, i);
    ftime (&end);
    printf("Divide and Conquer:\nTime: %d:%d\n", num, end.time - start.time, end.millitm - start.millitm);
    
    FILE * fp2 = fopen(file2,"r");
    if (fp1 == NULL) {
        printf("file data_2.txt could not be opened.\n");
        return 0;
    }

    Point * pArray[30000];
    i = 0;
    while (fgets(buffer, 60, fp2) != NULL){
        Point * newP = malloc(sizeof(Point));
        char * token; 
        token = strtok(buffer," \n");
        newP->x = atof(token);
        token = strtok(NULL," \n");
        newP->y = atof(token);
        pArray[i] = newP;
        i++;
    }
    fclose(fp2);
    printf("\n2.3\n\n");
    ftime (&start);
    Point **hull = convexHull(pArray, i, hull);
    ftime (&end);
    printf("Brute force:\nTime: %d:%d\n", num, end.time - start.time, end.millitm - start.millitm);


    return 0;
}
