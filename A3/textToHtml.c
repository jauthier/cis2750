/*
    textToHtml.c
    Author: Jessica Authier
    Date Modified: 2017/02/28    
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "translateConfig.h"

void interpretLine(char * line, FILE * fp);

int main(int argc, char * argv[]){

    /*check a file name has been given*/
    if (argc <= 1){
        printf("You must enter a config file.\n");
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
    FILE *outFP = fopen(outFileName,"w");

    fprintf(outFP, "<!DOCTYPE html>\n<html>\n<body>\n");
    /*read in file character by character*/
    char c = fgetc(fp);

    while (!feof(fp)){
        if (c == '.'){
            c = fgetc(fp);
            char d = fgetc(fp);
            if (isalpha(c) != 0 && d == '('){
                char * line = malloc(sizeof(char)*200);
                int i = 0;
                line[i] = c;
                printf("%c\n", line[i]);
                i++;
                line[i] = d;
                printf("%c\n", line[i]);
                i++;
                int openBraces = 0;
                d = fgetc(fp);
                while (d != ')' || openBraces != 0){
                    if (d == '(')
                        openBraces++;
                    if (d == ')')
                        openBraces--;
                    line[i] = d;
                    printf("%c\n", line[i]);
                    i++;
                    d = fgetc(fp);
                }
                line[i] = d;
                printf("%s\n", line);
                interpretLine(line, outFP);
                free(line);
            }
        }
        c = fgetc(fp);
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
