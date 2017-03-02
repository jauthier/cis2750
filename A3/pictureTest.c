#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*pictures*/

void pictures(char * line){
    char * src;
    char * height;
    char * width;

    printf("%s\n", line);
    char * token = strtok(line,"()");
    token = strtok(NULL,"()");

    /*token holds the inside of the ()*/
    char * token2 = strtok(token,",");
    token = strtok(NULL,",");
    if (token == NULL){ /*there is no size indicated*/
        printf("no size\n");
        src = strtok(token2,"\"");
        height = "100";
        width = "100";
    } else {
        /*check which one is image and which one is size*/
        if (strstr(token,"image")){
            printf("image first\n");
            /*get the stuff between the quotes*/
            src = strtok(token,"\"");
            token = strtok(token2,"<>");
            height = strtok(NULL,"<>");
            width = strtok(NULL,"<>");
        } else {
            src = strtok(token2,"\"");
            token = strtok(token,"<>");
            height = strtok(NULL,"<>");
            width = strtok(NULL,"<>");
        }
    }

    char * newLine = malloc(sizeof(char)*(strlen("    <img src=\"")
        + strlen(src) + strlen("\" height=\"") + strlen(height)
        + strlen("\" width=\"") + strlen(width) + strlen("\"/>\n")));
    printf("%s\n", newLine);
}

int main (int argc, char *argv[]){
    char hold[] = ".p(image=\"this_pic\", size=<20><30>)";
    pictures(hold);
    return 0;
}

