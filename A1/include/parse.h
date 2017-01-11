/*
	parse.h
	Jessica Authier
	01/11/2017
*/

#include <stdio.h>
#include <stdlib.h>

/*
* Reads in a file and parses it, printing each token on a new line.
*/
void parseFile(FILE *fp);

/*
* Sorts the character into one of three categories
*/
int sort(char c);
