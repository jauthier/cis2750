/*heading*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void headings (char *line, FILE *fp){
    char *text;
    char *size;

    char * token = strtok(line,"()");
    token = strtok(NULL,"()");

    /*token holds the inside of the ()*/
    char * token2 = strtok(token,",");
    token = strtok(NULL,",");

    if (if token == NULL){
        text = strtok(token2,"\"");
        text = strtok(NULL,"\"");
        size = "3";
    } else {
        if (strstr(token,"size")){
            text = strtok(token2,"\"");
            text = strtok(NULL,"\"");
            size = strtok(token,"=\n");
            size = strtok(NULL,"=\n");
        } else {
            text = strtok(token,"\"");
            text = strtok(NULL,"\"");
            size = strtok(token2,"=\n");
            size = strtok(NULL,"=\n");
        }
    }

    char * newLine = malloc(sizeof(char)*(strlen("    <h") + strlen(size) 
        + strlen(">") + strlen(text) + strlen("</h") + strlen(size) + strlen(">\n")));
    strcpy(newLine,"    <h");
    strcat(newLine,size);
    strcat(newLine,">");
    strcat(newLine,text);
    strcat(newLine,"</h");
    strcat(newLine,size);
    strcat(newLine,">\n");
    fprintf(fp, "%s", newLine);
    free(newLine);
}

int main (int argc, char * argv[]){
    char hold[] = ".h(size=<2>,text="Hello World")";
    headings(hold);
    return 0;
}
