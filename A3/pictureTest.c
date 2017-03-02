#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*pictures*/

void pictures(char * line){
    char * src;
    char * height;
    char * width;

    char * token = strtok(line,"()");
    token = strtok(NULL,"()");

    /*token holds the inside of the ()*/
    char * token2 = strtok(token,",");
    token = strtok(NULL,",");
    if (token == NULL){ /*there is no size indicated*/
        src = strtok(token2,"\"");
        src = strtok(NULL,"\"");
        height = "100";
        width = "100";
    } else {
        /*check which one is image and which one is size*/
        if (strstr(token,"image")){
            /*get the stuff between the quotes*/
            src = strtok(token,"\"");
            src = strtok(NULL,"\"");
            token = strtok(token2,"<>");
            height = strtok(NULL,"<>");
            width = strtok(NULL,"<>");
        } else {
            src = strtok(token2,"\"");
            src = strtok(NULL,"\"");
            token = strtok(token,"<>");
            height = strtok(NULL,"<>");
            width = strtok(NULL,"<>");
        }
    }

    char * newLine = malloc(sizeof(char)*(strlen("    <img src=\"")
        + strlen(src) + strlen("\" height=\"") + strlen(height)
        + strlen("\" width=\"") + strlen(width) + strlen("\"/>\n")));
    strcpy(newLine,"    <img src=\"");
    strcat(newLine,src);
    strcat(newLine,"\" height=\"");
    strcat(newLine,height);
    strcat(newLine,"\" width=\"");
    strcat(newLine,width);
    strcat(newLine,"\"/>\n");
    printf("%s", newLine);
}

int main (int argc, char *argv[]){
    char hold[] = ".p(image=\"this_pic\", size=<20><30>)";
    pictures(hold);
    char hold1[] = ".p(image=\"this_pic\")";
    pictures(hold1);
    char hold2[] = ".p(size=<20><30>, image=\"this_pic\")";
    pictures(hold2);
    return 0;
}

