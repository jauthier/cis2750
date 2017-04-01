/*
    streamLib.c
    Author: Jessica Authier
    Date Modified: 2017/02/14
*/

#include "stream.h"

userPost * createUserPost (char *username,char *streamname, char *date, char *text){
    userPost * newUP = malloc(sizeof(userPost));
    newUP->username = username;
    newUP->streamname = streamname;
    newUP->date = date;
    newUP->text = text;
    return newUP;
}

void destroyUserPost(userPost *toDestroy){
    free(toDestroy->username);
    free(toDestroy->streamname);
    free(toDestroy->date);
    free(toDestroy->text);
    free(toDestroy);
}

void updateStream(MYSQL mysql, char *stream, userPost *up){
    
    post(mysql, stream, up->username, up->date, up->text);
    updateUserTable(mysql,stream,user);
}

void addUser(char *username, char *list){
    /*tokenize the stream  list*/
    char * token = strtok(list," ,\n");
    while (token != NULL){
        int check1 = checkTables(mysql,token);
        if (check1 == 1){
            int check2 = checkUser(mysql,token,user);
            if (check2 == 0)
                addUser(mysql,token, user);
        } else {
            createTable(mysql, token);
            addUser(mysql,token, user);
        }
        token = strtok(NULL, " ,\n");
    }
}

void removeUser(char *username, char *list){
    /*tokenize the stream  list*/
    char * token = strtok(list," ,\n");
    while (token != NULL){
        int check = checkTables(mysql,token);
        if (check == 1)
            removeUser(mysql,token, user);
        token = strtok(NULL, " ,\n");
    }
}
