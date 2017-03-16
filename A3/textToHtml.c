/*
    textToHtml.c
    Author: Jessica Authier
    Date Modified: 2017/02/28    
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "translateConfig.h"

void interpretLine(char * line, FILE * fp);

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

    /*make the php file*/
    
    char *outFileName = malloc(sizeof(char)*(strlen(fileName)+1));
    strcpy(outFileName,strtok(fileName,"."));
    strcat(outFileName,".php");
    FILE *outFP = fopen(outFileName,"a");

    fprintf(outFP, "<!DOCTYPE html>\n<html>\n<body>\n");

    /*read in file line by  line*/
    char buffer[500];
    while (fgets(buffer,500,fp) != NULL){
        char *token = strtok(buffer,".\n");
        while (token != NULL){
            interpretLine(token, outFP);
            token = strtok(NULL,".\n");
        }
    }
    fprintf(outFP, "</body>\n</html>\n");
    return 0;
}

void interpretLine(char * line, FILE *fp){
    /*check the first letter of the line*/
    char first = line[0];
    char * inside = strtok(line,"()");
    inside = strtok(NULL,"()");

    switch (first){
        case 'b' : /*button*/
            button(inside, fp);
            break;
        case 'd' : /*horizontal line*/
            fprintf(fp, "<hr>\n");
            break;
        case 'e' : /*executable*/
            executable(inside, fp);
            break;
        case 'h' : /*header*/
            headings(inside, fp);
            break;
        case 'i' : /*one input*/
            input(inside,fp);
            break;
        case 'l' : /*link*/
            link(inside, fp);
            break;
        case 'p' : /*picture*/
            pictures(inside, fp);
            break;
        case 'r' : /*radio button*/
            radioButton(inside, fp);
            break;
        case 't' : /*text*/
            text(inside, fp);
            break;
        case 'n': /*new line*/
            fprintf(fp, "<br>\n");
            break;
    }
}
