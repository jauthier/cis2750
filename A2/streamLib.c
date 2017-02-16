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
    fprintf(fp, "Date: %s", up->date);
    fprintf(fp, "%s\n", up->text);
    
    /*find the end*/
    int numLines = 0;
    char c;
    while (!feof(fp)){
        c = fgetc(fp);
        if (c=='\n')
            numLines ++;
    }
    free(streamFile);
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
    free(streamDataFile);
}

void addUser(char *username, char *list){
    /*tokenize the stream  list*/
    char * token = strtok(list," ,\n");
    while (token != NULL){
        /*get the name of the file*/
        printf("in add file\n");
        char * streamFile = malloc(sizeof(char)*(strlen("messages/")+strlen(token)+strlen("StreamUsers.txt")));
        strcpy(streamFile,"messages/");
        strcat(streamFile,token);
        strcat(streamFile,"StreamUsers.txt");


        /*check the file exists*/
        int check = 0;
        FILE *fpTest = fopen(streamFile, "r");
        if (fpTest == NULL){
            makeStreamFiles(token);
        } else {
            /*check if the username is already in the file*/
            char line[100];
            while (!feof(fpTest)){   
                fgets(line,100,fpTest);
                if (strstr(line, username)==NULL){
                    check = 1;
                }
            }
        }
        fclose(fpTest);
        /*open the file and add the user*/
        if (check == 0){
            FILE * fp = fopen(streamFile, "a");
            fprintf(fp, "%s 0\n", username);
            fclose(fp);
        }
        free(streamFile);
        token = strtok(NULL, " ,\n");
    }
}

void removeUser(char *username, char *list){
    /*tokenize the stream  list*/
    char * token = strtok(list," ,\n");
    while (token != NULL){
        /*get the name of the file*/
        char * streamFile = malloc(sizeof(char)*(strlen("messages/")+strlen(token)+strlen("StreamUsers.txt")));
        strcpy(streamFile,"messages/");
        strcat(streamFile,token);
        strcat(streamFile,"StreamUsers.txt");

        /*open the file*/
        FILE *fp = fopen(streamFile,"r+");
        if (fp == NULL) /*if the file doesn't exist then there is no need to remove the user*/
            return;

        writeFile(streamFile,username);
        token = strtok(NULL, " ,\n");
        free(streamFile);
    }
}

void makeStreamFiles(char *stream){
    
    /*make stream file*/
    char * streamFile = malloc(sizeof(char)*(strlen("messages/")+strlen(stream)+strlen("Stream.txt")));
    strcpy(streamFile,"messages/");
    strcat(streamFile,stream);
    strcat(streamFile,"Stream.txt");
    FILE * fp1 = fopen(streamFile,"w");
    fclose(fp1);

    /*make streamData file*/
    char * streamDataFile = malloc(sizeof(char)*(strlen("messages/")+strlen(stream)+strlen("StreamData.txt")));
    strcpy(streamDataFile,"messages/");
    strcat(streamDataFile,stream);
    strcat(streamDataFile,"StreamData.txt");
    FILE * fp2 = fopen(streamDataFile,"w");
    fclose(fp2);
    free(streamFile);
    free(streamDataFile);
}

void writeFile(char * fileName, char * username){
    char tempFile[] = "temp.txt";
    FILE * fpIn = fopen(tempFile,"w");
    FILE * fpOut = fopen(fileName,"r");
    char line[100]; 
    while (!feof(fpOut)){   
        fgets(line,100,fpOut);
        if (strstr(line, username)==NULL){
            fprintf(fpIn, "%s\n", line);
        }
    }
    fclose(fpOut);
    remove(fileName);
    rename(tempFile,fileName);
    fclose(fpIn);
}
