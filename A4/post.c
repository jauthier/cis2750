/*
    post.c
    Author: Jessica Authier
    2017/03/31
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "stream.h"
#include <mysql/mysql.h>
#define HOSTNAME "dursley.socs.uoguelph.ca"
#define USERNAME "jauthier"
#define PASSWORD "0849720"
#define DATABASE "jauthier"

char * getTimeData ();
userPost * formatEntry (char * username, char * streamname, char * text);
void submitPost (userPost *up);
char * formatDate (char * date);

char * getTimeData (){
    time_t getTime = time (NULL);
    char * date  = malloc(sizeof(char)*strlen(ctime(&getTime)));
    strcpy(date, ctime(&getTime));
    char *finalDate = formatDate(date);
    free(date);
    return finalDate;
}

userPost * formatEntry (char * username, char * streamname, char * text){
        char * date = getTimeData();
        userPost * newPost = createUserPost(username, streamname, date, text);
        return newPost;
}

void submitPost (MYSQL mysql, char * stream, struct userPost *up){

    updateStream(MYSQL mysql, char * stream, up);
}

char * formatDate (char * date){
    /*will be in the form: dayOfWeek month day time year*/
    char *month = strtok(date," "); /*that will get the day of the week*/
    month = strtok(NULL, " ");
    char *day = strtok(NULL, " ");
    char * time = strtok(NULL, " \n");
    char *year = strtok(NULL, " \n");

    char *finalDate = malloc(sizeof(char)*(strlen(month)+strlen(day)+strlen(year)+strlen(time)+strlen(" ,   \n")));
    strcpy(finalDate, month);
    strcat(finalDate," ");
    strcat(finalDate,day);
    strcat(finalDate,", ");
    strcat(finalDate,year);
    strcat(finalDate," ");
    strcat(finalDate,time);
    strcat(finalDate,"\n");
    return finalDate;
} 

int main (int argc, char *argv[]){
    /* take in username, steam and text */
    char * username = malloc(sizeof(char)*strlen(argv[1]));
    strcpy(username,argv[1]);
    char * stream = malloc(sizeof(char)*strlen(argv[2]));
    strcpy(stream, argv[2]);
    char * text = malloc(sizeof(char)*1000);
    strcpy(text, argv[3]);
    int i = 4;
    for (i=4;i<argc;i++){
        strcat(text,argc[i]);
    }

    /*Connect to Database Server*/
    MYSQL mysql;
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql,HOSTNAME,USERNAME,PASSWORD,DATABASE,0,NULL,0)){
        printf("0");
        return 0;
    }

    /*check if the stream exists and the user has permission to post on the stream*/
    int check = checkUsers(mysql, stream, username);
    if (check == 0){
        printf("0");
        return 0;
    }

    /*format the post into a UserPost struct*/
    userPost * newPost = formatEntry(username, stream, text);
    submitPost(mysql, stream, newPost);
    printf("1");
    return 0;
}
