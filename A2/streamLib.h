/*
    streamLib.h
    Author: Jessica Authier
    Date Modified: 2017/02/14
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct userPost {
    char * username;
    char * streamname;
    char * date;
    char * text;
};
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
int updateStream(struct userPost *up);

/*
    Takes a userPost struct and its end line number.
    Gets the streamname and opens the corresponding streamData file.
    Adds the line number to the end of the file.
*/
void updateStreamData(struct userPost * up, int end);

/*

*/
void addUSer(char *username, char *list);

/*

*/
void removeUser(char *username, char *list);
