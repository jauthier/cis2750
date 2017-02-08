#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct userPost {
    char * username;
    char * streamname;
    char * date;
    char * text;
};

struct PostEntry {
    char * (*readInput)();
    char * (*getTimeData)();
    struct userPost * (*formatEntry)(char * username, char * streamname, char * text);
    
    void (*submitPost)();
};

struct userPost * createUserPost (char *username,char *streamname, char *date, char *text){
    struct userPost * newUP = malloc(sizeof(struct userPost));
    newUP->username = username;
    newUP->streamname = streamname;
    newUP->date = date;
    newUP->text = text;
    return newUP;
}

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
    printf("in getTimeData\n");
    time_t getTime = time (NULL);
    if (ctime(&getTime)==NULL)
        printf("null\n");
    printf("%s\n", ctime(&getTime));
    char * date  = malloc(sizeof(char)*strlen(ctime(&getTime)));
    strcpy(date, ctime(&getTime));

    return date;
}

struct userPost * formatEntry (char * username, char * streamname, char * text){
        char * date = getTimeData();
        struct userPost * newPost = createUserPost(username, streamname, date, text);
        return newPost;
}


void submitPost (struct userPost *up){
        printf("in sub post\n");
}

void peConstructor(struct PostEntry * pe){
    pe->readInput = readInput;
    pe->formatEntry = formatEntry;
    pe->getTimeData = getTimeData;
    pe->submitPost = submitPost;
}


int main (){
    
    struct PostEntry *pe;
    peConstructor(pe);
    /*char * text = pe->readInput();
    printf("%s\n", text);*/


    char * date = getTimeData();
    printf("%s\n", date);


    return 0;
}

