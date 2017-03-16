/*
    translateConfig.c
    Author: Jessica Authier
    Date Modified: 2017/03/15
*/

#include "translateConfig.h"

void button (char * line, FILE * fp){
    char *name;
    char *link;

    char * extra = malloc(sizeof(char)*200);
    strcpy(extra," ");
    int noLink = 0;
    int noName = 0;

    char * token = strtok(line,",");
    while (token != NULL){
        if (strstr(token,"link") != NULL){
            link = strtok(token,"\"");
            link = strtok(NULL,"\"");
            noLink = 1;
        } else if (strstr(token,"name") != NULL){
            name = strtok(token,"\"");
            name = strtok(NULL,"\"");
            noName = 1;
        } else {
            strcat(extra, token);
            strcat(extra, " ");
        }
        token = strtok(NULL,",");
    }

    if (noName == 0)
        strcpy(name, "Button");
    if (noLink == 0)
        return;

    fprintf(fp, "<form>\n");
    fprintf(fp, "\"    <button formaction=\"");
    fprintf(fp, "%s", link);
    fprintf(fp, "\" ");
    fprintf(fp,"%s", extra);
    fprintf(fp, ">");
    fprintf(fp, "%s", name);
    fprintf(fp, "</button>");
    fprintf(fp, "</form>\n");
    free(extra);
}

void executable (char * line, FILE * fp){
    char * file;
    int noFile = 0;

    char * token = strtok(line,",");
    while (token != NULL){
        if (strstr(token,"exe") != NULL){
            file = strtok(token,"=");
            file = strtok(NULL,"=\n");
            noFile = 1;
        }
        token = strtok(NULL,",");
    }

    if (noFile == 0)
        return;

    fprintf(fp, "<?php exec(");
    fprintf(fp, "%s", file);
    fprintf(fp, "); ?>\n");
}

void headings (char * line, FILE * fp){
    char *text;
    char *size;
    char * extra = malloc(sizeof(char)*200);
    strcpy(extra," ");
    int nosize = 0;
    int noText = 0;

    char * token;
    token = strtok(line,",=");
    while ( token != NULL){
        if (strcmp(token,"size") == 0){
            size = strtok(NULL,",=");
            nosize = 1;
        } else if (strcmp(token,"text") == 0){
            text = strtok(NULL,",=\"");
            noText = 1;
        } else {
            strcat(extra, token);
            token = strtok(NULL,",");
            strcat(extra,"=");
            strcat(extra,token);
            strcat(extra, " ");
        }
        token = strtok(NULL,",=");
    }

    if (nosize == 0)
       strcpy(size, "3");
    if (noText == 0)
        strcpy(text, " ");
    
    fprintf(fp, "<h");
    fprintf(fp, "%s", size);
    fprintf(fp, "%s", extra);
    fprintf(fp, ">");
    fprintf(fp, "%s", text);
    fprintf(fp, "</h");
    fprintf(fp, "%s", size);
    fprintf(fp, ">\n");
    free(extra);
}

void input (char * line, FILE * fp){
    char * action, * text,  * name, * value;
    char * extra = malloc(sizeof(char)*200);
    strcpy(extra," ");
    int noAction = 0;
    int noText = 0;
    int noName = 0;
    int noValue = 0;

    char * token;
    token = strtok(line,",=");
    while (token != NULL){
        if (strcmp(token,"action") == 0){
            action = strtok(NULL,"\"");
            noAction = 1;
        } else if (strcmp(token,"text") == 0){
            text = strtok(NULL,"\"");
            noText = 1;
        } else if (strcmp(token,"name") == 0){
            name = strtok(NULL,"\"");
            noName = 1;
        } else if (strcmp(token,"value") == 0){
            value = strtok(NULL,"\"");
            noValue = 1;
        } else {
            strcat(extra, token);
            token = strtok(NULL,",");
            strcat(extra,"=");
            strcat(extra,token);
            strcat(extra, " ");
        }
        token = strtok(NULL,",="); 
    }
    if (noAction == 0)
        return;
    if (noText == 0)
        strcpy(text, "Input");


    fprintf(fp, "<form type=\"post\" action=\"");
    fprintf(fp, "%s\"\n    ", action);
    fprintf(fp, "%s\"", text);
    fprintf(fp, ": <input type=\"text\"");
    if (noName == 1){
        fprintf(fp, " name=\"");
        fprintf(fp, "%s", name);
        fprintf(fp, "\"");
    }
    if (noValue ==1){
        fprintf(fp, " value=\"");
        fprintf(fp, "%s", value);
        fprintf(fp, "\"");
    }
    fprintf(fp, "%s", extra);
    fprintf(fp, ">\n");
    fprintf(fp, "    <input type=\"submit\">\n");
    fprintf(fp, "</form>\n");
    free(extra);
}

void link (char * line, FILE * fp){
    char *text;
    char *link;
    char * extra = malloc(sizeof(char)*200);
    strcpy(extra," ");
    int noLink = 0;
    int noText = 0;

    char * token = strtok(line,",=");
    while (token != NULL){
        if (strcmp(token,"link") == 0){
            link = strtok(NULL,"=");
            noLink = 1;
        } else if (strcmp(token,"text") == 0){
            text = strtok(NULL,"\"");
            noText = 1;
        } else {
            strcat(extra, token);
            token = strtok(NULL,",");
            strcat(extra,"=");
            strcat(extra,token);
            strcat(extra, " ");
        }
        token = strtok(NULL,",=");
    }

    if (noText == 0)
        strcpy(text, "link");
    if (noLink == 0)
        return;

    fprintf(fp,"    <a href=\"");
    fprintf(fp,"%s", link);
    fprintf(fp,"\"");
    fprintf(fp,"%s", extra);
    fprintf(fp,">");
    fprintf(fp,"%s", text);
    fprintf(fp,"</a>\n");
    free(extra);
}

void pictures (char * line, FILE * fp){
    char * src, * height, * width;
    char * extra = malloc(sizeof(char)*200);
    strcpy(extra," ");
    int nosize = 0;
    int noSrc = 0;

    char * token = strtok(line,",=");
    while (token != NULL){

        if (strcmp(token,"image") == 0){
            src = strtok(NULL,"\"");
            noSrc = 1;
        } else if (strcmp(token,"size") == 0){
            height = strtok(NULL,"=x");
            width = strtok(NULL,"x");
            nosize = 1;
        } else {
            strcat(extra, token);
            strcat(extra, " ");
        }
        token = strtok(NULL,",=");
    }

    if (nosize == 0){ /*there is no size indicated*/
        strcpy(height, "100");
        strcpy(width, "100");
    }
    if (noSrc == 0)
        return;

    fprintf(fp, "    <img src=\"");
    fprintf(fp, "%s",src);
    fprintf(fp, "\" height=\"");
    fprintf(fp, "%s",height);
    fprintf(fp, "\" width=\"");
    fprintf(fp, "%s",width);
    fprintf(fp, "\" ");
    fprintf(fp, "%s", extra);
    fprintf(fp, "/>\n");
    free(extra);
}

void radioButton (char * line, FILE *fp){
    char * action, * name;
    char * values[10];
    char * extra = malloc(sizeof(char)*200);
    strcpy(extra," ");
    int noAction = 0;
    int noName = 0;
    int noValues = 0;
    int valCount = 0;

    char * token = strtok(line,",");
    while (token != NULL){
        if (strstr(token,"action") == NULL){
            action = strtok(token,"\"");
            action = strtok(NULL,"\"");
            noAction = 1;
        } else if (strstr(token,"name") == NULL){
            name = strtok(token,"\"");
            name = strtok(NULL,"\"");
            noName = 1;
        } else if (strstr(token,"value") == NULL){
            token = strtok(token,"\"");
            values[valCount] = strtok(NULL,"\"");
            noValues = 1;
            valCount ++;
        } else {
            strcat(extra, token);
            strcat(extra, " ");
        }
        token = strtok(NULL,",");
    }

    if (noAction == 0||noValues == 0)
        return;

    fprintf(fp, "<form type=\"post\" action=\"%s\">\n",action);
    if (noName == 0)
        fprintf(fp, "    <input type=\"radio\" value=\"%s\" checked> %s <br>\n", values[0], values[0]);
    else 
        fprintf(fp, "    <input type=\"radio\" name=\"%s\" value=\"%s\" checked> %s <br>\n", name, values[0], values[0]);
    int i;
    for (i=1;i<valCount;i++){
        if (noName == 0)
            fprintf(fp, "    <input type=\"radio\" value=\"%s\"> %s <br>\n", values[i], values[i]);
        else 
            fprintf(fp, "    <input type=\"radio\" name=\"%s\" value=\"%s\"> %s <br>\n", name, values[i], values[i]);
    }
    fprintf(fp, "    <input type=\"submit\">\n");
    fprintf(fp, "<form>\n");
    free(extra);
}

void text (char * line, FILE * fp){
    char * text;
    char * extra = malloc(sizeof(char)*200);
    strcpy(extra," ");
    char buffer[100];
    int noFile = 0;
    int noText = 0;

    char * token = strtok(line,",");
    while(token != NULL){
        if (strstr(token,"text") == NULL){
            text = strtok(token,"\"");
            text = strtok(NULL,"\"");
            noText = 1;
        } else if (strstr(token,"file") == NULL){
            char * file = strtok(token,"\"");
            file = strtok(NULL,"\"");
            text = malloc(sizeof(char)*1000);
            FILE * fp2 = fopen(file,"r");
            if (fp2 == NULL){
                printf("The file: %s was not found.\n", file);
                return;
            }
            strcpy(text,fgets(buffer, 100, fp2));
            while (buffer != NULL){
                fgets(buffer, 100, fp2);
                strcat(text, buffer);
            }
            noFile = 1;
        } else {
            strcat(extra, token);
            strcat(extra, " ");
        }
        token = strtok(NULL,",");
    }

    if (noFile == 0||noText == 0)
        return;

    fprintf(fp, "<p %s>\n", extra);
    fprintf(fp, "%s\n", text);
    fprintf(fp, "</p>\n");
    free(extra);
    free(text);
}
