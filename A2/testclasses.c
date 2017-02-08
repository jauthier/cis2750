#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct userPost {
    char * username;
    char * streamname;
    char * date;
    char * text;
}userPost;

struct PostEntry {
    char * (* readInput)();
    userPost * (*formatEntry)(char * username, char * streamname, char * text);
    char * (*getTimeData)();
    void (*submitPost)();
};

userPost * createUserPost (char *username,char *streamname, char *date, char *text){
    userPost * newUP = malloc(sizeof(userPost));
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

userPost * formatEntry (char * username, char * streamname, char * text){
        char * date = getTimeData();
        userPost * newPost = createUserPost(username, streamname, date, text);
        return newPost;
}


void submitPost (userPost *up){
        printf("in sub post\n");
}

void peConstructor(struct PostEntry *pe){
    printf("in constructor\n");
    pe->readInput = *readInput;
    printf("first\n");
    pe->formatEntry = &formatEntry;
    pe->getTimeData = &getTimeData;
    pe->submitPost = &submitPost;
}


int main (){
    printf("initalize struct\n");
    struct PostEntry *pe;
    printf("call constructor\n");
    peConstructor(pe);
    /*char * text = pe->readInput();
    printf("%s\n", text);*/

    printf("call getTimeData\n");
    char * date = getTimeData();
    printf("%s\n", date);


    return 0;
}

