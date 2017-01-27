/*
* lineList.h
* Jessica Authier
* 2017/01/25
*/

#ifndef LINELIST_H
#define LINELIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Line {
    char * data;
    struct Line * next;
} Line;

typedef struct List {
    Line * head;
} List;


List * createList ();

void destroyList (List * toDestroy) ;

Line *createLine (char * data);

void destroyLine (Line * toDestroy);

List * addFront (List * list, Line * toAdd);

List * addBack (List * list, Line * toAdd);

Line * removeFront (List * list);

Line * removeBack (List * list);

int isEqual (Line *line, char *str);

Line * changeData (Line * line, char *newData);

Line * getLast(List * list);

void printList (List *list);

#endif
