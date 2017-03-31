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
    strcat(query," (id INT NOT NULL auto_increment, stream CHAR[30],
        user CHAR[30]), date CHAR[30]), text CHAR[100]");
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
    mysql_init(mysql);
    if (!mysql_real_connect(&mysql,HOSTNAME,USERNAME,PASSWORD,DATABASE,0,NULL,0)){
        printf("could not connect to host.\n%s\n",mysql_error(mysql));
        exit(0);
    }
    createTables(mysql, "cats");
    return 0;
}