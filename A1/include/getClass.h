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
#include "lineList.h"
#include "listFunctions.h"

void translate (List *tokenList);

List *classToStruct (Line *class, Line *restOfList);

List * methodToFunction (List *list);


#endif
