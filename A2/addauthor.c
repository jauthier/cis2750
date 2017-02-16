/*
    addauthor.c
    Author: Jessica Authier
    Date Modified: 2017/02/14
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char * argv[]){

    if (argc == 1){
        printf("You must enter a username!\n");
        exit(0);
    }

    int i = 1;
    int check = 0;
    char buffer[200];
    /*the user wants to remove a username*/
    if (strcmp(argv[1],"-r")==1){
        check = 1;
        i++;
    }
    strcpy(buffer,argv[i]);
    i++;
    while (i < argc){
        /*put all strings into one*/
        strcat(buffer, " ");
        strcat(buffer, argv[i]);
        i++;
    }
    char * username = malloc(sizeof(char)*strlen(buffer));
    strcpy(username,buffer);

    /*get list of streams*/
    printf("Enter the list of streams you want to add/remove,\nplease separate them by commas:\n");
    char streamHold[200];
    fgets(streamHold,200,stdin);

    char * streams = malloc(sizeof(char)*strlen(streamHold));
    strcpy(streams,streamHold);

    if (check == 1)
        removeUser(username,streams);
    else 
        addUser(username, streams);

    return 0;
}
