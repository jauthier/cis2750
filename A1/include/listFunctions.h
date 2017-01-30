/*
* listFunctions.h
* Jessica Auhtier
* 2017/01/26
*/

#ifndef LISTFUNCTIONS_H
#define LISTFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lineList.h"

Line * whileWSC (Line *temp);

int isType (char * str);

int isWhiteSpace (char * str);

int isComment (char *str);

List *addVar (List *list, Line *vars);

char *methodParameters (Line * line);

void changeFuncNames (Line *list, char * className, char *oldName, char *newName, char *funcParam);

int checkStructVar (List *methodList, List * varList, char *structName);

List * addParameters (List * methodList, Line *parameters);

List *makeConst (List *methodList, char *className);

#endif
