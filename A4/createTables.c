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
    char * file = "allStreams.txt";
    FILE * fpCount = fopen(file, "r");
    int count = 0;
    char line[31];
    while (!feof(fpCount)){
        fgets(line, 31, fpCount);
        count ++;
    }
    fclose(fpCount);
    FILE * fp = fopen(file, "r");
    char ** list = malloc(sizeof(char*)*count);
    int i = 0;
    for (i=0;i<count;i++){
        fgets(line, 31, fp);
        line[strlen(line)-1] = '\0';
        char * hold = malloc(sizeof(char)*strlen(line));
        strcpy(hold,line);
        list[i] = hold;
        printf("%s\n", list[i]);
    }

    list[count] = NULL;
    return list;
}

void getUsers (MYSQL mysql){
    /*make a user table to hold all the users*/
    char * query = malloc(sizeof(char)*200);
    strcpy(query,"SELECT * FROM users");
    if (mysql_query(&mysql, query))
        return;

    MYSQL_RES *result = mysql_store_result(&mysql);
    if (result == NULL)
        return;
    int num = mysql_num_fields(result);
    MYSQL_ROW row;
    printf("%d\n", num);
    while (row = mysql_fetch_row(result)){ 
        printf("in loop\n");
        int i = 0;
        for (i=0; i<num; i++){ 
            printf("here1\n");
            printf("%s ", row[i] ? row[i] : "NULL"); 
        } 
            printf("\n"); 
    }
  
  mysql_free_result(result);
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
        int i = 0;
        while (list[i] != NULL){
            printf("%s\n", list[i]);
            i++;
        }
    } else if (strcmp(action,"-users")==0){
        if (mysql_query(&mysql,"CREATE TABLE users (user CHAR(30))"))
        mysql_query(&mysql,"INSERT INTO users VALUES ('jess')");
        mysql_query(&mysql,"INSERT INTO users VALUES ('josh')");
        mysql_query(&mysql,"INSERT INTO users VALUES ('luke')");
        printf("here\n");
        getUsers(mysql);
    }


    return 0;
}