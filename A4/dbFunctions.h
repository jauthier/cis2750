/*
*   dbFunctions.h
*   Author: jessica Auhtier
*   Date Modified: 2017/03/31
*/
#ifndef DBFUNCTIONS_H
#define DBFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

char ** getAllStreams ();

int checkTable (MYSQL mysql, char * stream);

int checkUser (MYSQL mysql, char * stream, char * user);

int getUsersCP (MYSQL mysql, char* user, char * stream);

void createTables (MYSQL mysql, char *stream);

void clearTables (MYSQL mysql);

void removeTables (MYSQL mysql);

void getStreams (MYSQL mysql);

void getUsers (MYSQL mysql);

void getPosts (MYSQL mysql);

void getStreamPosts(MYSQL mysql, char * stream);

void addUser (MYSQL mysql, char * stream, char * user);

void removeUser (MYSQL mysql, char * stream, char * user);

void post (MYSQL mysql, char *stream, char * user, char * date, char * text);

void printDataTable (MYSQL mysql, char * stream);

void printStreamUsers(MYSQL mysql, char * stream);

void updateUserTable (MYSQL mysql, char * stream, char * user);

#endif