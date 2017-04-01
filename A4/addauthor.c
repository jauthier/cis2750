/*
    addauthor.c
    Author: Jessica Authier
    Date Modified: 2017/02/14
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream.h"
#include <mysql/mysql.h>
#define HOSTNAME "dursley.socs.uoguelph.ca"
#define USERNAME "jauthier"
#define PASSWORD "0849720"
#define DATABASE "jauthier"

int main (int argc, char * argv[]){

    if (argc < 3){
        printf("error");
        return 0;
    }
    MYSQL mysql;
    
    /*Connect to Database Server*/
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql,HOSTNAME,USERNAME,PASSWORD,DATABASE,0,NULL,0)){
        printf("could not connect to host.\n%s\n",mysql_error(&mysql));
        exit(0);
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
    i++;
    char * streams = malloc(sizeof(char)*strlen(argv[i]));
    strcpy(streams,argv[i]);

    if (check == 1)
        removeUser(mysql, username, streams);
    else 
        addUser(mysql, username, streams);

    return 0;
}
