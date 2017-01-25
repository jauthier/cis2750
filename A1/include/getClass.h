/*
* getClass.h
* Jessica Authier
* 2017/01/25
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void translate(List *tokenList);

Line *classToStruct(Line *class, Line *restOfList);

char *methodParameters (Line * line);

Element *changeFuncNames(Element *list, char * className, char *oldName, char *newName);

int isType(char * str);

int isWhiteSpace(char * str);

int isComment(char *str);
