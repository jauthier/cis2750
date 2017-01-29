#include "getClass.h"

void translate(List *tokenList, char *fileName){
    Line *current = tokenList->head; /* the Line being looked at by while loop*/
    while (current != NULL){ /* while not at then end of the list*/
        if (isEqual(current,"class") == 1){

            Line *hold = current->next;

            /*pass through the whitespace and the name of the class*/
            hold = whileWSC(hold);
            hold = hold->next;
            hold = whileWSC(hold);

            /*determine if this is a class or an instance of a class*/
            if (isEqual(hold, "{") == 1){ /*class declaration*/
                hold = hold->next;
                int openBraces = 0;
                
                while (isEqual(hold,"}") != 1 || openBraces != 0){ /* if hold is not a } and openBraces is not 0 then keep looking*/
                    if (isEqual(hold,"{") == 1)
                        openBraces++; /* record if there is an open brace*/
                    else if (isEqual(hold,"}") == 1)
                        openBraces--;
                    hold = hold->next;
                }
                /* once the close brace is found*/
                Line *end = hold->next; /* save the Line that follows*/
                hold->next = NULL;
                /* send the List to a function that turns the class into a method*/
                List *list = createList();
                list->head = current;
                
                List *structHead = classToStruct(current,end);
                Line *structLast = getLast(structHead);
                structLast->next = end;
                current = structLast;
            } else { /*class variable*/
                char * newName = malloc(sizeof(char)*strlen("struct"));
                strcpy(newName,"struct");
                current = changeData(current,newName);
                while (isEqual(hold,";")==1){
                    if (isEqual(hold, "class")==1){
                        char * newStruct = malloc(sizeof(char)*strlen("struct"));
                        strcpy(newStruct,"struct");
                        hold = changeData(hold,newStruct);
                    }
                    hold = hold->next;
                }
            }
            current = hold;
        } else if (isType(current->data)==1||isEqual(current,"struct")==1){
            printf("type found\n");
            Line *temp = current;
            if (isEqual(current,"struct")==1){
                temp = temp->next;
                temp = whileWSC(temp); /*will bring us to the name of the struct*/
            }
            temp = temp->next;
            temp = whileWSC(temp);
            if (isEqual(temp,"*")==1){
                temp = temp->next;
                temp = whileWSC(temp);
            }
            temp = temp->next;
            temp = whileWSC(temp);

            if (isEqual(temp,";")==1||isEqual(temp,",")==1){ /*global variable(s)*/
                if (isEqual(temp,",")==1){
                    temp = temp->next;
                    while (isEqual(temp,";")!=1){
                        temp = temp->next;
                    }
                }
                current = temp;
            } else { /*function or function prototype*/
                temp = temp->next;
                while (isEqual(temp,")")!=1){
                    if (isEqual(temp,"class")==1){
                        char *newStr = malloc(sizeof(char)*strlen("struct"));
                        strcpy(newStr,"struct");
                        temp = changeData(temp,newStr);
                    }
                    temp = temp->next;
                }
                temp = temp->next;
                temp = whileWSC(temp);
                if (isEqual(temp,";")==1){ /*prototype*/
                    current = temp;
                } else { /*function*/
                    printf("function\n");
                    Line * ret = translateFunc(temp);
                    current = ret;
                }
            }   
        }
        current = current->next; /* get the next*/
    }

    FILE * fp = fopen(fileName);
    Line *holdToken = tokenList->head;
    while (holdToken != NULL){
        fprintf(fp, "%s\n", holdToken->data);
        holdToken = holdToken->next;
    }
    printList(tokenList);
}

List *classToStruct (Line *class, Line *restOfList){
    List *funcToAdd = createList(); /*list of the functions and structs to add to the end of the struct*/
    List *variableList = createList(); /*list of the variables in the struct*/
    List *methodNameList = createList(); /*list of funtion pointers in the struct*/ 
    
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
        if (isType(hold->data)==1||isEqual(hold,"struct")==1){ /*a variable or a method*/
            Line * temp =  hold;
            Line * methodName;
            Line *type;
            /*get to the line after the name*/
            if (isEqual(temp,"struct")==1){
                temp = temp->next;
                temp = whileWSC(temp); /* will end up at the name of the struct*/
            }
            type = temp;
            temp = temp->next;
            temp = whileWSC(temp); /* be *, { or the method/variable name*/
            if (isEqual(temp,"*")==1){
                type = temp;
                temp = temp->next;
                temp = whileWSC(temp);
            }
            if (isEqual(temp,"{")!=1){
                methodName = temp;
                temp = temp->next;
                temp = whileWSC(temp);
            }

            if (isEqual(temp,";")==1 ||isEqual(temp,",")==1){ /*variable*/                
                variableList = addVar(variableList,hold);
                while (isEqual(temp,";")!=1) {
                    temp = temp->next;
                }
                last = temp;
                hold = temp->next;          
            } else if (isEqual(temp,"{")==1){ /*stuct declaration*/
                /* move the struct outside of the class*/
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
            } else { /* method */
                List *paramList = createList();
                /*change the name of the method*/
                char *funcParam = methodParameters(temp); /*get the letters to add to the name*/
                char * functionName = malloc(sizeof(char) *(strlen(className)+strlen(methodName->data)+strlen(funcParam)));
                strcpy(functionName,funcParam);
                strcat(functionName,methodName->data);
                strcat(functionName,className);
                methodName = changeData (methodName,functionName);
                free(funcParam);
                
                /*save the method name to the list*/
                Line *newMethod = createLine(functionName);
                methodNameList = addBack(methodNameList,newMethod); 
                
                /*search for any other uses of the function to change the names*/
                changeFuncNames(restOfList, className, methodName->data, functionName);

                /*get the parameters of the method*/
                while (isEqual(temp,")")!=1){
                    Line * toAdd = createLine(temp->data);
                    paramList = addBack(paramList,toAdd);
                    temp = temp->next;
                }
                paramList = addBack(paramList, createLine(")"));

                /*find the end of the method so the whole thing can be removed from the struct*/
                while (isEqual(temp,"}") != 1){
                    temp = temp->next;
                }
                Line *checkEnd = temp->next;
                checkEnd = whileWSC(checkEnd);
                if (isEqual(checkEnd,";")==1)
                    temp = checkEnd;
                
                /*save the Line after the }/; so it can be added back on after the function pointer is added*/
                Line * afterFunct = temp->next;
                Line *newLine1 = createLine("\n\n");
                temp->next = newLine1;
                
                /*add the type to the method list, while also keeping it in the struct*/
                List *methodList = createList();
                Line *method = createLine(hold->data);
                methodList = addBack(methodList,method); /* add the type*/
                last = hold;
                hold = hold->next;
                
                
                while (hold != methodName) { 
                    Line * newLine = createLine(hold->data);
                    methodList = addBack(methodList,newLine);
                    last = hold;
                    hold = hold->next;
                }
                
                methodList = addBack(methodList,hold);/*add the rest of the of the method*/
                /*check if the method uses any struct variables*/
                int checkSV = checkStructVar(methodList,variableList,className);
                methodList = methodToFunction(methodList);/*turn the method into a function*/
                                
                /*add the function to the functionlist*/
                funcToAdd = addBack(funcToAdd,methodList->head);
			
                /*make the function ptr*/
                if (checkSV == 1) { /* parameters*/
                    char *new1 = malloc(sizeof(char)*strlen("struct "));
                    strcpy(new1,"struct ");
                    char *new2 = malloc(sizeof(char)*strlen(className));
                    strcpy(new2,className);
                    char *new3 = malloc(sizeof(char)*strlen(" *"));
                    strcpy(new3," *");
                    char *new4 = malloc(sizeof(char)*strlen("sVar"));
                    strcpy(new4,"sVar");
                    Line *line1 = createLine(new1);
                    Line *line2 = createLine(new2);
                    Line *line3 = createLine(new3);
                    Line *line4 = createLine(new4);
                    line1->next = line2;
                    line2->next = line3;
                    line3->next = line4;
                    paramList = addParameters(paramList,line1);
                }
                char *str1 = malloc(sizeof(char)*strlen(" (*"));
                strcpy(str1," (*");
                char *str2 = malloc(sizeof(char)*strlen(functionName));
                strcpy(str2,functionName);
                char *str3 = malloc(sizeof(char)*strlen(")"));
                strcpy(str3,")");
                char *str4 = malloc(sizeof(char)*strlen(";\n"));
                strcpy(str4,";\n");
                Line *line5 = createLine(str1);
                Line *line6 = createLine(str2);
                Line *line7 = createLine(str3);
                Line *line8 = createLine(str4);
                line5->next = line6;
                line6->next = line7;
                line7->next = paramList->head;


                type->next = line5; /* add the pointer bit to the struct*/
                Line *fnPtr = paramList->head; /*add the parameters to the struct*/
                while (fnPtr->next != NULL){
                    fnPtr = fnPtr->next;
                }
                fnPtr->next = line8; /*add the rest of the struct back on*/
                line8->next = afterFunct;
                last->next = line5;                
                hold = afterFunct;
            }
        } else {
            last = hold;
            hold = hold->next;
        }
    }
    /*create a constructor for the struct*/
    List *constructor = createList();
    constructor = makeConst(methodNameList,className);
    funcToAdd = addBack(funcToAdd,constructor->head);
    List *finalList = createList();
    finalList = addBack(finalList,class);
	Line *newLine = createLine("\n\n");
	finalList = addBack(finalList,newLine);
    finalList = addBack(finalList,funcToAdd->head);
    return finalList;
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

Line * translateFunc (Line *start){    
    Line * temp = start->next;
    int openBraces = 0;
    
    while (isEqual(temp,"}")!=1||openBraces!=0){
        if (isEqual(temp,"{")==1){
            openBraces++;
        } else if (isEqual(temp,"}")==1){
            openBraces --;        
        } else {
            if (isEqual(temp,"class")==1) {
                int isPtr = 0;
                char * name = malloc(sizeof(char)*strlen("struct"));
                strcpy(name,"struct");
                temp = changeData(temp,name);
                temp = temp->next;
                temp = whileWSC(temp);
                Line *className = temp;
                temp = temp->next;
                temp = whileWSC(temp);
                if (isEqual(temp,"*")==1){
                    isPtr = 1;
                    temp = temp->next;
                    temp = whileWSC(temp);
                }
                Line * varName = temp;
                while (isEqual(temp,";")!=1){
                    temp = temp->next;
                }
                Line *hold = temp->next;
                char * str1 = malloc(sizeof(char)*(strlen(className->data)+strlen("constructor\n")));
                strcpy(str1,"\n    ");
                strcat(str1,className->data);
                strcat(str1,"constructor");
                temp->next = createLine(str1);
                temp = temp->next;
                if (isPtr==1) {
                    char * str2 = malloc(sizeof(char)*strlen("("));
                    strcpy(str2,"(");
                    temp->next = createLine(str2);
                } else {
                    char * str2 = malloc(sizeof(char)*strlen("(&"));
                    strcpy(str2,"(&");
                    temp->next = createLine(str2);
                }
                temp = temp->next;
                char *str3 = malloc(sizeof(char)*strlen(varName->data));
                strcpy(str3,varName->data);
                temp->next = createLine(str3);
                temp = temp->next;
                char *str4 = malloc(sizeof(char)*strlen(");\n"));
                strcpy(str4,");\n");
                temp->next = createLine(str4);
                temp = temp->next;
                temp->next = hold;
            }
        }
        temp = temp->next;
    }
    printf("at the end\n");
    return temp;
}
