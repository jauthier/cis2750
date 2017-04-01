/*
*   dbFunctions.c
*   Author: jessica Auhtier
*   Date Modified: 2017/03/31
*/

#include "dbFunctions.h"

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
    }
    list[count] = NULL;
    return list;
}

/*check table exists*/
int checkTable (MYSQL mysql, char * stream){
    char *query = malloc(sizeof(char)*512);
    strcpy(query,"SHOW TABLES LIKE \'");
    strcat(query,stream);
    strcat(query,"Users\'");
    /*check if table exists*/
    mysql_query(&mysql, query);
    if (mysql_num_rows(mysql_store_results(&mysql)) > 0){
        free(query);
        return 1;
    }
    free(query);
    return 0;
}

int checkUser (MYSQL mysql, char * stream, char * user){
    char *query = malloc(sizeof(char)*512);
    strcpy(query,"SELECT user FROM ");
    strcat(query,stream); 
    strcat(query, "Users WHERE user = \'");
    strcat(query,user);
    strcat(query,"\'");
    /*check if table exists*/
    if (mysql_query(&mysql, query))
        return 0;
    if (mysql_num_rows(mysql_store_results(&mysql)) > 0){
        free(query);
        return 1;
    }
    free(query);
    return 0;
}

int getUsersCP (MYSQL mysql, char* user, char * stream){
    char *query = malloc(sizeof(char)*512);
    strcpy(query,"SELECT lastPost FROM ");
    strcat(query,stream); 
    strcat(query, "Users WHERE user = \'");
    strcat(query,user);
    strcat(query,"\'");
    /*check if table exists*/
    if (mysql_query(&mysql, query))
        return 0;
    MYSQL_RES *result = mysql_store_results(&mysql);
    if (result == 0)
        return 0;
    MYSQL_ROW row = mysql_fetch_row(result);
    printf("\n%s ", row[0] ? row[0] : " ");
    free(query);
    return 1;
}

/*create table*/
void createTables (MYSQL mysql, char *stream){
    /*create streamposts, streamUsers, streamData*/
    char *query = malloc(sizeof(char)*512);
    strcpy(query,"CREATE TABLE ");
    strcat(query,stream);
    strcat(query," (stream CHAR(30), user CHAR(30), date CHAR(30), text TEXT(1000))");
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
    free(query);
}

/*clear tables*/
void clearTables (MYSQL mysql){
    /*get the names of all the streams*/
    char ** list = getAllStreams();
    int i = 0;
    while (list[i] != NULL){
        char *query = malloc(sizeof(char)*512);
        strcpy(query,"TRUNCATE TABLE ");
        strcat(query,list[i]);
        mysql_query(&mysql, query);
        query[0] = '\0';
        strcpy(query,"TRUNCATE TABLE ");
        strcat(query,list[i]);
        strcat(query,"Users");
        mysql_query(&mysql, query);
        query[0] = '\0';
        strcpy(query,"TRUNCATE TABLE ");
        strcat(query,list[i]);
        strcat(query,"Data");
        mysql_query(&mysql, query);
        i++;
        free(query);
    }
    i = 0;
    while (list[i] != NULL){
        free(list[i]);
        i++;
    }
    free(list[i]);
    free(list);
    
}

/*remove tables*/
void removeTables (MYSQL mysql){
    /*get the names of all the streams*/
    char ** list = getAllStreams();
    int i = 0;
    while (list[i] != NULL){
        char *query = malloc(sizeof(char)*512);
        strcpy(query,"DROP TABLE IF EXISTS ");
        strcat(query,list[i]);
        mysql_query(&mysql, query);
        query[0] = '\0';
        (query,"DROP TABLE IF EXISTS ");
        strcat(query,list[i]);
        strcat(query,"Users");
        mysql_query(&mysql, query);
        query[0] = '\0';
        strcpy(query,"DROP TABLE IF EXISTS ");
        strcat(query,list[i]);
        strcat(query,"Data");
        mysql_query(&mysql, query);
        i++;
        free(query);
    }
    i = 0;
    while (list[i] != NULL){
        free(list[i]);
        i++;
    }
    free(list[i]);
    free(list);
}

/*get streams*/
void getStreams (MYSQL mysql){
    char ** list = getAllStreams();
    int i = 0;
    while (list[i] != NULL){
        printf("%s\n", list[i]);
        i++;
    }
    i = 0;
    while (list[i] != NULL){
        free(list[i]);
        i++;
    }
    free(list[i]);
    free(list);
}

/*get users*/
void getUsers (MYSQL mysql){
    /*make a user table to hold all the users*/
    char * query = malloc(sizeof(char)*512);
    strcpy(query,"SELECT * FROM users");
    if (mysql_query(&mysql, query))
        return;

    MYSQL_RES *result = mysql_store_result(&mysql);
    if (result == NULL)
        return;
    int num = mysql_num_fields(result);
    MYSQL_ROW row;
    while (row = mysql_fetch_row(result)){ 
        int i = 0;
        for (i=0; i<num; i++){ 
            printf("%s ", row[i] ? row[i] : "NULL"); 
        } 
            printf("\n"); 
    }
    mysql_free_result(result);
    free(query);
}

/*get posts*/
void getPosts (MYSQL mysql){
    char ** list = getAllStreams();
    int i = 0;
    while (list[i] != NULL){
        char * query = malloc(sizeof(char)*512);
        strcpy(query,"SELECT * FROM ");
        strcat(query,list[i]);
        mysql_query(&mysql, query);
        MYSQL_RES *result = mysql_store_result(&mysql);
        if (result == NULL)
            return;
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
  
        while (row = mysql_fetch_row(result)){ 
            int j = 0;
            for (j=0; j<num_fields; j++){ 
                printf("\n%s ", row[j] ? row[j] : " ");
            }
        }
        i++;
        mysql_free_result(result);
        free(query);
    }
    i = 0;
    while (list[i] != NULL){
        free(list[i]);
        i++;
    }
    free(list[i]);
    free(list);
    
}

void getStreamPosts(MYSQL mysql, char * stream){
    char * query = malloc(sizeof(char)*512);
    strcpy(query,"SELECT * FROM ");
    strcat(query,stream);
    mysql_query(&mysql, query);
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (result == NULL)
        return;
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
  
    while (row = mysql_fetch_row(result)){ 
        int j = 0;
        for (j=0; j<num_fields; j++){ 
            printf("\n%s ", row[j] ? row[j] : " ");
        }
    }
    mysql_free_result(result);
    free(query);

}

/*add user*/
void addUser (MYSQL mysql, char * stream, char * user){
    char * query = malloc(sizeof(char)*512);
    strcpy(query, "INSERT INTO ");
    strcat(query, stream);
    strcat(query, "Users VALUES (\'");
    strcat(query, user);
    strcat(query,"\', 0)");
    mysql_query(&mysql,query);
    free(query);
}

/*remove user*/
void removeUser (MYSQL mysql, char * stream, char * user){
    char * query = malloc(sizeof(char)*512);
    strcpy(query, "DELETE FROM ");
    strcat(query, stream);
    strcat(query, "Users WHERE users = \'");
    strcat(query, user);
    strcat(query,"\'");
    mysql_query(&mysql,query);
    free(query);
}

/*post*/
void post (MYSQL mysql, char *stream, char * user, char * date, char * text){
    
    char * query = malloc(sizeof(char)*512);
    strcpy(query,"INSERT INTO ");
    strcat(query,stream);
    strcat(query, " VALUES (\'");
    strcat(query,stream);
    strcat(query,"\', \'");
    strcat(query,user);
    strcat(query,"\', \'");
    strcat(query,date);
    strcat(query,"\', \'");
    strcat(query,text);
    strcat(query,"\', \')");
    mysql_query(&mysql,query);
    query[0] = '\0';
    mysql_query(&mysql, "INSERT INTO ");
    strcat(query,stream);
    strcat(query, "Data VALUES (0)");
    free(query);
}

void printDataTable (MYSQL mysql, char * stream){
    char * query = malloc(sizeof(char)*512);
    strcpy(query,"SELECT * FROM ");
    strcat(query,stream);
    strcat(query,"Data");
    mysql_query(&mysql, query);
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (result == NULL)
        return;
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
  
    while (row = mysql_fetch_row(result)){ 
        int j = 0;
        for (j=0; j<num_fields; j++){ 
            printf("%s ", row[j] ? row[j] : " ");
        }
    }
    mysql_free_result(result);
    free(query);
}

void printStreamUsers(MYSQL mysql, char * stream){
    char * query = malloc(sizeof(char)*512);
    strcpy(query,"SELECT user FROM ");
    strcat(query,stream);
    strcat(query,"User");
    mysql_query(&mysql, query);
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (result == NULL)
        return;
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
  
    while (row = mysql_fetch_row(result)){ 
        int j = 0;
        for (j=0; j<num_fields; j++){ 
            printf("%s ", row[j] ? row[j] : " ");
        }
    }
    mysql_free_result(result);
    free(query);
}

void updateUserTable (MYSQL mysql, char * stream, char * user){
    int num = getUsersCP (mysql, user, stream) + 1;
    char buffer[10];
    snprintf(buffer, 10, "%d",num);
    char * query = malloc(sizeof(char)*512);
    strcpy(query,"UPDATE ");
    strcat(query,stream);
    strcat(query,"Users SET lastPost=");
    strcat(query,buffer);
    strcat(query," WHERE user=\'");
    strcat(query,user);
    strcat(query,"\'");
    mysql_query(&mysql, query);
}
