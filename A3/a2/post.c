/*
    post.c
    Author: Jessica Authier
    2017/03/15
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "stream.h"

char * getTimeData ();
userPost * formatEntry (char * username, char * streamname, char * text);
void submitPost (userPost *up);
int checkStreamUsers (FILE *sufp, char *username);
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

void submitPost (struct userPost *up){

    int end = updateStream(up);
    updateStreamData(up, end);
}

int checkStreamUsers (FILE *sufp, char *username){

    if (sufp == NULL){
        return 0;
    }

    char userLine[210];
    while (fgets(userLine,210,sufp) != NULL){
        if (strstr(userLine,username) != NULL)
            return 1;
    }
    return 0;
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
    char * text = malloc(sizeof(char)*strlen(argv[3]));
    strcpy(text, argv[3]);

    /*check if the stream exists and the user has permission to post on the stream*/
    char * streamFile = malloc(sizeof(char)*(strlen("a2/messages/")+strlen(stream)+strlen("StreamUsers.txt")));
    strcpy(streamFile,"a2/messages/");
    strcat(streamFile,stream);
    strcat(streamFile,"StreamUsers.txt");
    FILE * sufp = fopen(streamFile,"r");
    int checkSU = checkStreamUsers(sufp, username);
    if (checkSU == 0){
        printf("0");
        return 0;
    }

    /*format the post into a UserPost struct*/
    userPost * newPost = formatEntry(username, stream, text);
    submitPost(newPost);
    printf("1");
    return 0;
}
