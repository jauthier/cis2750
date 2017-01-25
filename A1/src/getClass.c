#include "getClass.h"

void translate(List *tokenList){
	printf("IN translate\n");
    Line *start = NULL; // this will hold the Line that is before the Line of interest
    Line *current = tokenList->head; // the Line being looked at by while loop
    while (current != NULL){ // while not at then end of the list
        printf("%s: %d\n", current->data,isEqual(current,"class"));
        if (isEqual(current,"class") == 1){
            printf("IN CLASS\n");

            Line *hold = current->next;

            /*pass through the whitespace and the name of the class*/
            int checkWS = isWhiteSpace(hold->data);
            int checkC = isComment(hold->data);
            while (checkWS == 1 || checkC == 1){
                hold = hold->next;
                checkWS = isWhiteSpace(hold->data);
                checkC = isComment(hold->data);
            }
            do {
                hold = hold->next;
                checkWS = isWhiteSpace(hold->data);
                checkC = isComment(hold->data);
            } while (checkWS == 1 || checkC == 1);

            /*determine if this is a class or an instance of a class*/
            if (isEqual(hold, "{") == 1){
                hold = hold->next;
                int openBraces = 0;
                while (strcmp(hold->data,"}") != 0 && openBraces != 0){ // if hold is not a } and openBraces is not 0 then keep looking
                    if (strcmp(hold->data,"{") == 0)
                        openBraces++; // record if there is an open brace
                    else if (strcmp(hold->data,"}") == 0)
                        openBraces--;
                    hold = hold->next;
                }
                // once the close brace is found
                Line *end = hold->next; // save the Line that follows
                hold->next = NULL;
                printf("goind to make a struct\n");
                // send the List to a function that turns the class into a method
                Line *structHead = classToStruct(current,end);  
            } else {

            }
        } else {
            printf("not a class\n");
        }
        start = current; // keep trake of the last
        current = current->next; // get the next
    }
}

Line *classToStruct(Line *class, Line *restOfList){
    printf("in class to struct\n");
    List *funcToAdd = createList();
    List *variableNames = createList();
    Line *hold = class->next;
    int checkC, checkWS, checkT;
    char *className;
    /*change class to struct*/
    char *structure = malloc(sizeof(char)*strlen("struct"));
    strcpy(structure,"struct");
    class = changeData (class, structure);


    printf("after name change\n");

    /*get the name of the class*/
    checkWS = isWhiteSpace(hold->data); 
    checkC = isComment(hold->data);
    while (checkC==1||checkWS==1){
        hold = hold->next;
        checkWS = isWhiteSpace(hold->data); 
        checkC = isComment(hold->data);
    }
    strcpy(className,hold->data);
    /*go through the list, check each line*/ 
    while (hold != NULL) {
        
        if (isWhiteSpace(hold->data) == 1 ||isComment(hold->data) == 1){ // whitespace or comment
            hold = hold->next;
        } else if (isEqual(hold,"*") == 1||isType(hold->data)==1){ //a variable or a method
            Line *last; // this will hold the Line before the ; or method name
            Line * temp = hold;
            do {
                last = temp;
                temp = temp->next;
                checkWS = isWhiteSpace(temp->data);
                checkC = isComment(temp->data);
                checkT = isType(temp->data);
            } while (checkWS == 1||checkC == 1||checkT);




            if (isEqual(temp,";")==1 ||isEqual(temp,",")==1){ // variable
                while (isEqual(temp,";")!=1) {
                    temp = temp->next;
                }
                temp = temp->next;
            } else { // method
                /*change the name of the method*/
                char *oldName = temp->data;
                char *funcParam = methodParameters(temp);
                char * functionName = malloc(sizeof(char) *(strlen(className)+strlen(temp->data)+strlen(funcParam)));
                strcpy(functionName,funcParam);
                strcat(functionName,className);
                strcat(functionName,temp->data);
                temp = changeData (temp,functionName);
                free(funcParam);
                /*search for any other uses of the function to change the names*/
                changeFuncNames(temp, className, oldName, functionName);
                /*find the end of the method so the whole thing can be removed from the struct*/
                while (isEqual(temp,"}") != 0){
                    temp = temp->next;
                }
                /*save the Line after the } so it can be added back on after the function pointer is added*/
                Line * afterFunct = temp->next;
                temp->next = NULL;

                /*add the type to the method list, while also keeping it in the struct*/
                List *methodList = createList();
                Line *method = createLine(hold->data);
                methodList = addBack(methodList,method);
                hold = hold->next;
                while (hold != last) {
                    Line * newLine = createLine(hold->data);
                    methodList = addBack(methodList,newLine);
                    hold = hold->next;
                }
                Line *newL = createLine(hold->data);
                methodList = addBack(methodList,newL);

                //add the rest of the of the method
                hold = hold->next;
                methodList = addBack(methodList,hold);

                //check if the method uses any struct variables



                // add a function pointer and put the rest of the class after
                char *tempName = ")();";
                strcat(tempName,functionName);
                strcat(tempName,"(*");
                char * fnPtrName = malloc(sizeof(char)*strlen(tempName));

                Line *fnPtr = createLine(fnPtrName);
                last->next = fnPtr;
                fnPtr->next = afterFunct;

                // send the method list off

            }



        } else { // check for structs inside the class
            printf("other\n");
            hold = hold->next;
        }

    }
    return class;
}

/*takes in the list of tokens, looks for any parameters and returns a string with a character 
for each parameter. If there is an int i is returned, if there is an int and a char ic is returned ...*/
char *methodParameters (Line * line){
    int i = 0;
    line = line->next;
    char hold[10];
    while (isEqual(line, ")") != 1) {
        if (isType(line->data)==1){
            hold[i] = line->data[0];
            i++;
        }
        line = line->next;
    }
    char *toAdd = malloc(sizeof(char)*strlen(hold));
    return toAdd;
}

void changeFuncNames(Line *list, char * className, char *oldName, char *newName){
    //search for the class name, thus we will get any names of the objects that were made

    Line *hold = list;
    while (hold != NULL){
        if (isEqual(hold,className)==1){
            do {
                hold = hold->next;
            } while(isWhiteSpace(hold->data)==1||isComment(hold->data)==1);
            // should be the name of a class variable
            //seach for the name of this var
            Line * temp = hold->next;
            while (temp != NULL){
                if (isEqual(temp,hold->data)==1){ // found a variable
                    if (isEqual(temp->next, ".")==1&&isEqual(temp->next->next,oldName)==1){
                        temp = temp->next->next;
                        char *name = malloc(sizeof(char)*strlen(newName));
                        strcpy(name,newName);
                        temp = changeData(temp,name);
                    }
                }
                temp = temp->next;
            }
        }
        hold = hold->next;
    }
}

int isType(char * str){
    if (strcmp(str,"int")==0||strcmp(str,"char")==0||strcmp(str,"short")==0
        ||strcmp(str,"long")==0||strcmp(str,"double")==0||strcmp(str,"float")==0
        ||strcmp(str,"void")==0)
        return 1;
    else 
        return 0;
}

int isWhiteSpace(char * str) {
	int len = strlen(str);
	int i = 0;
	for (i=0;i<len;i++) {
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r'){
			return 0;
		}
	}
	return 1;
}

int isComment(char *str) {
    if (strlen(str) < 3)
        return 0;
    else if (str[0] == '/' && (str[1] == '/' || str[1] == '*')) // if // or /*
        return 1;
    else
        return 0;
}
