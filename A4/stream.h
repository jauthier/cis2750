/*
    streamLib.h
    Author: Jessica Authier
    Date Modified: 2017/02/31s
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "dbFunctions.c"

typedef struct userPost {
    char * username;
    char * streamname;
    char * date;
    char * text;
}userPost;

/*
    Creates and returns a userPost structure.
*/
struct userPost * createUserPost (char *username,char *streamname, char *date, char *text);

/*
    Takes a userPost struct, frees the momory and destroyes it.
*/
void destroyUserPost(struct userPost *toDestroy);

/*
    Takes a userPost struct, gets its streamname and opens the corresponding stream file.
    Adds the post to the stream file and counts the number of lines in the file.
    Returns the end line number of the post.
*/
void updateStream(struct userPost *up);

/*

*/
void addUser(char *username, char *list);

/*

*/
void removeUser(char *username, char *list);
