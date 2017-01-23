/*
    Author: Jessica Authier
    2016\05\27
*/

#include "linkedlist.h"

List * createList(){

    List *list;
    list = malloc(sizeof(List));
    list->head = NULL;
    return list;
}

void destroyList(List * toDestroy) {
    
    Element * head = toDestroy->head;
    while (head != NULL){ /* While the list isn't empty */
        Element * temp = head; /* hold the Element at the front of the list */
        head = head->next; /* set the next Element to be the first */
        free(temp); /* remove the previous first Element */
    }
    free(toDestroy);
}

Element * createElement(void * contents){
    
    Element * newElement;
    newElement = malloc(sizeof(Element));
    newElement->elementPtr = contents;
    newElement->next = NULL;
    return newElement;
}

void destroyElement(Element * toDestroy){
    
    free(toDestroy);
}

List * addFront(List * list, Element * toAdd){
    
    if (list->head == NULL){ /* if the list is empty */
        list->head = toAdd;
    } else {
        Element * hold = list->head; /* hold the first Element */
        toAdd->next = hold; /* set the held Element as the Element that follows the Element being added to the front */
        list->head = toAdd; /* set the new Element to be the first Element */
    }
    return list;
}

List * addBack(List * list, Element * toAdd){
    
    if (list->head == NULL){ /* if the list is empty */
        list->head = toAdd;
    } else {
        Element * temp = list->head; /* get the first Element of the list */
        while(temp->next != NULL){ /* while it is not the last Element of the list */
            temp = temp->next; /* iterate through the list until it reaches the end */
        }
        temp->next = toAdd; /* add the Element to the end of the list */
    } 
    return list;
}

Element * removeFront(List * list){
    
    if (list->head == NULL){ /* if the list is empty then there is not Elements to remove */
        printf("There are no elements to remove.\n");
        return NULL;
    } else {
        Element * hold = list->head; /* hold the first Element */
        list->head = hold->next; /* set the head to the second Element */
        return hold;
    }
}

Element * removeBack(List * list){
    
    Element * temp = list->head;
    if (temp == NULL){ /* if the list is empty */
        printf("There are no elements to remove.\n");
    } else if (temp->next == NULL) { /* there is only one Element in the list */
        list->head = NULL; /* remove the one Element */
    } else {
        while(temp->next->next != NULL){ /* while temp is not the second last Element of the list */
            temp = temp->next; /* iterate through the list until it reaches the end */
        }
        Element * hold = temp->next; /* hold the last Elementof the List */
        temp->next = NULL; /* remove the last Element of the List */
        temp = hold;
    }
    return temp;
}

Element * getFront(List * list){
    
    return list->head;
}

int getLength(List * list){
    
    int count = 0;
    Element * temp = list->head;
    while (temp != NULL){
        count ++;
        temp = temp->next;
    }
    return count;
}
