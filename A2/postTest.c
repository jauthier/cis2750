// post.c  
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
	// take in user name
    char buffer[200];

    if (argc == 1){
        printf("Please enter your username.\n");
        exit;
    } else {
        int i;
        strcpy(buffer,argv[1]);
        for (i=2;i<argc;i++){
            //put all strings into one
            strcat(buffer, " ");
            strcat(buffer, argv[i]);
        }

        printf("%s\n",buffer);
    }
    char * username = malloc(sizeof(char)*strlen(buffer));
    strcpy(username,buffer);

    /* get the stream*/
    printf("stream: ");
    char stream[100];
    fgets(stream, 100, stdin);

    /*check if the stream exists and the user has permission to post on the stream*/
    char * streamFile = malloc(sizeof(char)*(strlen(stream)+strlen("StreamUsers")));
    strcpy(streamFile,stream);
    strcat(streamFile,"StreamUsers");

    FILE * sufp = fopen(streamFile,"r");
    int checkSU = checkStreamUsers(sufp,username);
    if (checkSU == 0)
        return 0;



    

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
