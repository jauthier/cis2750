/*
*   db.c
*   Author: jessica Auhtier
*   Date Modified: 2017/03/31
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#define HOSTNAME "dursley.socs.uoguelph.ca"
#define USERNAME "jauthier"
#define PASSWORD "0849720"
#define DATABASE "jauthier"
#include "dbFunctions.h"

int main(int argc, char *argv[]){

    // get the host name from the command line
    if (argc < 2){
        printf("You must enter an action.\n");
        exit(0);
    }
    char * action = malloc(sizeof(char)*strlen(argv[1]));
    strcpy(action,argv[1]);

    MYSQL mysql;
    
    /*Connect to Database Server*/
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql,HOSTNAME,USERNAME,PASSWORD,DATABASE,0,NULL,0)){
        printf("could not connect to host.\n%s\n",mysql_error(&mysql));
        exit(0);
    }
    
    if (strcmp(action,"-clear")==0){
        clearTables(mysql);
    } else if (strcmp(action,"-reset")==0){
        removeTables(mysql);
    } else if (strcmp(action,"-posts")==0){
        getPosts(mysql);
    } else if (strcmp(action,"-users")==0){
        getUsers(mysql);
    } else if (strcmp(action,"-streams")==0){
        getStreams(mysql);
    } else if (strcmp(action,"-help")==0){
        
    } else if (strcmp(action,"-remove")==0){
        if (argc < 4){
            printf("You must enter the user and the stream.\n");
            exit(0);
        }
        char * user = malloc(sizeof(char)*strlen(argv[2]));
        strcpy(user,argv[2]);
        char * stream = malloc(sizeof(char)*strlen(argv[3]));
        strcpy(stream,argv[3]);
        /*check if the table exists*/
        int check = checkTable(mysql,stream);
        if (check == 1)
            removeUser(mysql,stream, user);
    } else if (strcmp(action,"-add")==0){
        if (argc < 4){
            printf("You must enter the user and the stream.\n");
            exit(0);
        }
        char * user = malloc(sizeof(char)*strlen(argv[2]));
        strcpy(user,argv[2]);
        char * stream = malloc(sizeof(char)*strlen(argv[3]));
        strcpy(stream,argv[3]);
        int check1 = checkTable(mysql,stream);
        if (check1 == 1){
            int check2 = checkUser(mysql,stream,user);
            if (check2 == 0)
                addUser(mysql,stream, user);
        } else {
            createTables(mysql, stream);
            addUser(mysql,stream, user);
        }
    } else if (strcmp(action,"-post")==0){
        if (argc < 6){

            exit(0);
        }
        char * user = malloc(sizeof(char)*strlen(argv[2]));
        strcpy(user,argv[2]);
        char * stream = malloc(sizeof(char)*strlen(argv[3]));
        strcpy(stream,argv[3]);
        char * date = malloc(sizeof(char)*strlen(argv[4]));
        strcpy(date,argv[4]);
        char * text = malloc(sizeof(char)*1000);
        strcpy(text, argv[5]);
        int i = 6;
        for (i=6;i<argc;i++){
            strcat(text,argv[i]);
        }
        post(mysql,stream,user,date,text);
    } else if (strcmp(action,"-sPost")==0){
        if (argc < 3){

            exit(0);
        }
        char * stream = malloc(sizeof(char)*strlen(argv[2]));
        strcpy(stream,argv[2]);
        getStreamPosts(mysql, stream);
    } else if (strcmp(action,"-getData")==0){
        if (argc < 3){

            exit(0);
        }
        char * stream = malloc(sizeof(char)*strlen(argv[2]));
        strcpy(stream,argv[2]);
        printDataTable(mysql, stream);
    } else if (strcmp(action,"-getSU")==0){
        if (argc < 3){

            exit(0);
        }
        char * stream = malloc(sizeof(char)*strlen(argv[2]));
        strcpy(stream,argv[2]);
        printStreamUsers(mysql, stream);
    } else if (strcmp(action,"-getUsersCP")==0){
        if (argc < 4){

            exit(0);
        }
        char * user = malloc(sizeof(char)*strlen(argv[2]));
        strcpy(user,argv[2]);
        char * stream = malloc(sizeof(char)*strlen(argv[3]));
        strcpy(stream,argv[3]);
        getUsersCP(mysql, stream);
    } else if (strcmp(action,"-update")==0){
        if (argc < 4){

            exit(0);
        }
        char * user = malloc(sizeof(char)*strlen(argv[2]));
        strcpy(user,argv[2]);
        char * stream = malloc(sizeof(char)*strlen(argv[3]));
        strcpy(stream,argv[3]);
        getUsersCP(mysql, stream);
        updateUserTable (mysql, stream, user);
    }
    mysql_close(&mysql);
    return 0;
}
