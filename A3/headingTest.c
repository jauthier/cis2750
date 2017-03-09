/*heading*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void headings (char *line, FILE *fp){
    char *text;
    char *size;
    char * extra = malloc(sizeof(char)*200);
    strcpy(extra," ");
    int nosize = 0;
    int noText = 0;

    char * token = strtok(line,",");
    while (token != NULL){

        if (strstr(token,"size") == NULL){
            size = strtok(token,"=\n");
            size = strtok(NULL,"=\n");
            nosize = 1;
        } else if (strstr(token,"text") == NULL){
            text = strtok(token,"\"");
            text = strtok(NULL,"\"");
            noText = 1;
        } else {
            strcat(extra, token);
            strcat(extra, " ");
        }
        token = strtok(NULL,",");
    }

    if (nosize == 0)
       strcpy(size, "3");
    if (noText == 0)
        strcpy(text, " ");
    
    printf("    <h");
    printf("%s", size);
    printf("%s", extra);
    printf(">");
    printf("%s", text);
    printf("</h");
    printf("%s", size);
    printf(">\n");
    free(extra);
}
