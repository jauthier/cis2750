/*
	2_3.c
	Jessica Authier
	0849720
	2017/02/13
*/

#include "2_3.h"

int orientation (Point *p, Point *q, Point *r){
    int val = (q->y - p->y)*(r->x - q->x)-(q->x - p->x)*(r->y - q->y);
    if (val == 0)
        return 0;
    if (val < 0)
        return 2;
    else
        return 1;
}

Point ** convexHull (Point **points, int n, Point **hull){

    int i = 1;
    Point *left = points[0];
    for (i=1;i<n;i++){
        if (left->x > points[i]->x)
            left = points[i];
    }
    Point *hold = left;
    int j = 0;
    do {
        hull[j] = hold;
        int p = 0;
        i = 1;
        for (i=1;i<n;i++){
            if (orientation(hold,points[i],points[p]) == 2)
                p = i;
            hold = points[p];
            j++;
        }
    } while (hold != left);
    return hull;
}

/*
Point ** convexHullDaC (Points ** points, int n){
    if (n <= 3)
        return points;

    int i = 1;
    Point *left = points[0];
    for (i=1;i<n;i++){
        if (left->x > points[i]->x)
            left = points[i];
    }
    i = 1;
    Point *right = points[0];
    for (i=1;i<n;i++){
        if (right->x > points[i]->x)
            right = points[i];
    }

    Point *l[n];
    Point *r[n];

    l[0] = left;
    r[0] = right;

    float mid = right->x - (right->x - left->x)/2
    i = 0;
    int j=1, k=1;
    for (i=0;i<n;++i){
        if (points[i]->x < mid){
            l[j] = points[i];
            j++;
        } else {
            r[k] = points[i];
            k++;
        }
    }
    l = convexHullDaC(l,j+1);
    r = convexHullDaC(r,k+1)
    hull = merge(l, r, j+1, k+1);

}

Points ** merge (Points ** l, Points ** r, int lenL, int lenR){

}
*/
