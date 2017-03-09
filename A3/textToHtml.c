/*
    textToHtml.c
    Author: Jessica Authier
    Date Modified: 2017/02/28    
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void interpretLine(char * line);

int main(int argc, char * argv[]){

    /*check a file name has been given*/
    if (argc <= 1){
        printf("You must enter a text config file.\n");
        exit(0);
    }

    /*get the file name*/
    char *fileName = argv[1];
    FILE *fp = fopen(fileName,"r");
    if (fp == NULL){
        printf("The file you gave was not found.\n");
        exit(0);
    }

    /*make the html file*/
    
    char *outFileName = malloc(sizeof(char)*(strlen(fileName)+1));
    strcpy(outFileName,strtok(fileName,"."));
    strcat(outFileName,".html");
    FILE *outFP = fopen(outFileName,"w");

    /*read in file line by  line*/
    char buffer[500]
    while (fgets(buffer,500,fp) != NULL){
        char *token = strtok(buffer,".\n");
        while (token != NULL){
            interpretLine(token, outFP);
            token = strtok(NULL,".\n");
        }
    }
    return 0;
}

void interpretLine(char * line, FILE *fp){
    /*check the first letter of the line*/
    char first = line[0];
    char * inside = strtok(line,"()");
    inside = strtok(NULL,"()");

    switch (first){
        case 'b' :
            button(inside, outFP);
            break;
        case 'd' :

            break;
        case 'e' :

            break;
        case 'h' :
            heading(inside, outFP);
            break;
        case 'i' :

            break;
        case 'l' :
            link(inside, outFP);
            break;
        case 'p' :
            pictures(inside, outFP);
            break;
        case 'r' :

            break;
        case 't' :

            break;
    }
}
