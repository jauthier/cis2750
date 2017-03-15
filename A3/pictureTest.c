#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*pictures*/

void pictures (char * line, FILE *fp){
    char * src, * height, * width;
    char * extra = malloc(sizeof(char)*200);
    strcpy(extra," ");
    int nosize = 0;
    int noSrc = 0;

    char * token = strtok(line,",");
    while (token != NULL){

        if (strstr(token,"image") == NULL){
            src = strtok(token,"\"");
            src = strtok(NULL,"\"");
            noSrc = 1;
        } else if (strstr(token,"size") == NULL){
            token = strtok(token,"=");
            height = strtok(NULL,"=x");
            width = strtok(NULL,"x\n");
            nosize = 1;
        } else {
            strcat(extra, token);
            strcat(extra, " ");
        }
        token = strtok(NULL,",");
    }

    if (nosize == 0){ /*there is no size indicated*/
        strcpy(height, "100");
        strcpy(width, "100");
    }
    if (noSrc == 0)
        return;

    printf("    <img src=\"");
    printf("%s",src);
    printf("\" height=\"");
    printf("%s",height);
    printf("\" width=\"");
    printf("%s",width);
    printf("\"/>\n");
    free(extra);
}
