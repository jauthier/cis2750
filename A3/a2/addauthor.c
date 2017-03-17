/*
    addauthor.c
    Author: Jessica Authier
    Date Modified: 2017/02/14
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream.h"

int main (int argc, char * argv[]){

    if (argc < 3){
        printf("error");
        return 0;
    }
    int check = 0;
    int i = 1;
    /*the user wants to remove a username*/
    if (strcmp(argv[1],"-r")==0){
        check = 1;
        i++;
    }
    char * username = malloc(sizeof(char)*strlen(argv[i]));
    strcpy(username,argv[i]);

    char * streams = malloc(sizeof(char)*strlen(argv[i]));
    strcpy(streams,argv[i]);
    printf("here\n");
    if (check == 1)
        removeUser(username,streams);
    else 
        addUser(username, streams);

    return 0;
}
