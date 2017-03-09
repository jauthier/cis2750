#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkStreamUsers (FILE *sufp, char *username);

int main (int argc, char *argv[]){
    char *username, *stream;
    strcpy(username,argv[1]);
    strcpy(stream, argv[2]);
    char * streamFile = malloc(sizeof(char)*(strlen("a2/messages/")+strlen(stream)+strlen("StreamUsers.txt")));
    strcpy(streamFile,"a2/messages/");
    strcat(streamFile,stream);
    strcat(streamFile,"StreamUsers.txt");
    /*check username and stream*/
    FILE * sufp = fopen(streamFile,"r");
    int checkSU = checkStreamUsers(sufp,username);
    fclose(sufp);
    free(streamFile);
    printf("%d\n", checkSU);
    return 0;
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