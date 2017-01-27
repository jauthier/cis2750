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
                List *structHead = classToStruct(current,end);
                Line *structLast = getLast(structHead);

            } else {

            }
        } else {
            printf("not a class\n");
        }
        start = current; // keep trake of the last
        current = current->next; // get the next
    }
}

List *classToStruct (Line *class, Line *restOfList){  ///make a list to return
    List *funcToAdd = createList();
    List *variableList = createList(); //list of the variables
    List *methodNameList = createLine(); //list of method names
    Line *hold = class->next;
    char className[20];
    /*change class to struct*/
    char *structure = malloc(sizeof(char)*strlen("struct"));
    strcpy(structure,"struct");
    class = changeData (class, structure);
    /*get the name of the class*/
    while (isComment(hold->data)==1||isWhiteSpace(hold->data)==1){
        hold = hold->next;
    }
    strcpy(className,hold->data);
    Line *last = hold;
    hold = hold->next;
    /*go through the list, check each line*/ 
    while (hold != NULL) {
        if (isWhiteSpace(hold->data) == 1 ||isComment(hold->data) == 1){ // whitespace or comment
            last = hold;
            hold = hold->next;
        } else if (isType(hold->data)==1||isEqual(hold,"struct")==1){ //a variable or a method
            Line * temp = hold;
            Line * methodName;
            Line *afterType;
            /*get to the line after the name*/
            if (isEqual(temp,"struct")==1){
                temp = temp->next;
                temp = whileWSC(temp); // will end up at the name of the struct
            }
            afterType = temp;
            temp = temp->next;
            temp = whileWSC(temp); // be *, { or the method/variable name
            if (isEqual(temp,"*")==1){
                afterType = temp;
                temp = temp->next;
                temp = whileWSC(temp);
            }
            if (isEqual(temp,"{")!=1){
                methodName = temp;
                temp = temp->next;
                temp = whileWSC(temp);
            }
            if (isEqual(temp,";")==1 ||isEqual(temp,",")==1){ // variable
                variableList = addVar(variableList,hold); 
                while (isEqual(temp,";")!=1) {
                    temp = temp->next;
                }
                last = temp;
                hold = temp->next;          
            } else if (isEqual(temp,"{")==1){ //stuct declaration
                // move the struct outside of the class
                while (isEqual(temp,"}")!=1){
                    temp = temp->next;
                }
                temp = temp->next;
                temp = whileWSC(temp);
                if (isEqual(temp,";")==1){
                    temp = temp->next;
                }
                Line *afterStruct = temp->next;
                temp->next = NULL;
                last->next = afterStruct;
                funcToAdd = addFront(funcToAdd,hold);
                hold = afterStruct; 
            } else { // method
                List *paramList = createList();
                /*change the name of the method*/
                char *funcParam = methodParameters(temp); // get the letters to add to the name
                char * functionName = malloc(sizeof(char) *(strlen(className)+strlen(methodName->data)+strlen(funcParam)));
                strcpy(functionName,funcParam);
                strcat(functionName,methodName->data);
                strcat(functionName,className);
                methodName = changeData (methodName,functionName);
                free(funcParam);
                /*save the maethod name to the list*/
                Line *newMethod = createLine(functionName);
                methodNameList = addBack(methodNameList,newMethod); 
                /*search for any other uses of the function to change the names*/
                changeFuncNames(restOfList, className, methodName->data, functionName);

                /*get the parameters of the method*/
                while (isEqual(temp,"(")!=1){
                    temp = temp->next;
                }
                paramList = addBack(paramList,createLine("("));
                while (isEqual(temp,")")){
                    Line * toAdd = createLine(temp->data);
                    paramList = addBack(paramList,toAdd);
                }
                paramList = addBack(paramList, createLine(")"))

                /*find the end of the method so the whole thing can be removed from the struct*/
                while (isEqual(temp,"}") != 0){
                    temp = temp->next;
                }
                Line *checkEnd = temp->next;
                checkEnd = whileWSC(checkEnd);
                if (isEqual(checkEnd,";")==1)
                    temp = checkEnd;
                /*save the Line after the }/; so it can be added back on after the function pointer is added*/
                Line * afterFunct = temp->next;
                temp->next = NULL;

                /*add the type to the method list, while also keeping it in the struct*/
                List *methodList = createList();
                Line *method = createLine(hold->data);
                methodList = addBack(methodList,method); // add the type
                hold = hold->next;
                while (hold != methodName) { 
                    Line * newLine = createLine(hold->data);
                    methodList = addBack(methodList,newLine);
                    hold = hold->next;
                }
                /*add the rest of the of the method*/
                hold = hold->next;
                methodList = addBack(methodList,hold);

                /*check if the method uses any struct variables*/
                int checkSV = checkStructVar(methodList,variableList,className);
                /*make the function ptr*/
                if (checkSV == 1) { // parameters
                    char * param = malloc(sizeof(char)*(strlen(structName)+strlen(structVarName)+10));
                    strcpy(param,structVarName);
                    strcat(param," *");
                    strcat(param,structName);
                    strcat(param,"struct ");
                    Line * parameters = createLine(param);
                    paramList = addParameters(paramList,parameters)
                }
                char *fnPtrName = malloc(sizeof(char)*(strlen(functionName)+4));
                strcpy (fnPtrName,")");
                strcat(fnPtrName,functionName);
                strcat(fnPtrName,"(*");
                Line *fnPtr = createLine(fnPtrName); //pointer bit
                afterType->next = fnPtr; // add the pointer bit to the struct
                fnPtr->next = paramList->head; // add the parameters to the struct
                while (fnPtr->next != NULL){
                    fnPtr = fnPtr->next;
                }
                fnPtr->next = afterFunct; // add the rest of the struct back on
                last = fnPtr;
                hold = afterFunct;
                // send the method list off, and add it to the function pointer

            }
        } else { // check for structs inside the class


            printf("other\n");
            hold = hold->next;
        }

    }
    return class;
}

List * methodToFunction (List *list){

    Line *hold = list->head;
    while (hold != NULL){
        if (isEqual(hold,"class")==1){
            char * name = malloc(sizeof(char)*strlen("struct"));
            hold = changeData(hold, name);
        }
        hold = hold->next;
    }
    return list;
}
