/*
* listFunctions.c
* Jessica Auhtier
* 2017/01/26
*/

#include "listFunctions.h"

Line * whileWSC (Line *temp){
    while (isWhiteSpace(temp->data) == 1||isComment(temp->data) == 1){
        temp = temp->next;
    }
    return temp;
}

int isType (char * str){
    if (strcmp(str,"int")==0||strcmp(str,"char")==0||strcmp(str,"short")==0
        ||strcmp(str,"long")==0||strcmp(str,"double")==0||strcmp(str,"float")==0
        ||strcmp(str,"void")==0)
        return 1;
    else 
        return 0;
}

int isWhiteSpace (char * str) {
    int len = strlen(str);
    int i = 0;
    for (i=0;i<len;i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r'){
            return 0;
        }
    }
    return 1;
}

int isComment (char *str) {
    if (strlen(str) < 3)
        return 0;
    else if (str[0] == '/' && (str[1] == '/' || str[1] == '*'))
        return 1;
    else
        return 0;
}

List *addVar (List *list, Line *vars){
    int isStruct = 0;
    if  (isEqual(vars, "struct")==1){
        isStruct = 1;
        list = addBack(list, createLine(vars->data));
        vars = vars->next;
		vars = whileWSC(vars);/*find the name of the struct*/    
    }
    
	Line *type = createLine(vars->data);
	list = addBack(list,type);
    vars = vars->next;    
    while (isEqual(vars,";")!=1){
        if (isEqual(vars,",")==1){
            if (isStruct == 1){
                list = addBack(list, createLine("struct"));
            }
            list = addBack(list,createLine(type->data));
			vars = vars->next;
        } else if (isWhiteSpace(vars->data)==1||isComment(vars->data)==1){
            vars = vars->next;
        } else {
            Line * newLine = createLine(vars->data);
            list = addBack(list, newLine);
			vars = vars->next;
        }
    }
    return list;
}

char *methodParameters (Line * line){
    int i = 0;
    line = line->next;
    char hold[50];
    while (isEqual(line, ")") != 1) {
        if (isType(line->data)==1){
            hold[i] = line->data[0];
            i++;
        }
        line = line->next;
    }
    hold[i] = '\0';
    char *toAdd = malloc(sizeof(char)*(int)strlen(hold));
    strcpy(toAdd,hold);
    return toAdd;
}

void changeFuncNames (Line *list, char * className, char *oldName, char *newName, char *funcParam,int check){
    /*search for the class name, thus we will get any names of the objects that were made*/
    Line *hold = list;
    Line *lastType;
    while (hold != NULL){
        if (isEqual(hold,className)==1){
            do {
                hold = hold->next;
            } while(isWhiteSpace(hold->data)==1||isComment(hold->data)==1);
            Line * temp = hold->next;
            while (temp != NULL){
                if (isType(temp->data)==1){
                    lastType = temp;
                }
                if (isEqual(temp,hold->data)==1){
                    Line *varName = createLine(hold->data);
					temp = temp->next;
                    temp = whileWSC(temp);
                    if (isEqual(temp, ".")==1&&isEqual(temp->next,oldName)==1){
                        temp = temp->next;/*check the parameters*/
                        Line * nameHold = temp;
                        temp = temp->next;
                        temp = whileWSC(temp);
                        Line *paramStart = temp;
                        int check = 0;
                        int len = strlen(funcParam);
                        while (isEqual(temp,")")!=1){
							
							if (isWhiteSpace(temp->data)!=1&&isEqual(temp,",")!=1&&isEqual(temp,"(")!=1){
								check++;
							}
							temp = temp->next;
						}
                        if (check == len){
							char *name = malloc(sizeof(char)*strlen(newName));
							strcpy(name, newName);
							nameHold = changeData(nameHold,name);
                            printf("check: %d",check);
                            if (check == 1){
                                List * paramList = createList();
                                paramList->head = paramStart;
                                List * toAdd = createList();

                                if (isPtr(lastType)==0){
                                    char * and = malloc(sizeof(char)*strlen("&"));
                                    strcpy(and,"&");
                                    toAdd = addBack(toAdd,createLine(and));
                                }
                                toAdd = addBack(toAdd,createLine(varName->data));
                                paramList = addParameters(paramList, toAdd->head);
                            }
						}
                    }
                }
                temp = temp->next;
            }
        }
        hold = hold->next;
    }
}

int isPtr(Line * type){
    type = type->next;
    type = whileWSC(type);
    if (isEqual(type,"*")==1)
        return 1;
    return 0;
}

int checkStructVar (List *methodList, List * varList, char *structName){
    Line *holdVars = varList->head;
    int check = 0;
    char structVarName[10];
    strcpy(structVarName,"sVar");
    while (holdVars != NULL){
        if (isEqual(holdVars,"struct")==1)
            holdVars = holdVars->next;
        holdVars = holdVars->next;
        if (isEqual(holdVars,"*")==1)
            holdVars = holdVars->next;

        Line * holdMethod = methodList->head;
        while (holdMethod != NULL){
            if (strcmp(holdMethod->data,holdVars->data)==0){
                char *newVar = malloc(sizeof(char)*(strlen(structVarName)+strlen(holdMethod->data)+3));
                strcpy(newVar,structVarName);
                strcat(newVar,"->");
                strcat(newVar,holdMethod->data);
                holdMethod = changeData(holdMethod,newVar);
                check = 1;
            }
            holdMethod = holdMethod->next;
        }
        holdVars = holdVars->next;
    }
    if (check == 1){
        char * param = malloc(sizeof(char)*(strlen(structName)+strlen(structVarName)+10));
        strcpy(param,"struct ");
        strcat(param,structName);
        strcat(param," *");
        strcat(param,structVarName);
        Line * parameters = createLine(param);
        methodList = addParameters(methodList, parameters);
    }
    return check;
}    

List * addParameters (List * methodList, Line *parameters){
    Line *hold = methodList->head;
    while (isEqual(hold,"(")!=1){
        hold = hold->next;
    }
    Line * holdParam = hold->next;
    Line * temp = hold->next;
    hold->next = parameters;
    while (hold->next != NULL){ /*find the end of the parameter that was added*/
        hold = hold->next;
    }
    while (isComment(temp->data)==1||isWhiteSpace(temp->data)==1){
        temp = temp->next;
    }
    if (isEqual(temp,")")!=1){ /* other parameters so add a comma*/
        Line *comma = createLine(", ");
        hold->next = comma;
        hold = hold->next;
    }
    hold->next = holdParam;
    return methodList;
}

List *makeConst (List *methodList, char *className){
    List * conList = createList();
    char *type = malloc(sizeof(char)*strlen("void "));
    strcpy(type,"void ");
    Line *funcType = createLine(type);
    conList = addBack(conList,funcType);
    char * name = malloc(sizeof(char)*(strlen(className)+strlen("constructor")));
    strcpy(name,className);
    strcat(name, "constructor");
    Line * funcName = createLine(name);
    conList = addBack(conList,funcName);
    char *param = malloc(sizeof(char)*strlen("(struct "));
    strcpy(param,"(struct ");
    Line *paramLine = createLine(param);
    conList = addBack(conList,paramLine);
    char *cName = malloc(sizeof(char)*strlen(className));
    strcpy(cName,className);
    Line *classN = createLine(cName);
    conList = addBack(conList,classN);
    char *end = malloc(sizeof(char)*strlen(" *sVar){"));
    strcpy(end," *sVar){\n");
    Line *end2 = createLine(end);
    conList = addBack(conList,end2);

    Line *hold = methodList->head;
    while (hold != NULL){
        char *line1 = malloc(sizeof(char)*(strlen("    sVar->")+(strlen(hold->data)*2)+5));
        strcpy(line1, "    sVar->");
        strcat(line1,hold->data);
        strcat(line1, " = ");
        strcat(line1,hold->data);
        strcat(line1, ";\n");
        Line *line2 = createLine(line1);
        conList = addBack(conList,line2);
        hold = hold->next;
    }
    char *last = malloc(sizeof(char)*strlen("}\n\n"));
    strcpy(last,"}\n\n");
    Line *last2 = createLine(last);
    conList = addBack(conList,last2);
    return conList;
}
