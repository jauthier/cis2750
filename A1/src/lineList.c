/*
* Jessica Authier
* 2017/01/25
*/
#include "lineList.h"

List * createList (){
    List *list = malloc(sizeof(List));
    list->head = NULL;
    return list;
}

void destroyList (List * toDestroy) {
    
    Line * head = toDestroy->head;
    while (head != NULL){ /* While the list isn't empty */
        Line * temp = head; /* hold the Line at the front of the list */
        head = head->next; /* set the next Element to be the first */
        destroyLine(temp); /* remove the previous first Element */
    }
    free(toDestroy);
}

Line *createLine (char * data){
    Line *newLine = malloc(sizeof(Line));
    newLine->data = data;
    newLine->next = NULL;
    return newLine;
}

void destroyLine (Line * toDestroy){
    free(toDestroy->data);
    free(toDestroy);
}

List * addFront (List * list, Line * toAdd){
    
    if (list->head == NULL){ /* if the list is empty */
        list->head = toAdd;
    } else {
        Line * hold = list->head; /* hold the first Line */
        toAdd->next = hold; /* set the held Line as the Line that follows the Line being added to the front */
        list->head = toAdd; /* set the new Line to be the first Line */
    }
    return list;
}

List * addBack (List * list, Line * toAdd){
    Line * temp = list->head; /* get the first Line of the list */
    
    if (temp == NULL){ /* if the list is empty */
		list->head = toAdd;
    } else { 
        while(temp->next != NULL){ /* while it is not the last Line of the list */	
            temp = temp->next; /* iterate through the list until it reaches the end */
        }
        temp->next = toAdd; /* add the Line to the end of the list */
    } 
    return list;
}

Line * removeFront (List * list){
    
    if (list->head == NULL){ /* if the list is empty then there is not Lines to remove */
        printf("There are no Lines to remove.\n");
        return NULL;
    } else {
        Line * hold = list->head; /* hold the first Line */
        list->head = hold->next; /* set the head to the second Line */
        return hold;
    }
}

Line * removeBack (List * list){
    
    Line * temp = list->head;
    if (temp == NULL){ /* if the list is empty */
        printf("There are no Lines to remove.\n");
    } else if (temp->next == NULL) { /* there is only one Line in the list */
        list->head = NULL; /* remove the one Line */
    } else {
        while(temp->next->next != NULL){ /* while temp is not the second last Line of the list */
            temp = temp->next; /* iterate through the list until it reaches the end */
        }
        Line * hold = temp->next; /* hold the last Lineof the List */
        temp->next = NULL; /* remove the last Line of the List */
        temp = hold;
    }
    return temp;
}

int isEqual (Line *line, char *str){
    if (strcmp(line->data,str)==0)
        return 1;
    else
        return 0;
}

Line * changeData (Line * line, char *newData){
    char * oldData = line->data;
    line->data = newData;
    free(oldData);
    return line;
}

Line * getLast (List * list){
    Line *hold = list->head;
    while (hold->next != NULL){
        hold = hold->next;
    }
    return hold;
}

void printList (List *list){
    Line *hold = list->head;
    while (hold != NULL){
        printf("%s", hold->data);
        hold = hold->next;
    }
}
