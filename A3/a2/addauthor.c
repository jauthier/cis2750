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

    int i = 1;
    int check = 0;
    char *buffer;
    /*the user wants to remove a username*/
    if (strcmp(argv[1],"-r")==0){
        check = 1;
        i++;
    }
    strcpy(buffer,argv[i]);
    i++;
    char * username = malloc(sizeof(char)*strlen(buffer));
    strcpy(username,buffer);

    strcpy(buffer,argv[i]);
    char * streams = malloc(sizeof(char)*strlen(buffer));
    strcpy(streams,buffer);

    if (check == 1)
        removeUser(username,streams);
    else 
        addUser(username, streams);

    return 0;
}
