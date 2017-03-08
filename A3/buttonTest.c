

void button (char * line, FILE *fp){
    char *name;
    char *link;

    char * token = strtok(line,"()");
    token = strtok(NULL,"()");

    /*token holds the inside of the ()*/
    char * token2 = strtok(token,",");
    token = strtok(NULL,",");

    if (strstr(token,"link")){
        name = strtok(token2,"\"");
        name = strtok(NULL,"\"");
        link = strtok(token,"\"");
        link = strtok(NULL,"\"");
    } else {
        name = strtok(token,"\"");
        name = strtok(NULL,"\"");
        link = strtok(token2,"\"");
        link = strtok(NULL,"\"");
    }
    char * newLine = malloc(sizeof(char)*(strlen("        <button formaction=\"") + strlen(link)
        + strlen("\">") + strlen(name) + strlen("</button>\n")));
    strcpy(newLine,"        <button tpye=\"submit\"");
    strcat(newLine,link);
    strcat(newLine,"\">");
    strcat(newLine,name);
    strcat(newLine,"</button>\n");
    fprintf(fp, "<form>\n");
    fprintf(fp,"%s", newLine);
    fprintf(fp, "</form>\n");
    free(newLine);
}

