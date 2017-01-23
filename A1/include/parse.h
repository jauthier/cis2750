/*
	parse.h
	Jessica Authier
	2017/01/16
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"


/*
* Reads in a file and parses it, printing each token on a new line.
*/
void parseFile(FILE *fp);

/*
* Sorts the character into one of three categories
*/
int sort(char c);

/*
* Take the parsed file and turns it into a List
*/
List *fileToList(char *fileName);