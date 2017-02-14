#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "streamLib.h"

struct PostEntry {
    char * (* readInput)();
    userPost * (*formatEntry)(char * username, char * streamname, char * text);
    char * (*getTimeData)();
    void (*submitPost)();
};

char * readInput ();
char * getTimeData ();
userPost * formatEntry (char * username, char * streamname, char * text);
void submitPost (userPost *up);
int checkStreamUsers (FILE *sufp, char *username);

char * readInput (){
    char buffer[100];
    char *hold = malloc(sizeof(char)*1000);
    printf("Enter text: ");
    if (fgets(buffer, 100, stdin) != NULL){
        strcpy(hold, buffer);
        while (fgets(buffer, 100, stdin) != NULL){
            strcat(hold, buffer);
        }
    }
    char *text = malloc(sizeof(char)*strlen(hold));
    return text;
}

char * getTimeData (){
    time_t getTime = time (NULL);
    char * date  = malloc(sizeof(char)*strlen(ctime(&getTime)));
    strcpy(date, ctime(&getTime));
    return date;
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

void peConstructor(struct PostEntry *pe){
    printf("in constructor\n");
    pe->readInput = &readInput;
    printf("first\n");
    pe->formatEntry = &formatEntry;
    pe->getTimeData = &getTimeData;
    pe->submitPost = &submitPost;
}


int main (int argc, char *argv){
    /* take in user name*/
    char buffer[200];

    if (argc == 1){
        printf("Please enter your username.\n");
        exit(0);
    } else {
        int i;
        strcpy(buffer,argv[1]);
        for (i=2;i<argc;i++){
            /*put all strings into one*/
            strcat(buffer, " ");
            strcat(buffer, argv[i]);
        }
    }
    char * username = malloc(sizeof(char)*strlen(buffer));
    strcpy(username,buffer);

    /* get the stream*/
    printf("stream: ");
    char streamHold[100];
    fgets(streamHold, 100, stdin);
    char * stream = malloc(sizeof(char)*strlen(streamHold));

    /*check if the stream exists and the user has permission to post on the stream*/
    char * streamFile = malloc(sizeof(char)*(strlen(stream)+strlen("StreamUsers")));
    strcpy(streamFile,stream);
    strcat(streamFile,"StreamUsers");
    /*check username and stream*/
    FILE * sufp = fopen(streamFile,"r");
    int checkSU = checkStreamUsers(sufp,username);
    if (checkSU == 0)
        exit(0);
    
    struct PostEntry * pe;
    pe = malloc(sizeof(struct PostEntry));        
    /*get the post text*/
    char * text = pe->readInput();
    /*format the post into a UserPost struct*/
    userPost * newPost = formatEntry(username, stream, text);


    return 0;
}

int checkStreamUsers (FILE *sufp, char *username){

    if (sufp == NULL){
        printf("The stream you wish to access does not exist!\n");
        return 0;
    }

    char userLine[210];
    while (fgets(userLine,210,sufp) != NULL){
        if (strstr(userLine,username) != NULL)
            return 1;
    }
    printf("You do not have permission to post to this stream!\n");
    return 0;
}

