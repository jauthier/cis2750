/*
* getClass.h
* Jessica Authier
* 2017/01/25
*/

#ifndef GETCLASS_H
#define GETCLASS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lineList.h>

void translate(List *tokenList);

Line *classToStruct(Line *class, Line *restOfList);

char *methodParameters (Line * line);

Line *changeFuncNames(Line *list, char * className, char *oldName, char *newName);

int isType(char * str);

int isWhiteSpace(char * str);

int isComment(char *str);

#endif
