

void link (char * line, FILE *fp){
    char *text;
    char *link;
    char * extra = malloc(sizeof(char)*200);
    strcpy(extra," ");
    int noLink = 0;
    int noText = 0;

    char * token = strtok(line,",");
    while (token != NULL){
        if (strstr(token,"link") != NULL){
            link = strtok(token,"=");
            link = strtok(NULL,"=\n");
            noLink = 1;
        } else if (strstr(token,"text") != NULL){
            text = strtok(token,"\"");
            text = strtok(NULL,"\"");
            noText = 1;
        } else {
            strcat(extra, token);
            strcat(extra, " ");
        }
        token = strtok(NULL,",");
    }

    if (noText == 0)
        strcpy(text, "link");
    if (noLink == 0)
        return;

    printf("    <a href=\"");
    printf("%s", link);
    printf("\"");
    printf("%s", extra);
    printf(">");
    printf("%s\n", text);
    printf("</a>\n");
    free(extra);
}
