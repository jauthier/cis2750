/*
	2_3.h
	Jessica Authier
	0849720
	2017/02/13
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    float x, y;
} Point;

int orientation (Point *p, Point *q, Point *r);
Point ** convexHull (Point *points[], int n);
//Point ** convexHullDaC (Points ** points, int n);
//Points ** merge (Points ** l, Points ** r, int lenL, int lenR);
