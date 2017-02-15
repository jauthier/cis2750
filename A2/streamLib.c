/*
    streamLib.c
    Author: Jessica Authier
    Date Modified: 2017/02/14
*/

#include "streamLib.h"

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

int updateStream(userPost *up){
    printf("in updateStream\n");
    /*find the stream file*/
    char * streamFile = malloc(sizeof(char)*(strlen("messages/")+strlen("stream.txt")+strlen(up->streamname)));
    strcpy(streamFile,"messages/");
    strcat(streamFile,up->streamname);
    strcat(streamFile,"Stream.txt");
    printf("file: %s\n", streamFile);
    FILE * fp = fopen(streamFile,"a+");
    
    /*add the post to the file*/
    fprintf(fp, "Sender: %s\n", up->username);
    fprintf(fp, "Date: %s\n", up->date);
    fprintf(fp, "%s\n", up->text);
    
    /*find the end*/
    int numLines = 0;
    char c;
    while (!feof(fp)){
        c = fgetc(fp);
        if (c=='\n')
            numLines ++;
    }
    return numLines;
}

void updateStreamData(userPost * up, int end){
    /*find the streamData file*/
    char * streamDataFile = malloc(sizeof(char)*(strlen("messages/")+strlen("streamData.txt")+strlen(up->streamname)));
    strcpy(streamDataFile,"messages/");
    strcat(streamDataFile,up->streamname);
    strcat(streamDataFile,"StreamData.txt");
    FILE * fp = fopen(streamDataFile,"a");

    /*add the number to the ned of the file*/
    fprintf(fp, "%d\n", end);
}

