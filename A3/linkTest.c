

void link (char * line, FILE *fp){
    char *text;
    char *link;

    char * token = strtok(line,"()");
    token = strtok(NULL,"()");

    /*token holds the inside of the ()*/
    char * token2 = strtok(token,",");
    token = strtok(NULL,",");

    if (if token == NULL){
        link = strtok(token2,"<>");
        link = strtok(NULL,"<>");
        text = "link";
    } else {
        if (strstr(token,"link")){
            text = strtok(token2,"\"");
            text = strtok(NULL,"\"");
            link = strtok(token,"=");
            link = strtok(NULL,"=\n");
        } else {
            text = strtok(token,"\"");
            text = strtok(NULL,"\"");
            link = strtok(token2,"=");
            link = strtok(NULL,"=\n");
        }
    }

    char * newLine = malloc(sizeof(char)*(strlen("    <a href=\"") + strlen(link) 
        + strlen("\">") + strlen(text) + strlen("</a>\n")));
    strcpy(newLine,"    <a href=\"");
    strcat(newLine,link);
    strcat(newLine,"\">");
    strcat(newLine,text);
    strcat(newLine,"</a>\n");
    fprintf(fp,"%s", newLine);
    free(newLine);
}
