#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#define HOSTNAME "dursley.socs.uoguelph.ca"
#define USERNAME "jauthier"
#define PASSWORD "0849720"
#define DATABASE "jauthier"

#define MAX_QUERY 512


/*create table*/
void createTables (MYSQL mysql, char *stream){
    /*create streamposts, streamUsers, streamData*/
    char *query = malloc(sizeof(char)*200);
    strcpy(query,"CREATE TABLE ");
    strcat(query,stream);
    strcat(query," (id INT NOT NULL auto_increment, stream CHAR[30], user CHAR[30]), date CHAR[30]), text CHAR[100]");
    mysql_query(&mysql, query);
    query[0] = '\0';
    strcpy(query,"CREATE TABLE ");
    strcat(query,stream);
    strcat(query,"Users (user CHAR[30]), lastPost INT DEFAULT 0)");
    mysql_query(&mysql, query);
    query[0] = '\0';
    strcpy(query,"CREATE TABLE ");
    strcat(query,stream);
    strcat(query,"Data (postEnd INT)");
    mysql_query(&mysql, query);
    query[0] = '\0';
}

/* get the names of all the current streams*/
char ** getAllStreams (){
    char * file = "a2/messages/allStreams.txt";
    FILE * fp = fopen(file, "r");
    int count = 0;
    while (!feof(fp)){
        count ++;
    }
    char ** list = malloc(sizeof(*list)*count);
    char line[31];
    int i = 0;
    for (i=0;i<count;i++){
        fgets(line, 31, fp);
        line[strlen(line)] = '\0';
        char * hold = malloc(sizeof(char)*strlen(line));
        strcpy(hold,line);
        list[i] = hold;
    }
    for (i=0;i<count;i++){
        printf("%s\n", list[i]);
    }
    return list;
}

int main(int argc, char *argv[]){

    // get the host name from the command line
    if (argc < 2){
        printf("You must enter an action.\n");
        exit(0);
    }
    char * action = malloc(sizeof(char)*strlen(argv[1]));
    strcpy(action,argv[1]);

    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL_FIELD *field;
    char query[MAX_QUERY];

    /*Connect to Database Server*/
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql,HOSTNAME,USERNAME,PASSWORD,DATABASE,0,NULL,0)){
        printf("could not connect to host.\n%s\n",mysql_error(&mysql));
        exit(0);
    }
    
    if (strcmp(action,"-streams")==0){
        char ** list = getAllStreams();
    }

    return 0;
}