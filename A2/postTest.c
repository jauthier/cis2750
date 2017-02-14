// post.c  
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int checkStreamUsers (FILE *sufp, char *username);

class PostEntry(){

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

    struct userPost * formatEntry (char * username, char * streamname, char * text){
        char * date = getTimeData();
        struct userPost * newPost = createUserPost(username, streamname, date, text);
        return newPost;
    }

    char * getTimeData (){
        time_t getTime = time (NULL);
        char * date  = malloc(sizeof(char)*strlen(ctime(&getTime)));
        strcpy(date, ctime(&getTime));
        return date;
    }

    void submitPost (struct userPost *up){

    }
};

int main (int argc, char *argv[]){
	/* take in user name*/
    char buffer[200];

    if (argc == 1){
        printf("Please enter your username.\n");
        exit;
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

    FILE * sufp = fopen(streamFile,"r");
    int checkSU = checkStreamUsers(sufp,username);
    if (checkSU == 0)
        return 0;

    struct PostEntry * pe;
    pe = malloc(sizeof(struct PostEntry));        
    char * text = pe->readInput();



    return 0;
}

int checkStreamUsers (FILE *sufp, char *username){

    if (sufp == NULL){
        printf("The stream you wish to access does not exist!\n");
        return 0;
    }

    char userLine[210];
    while (fgets(userLine,210,sufp) != NULL){
        if (strstr(userLine,userName) != NULL)
            return 1;
    }
    printf("You do not have permission to post to this stream!\n");
    return 0;
}
