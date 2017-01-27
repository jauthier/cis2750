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
    if  (isEqual(vars, "struct")==1) {
        isStruct = 1;
        list = addBack(list, createLine(vars->data));
        vars = vars->next;
        vars = whileWSC(vars);/*find the name of the struct*/
    }
    Line *type = createLine(vars->data);
    vars = vars->next;
    while (isEqual(vars,";")!=1){
        if (isEqual(vars,",")==1){
            if (isStruct == 1){
                list = addBack(list, createLine("struct"));
                
            }
            list = addBack(list,createLine(type->data));
        } else if (isWhiteSpace(vars->data)==1||isComment(vars->data)==1){
            continue;
        } else {
            list = addBack(list, createLine(vars->data));
        } 
        vars = vars->next;
    }
    return list;
}

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

void changeFuncNames (Line *list, char * className, char *oldName, char *newName){
    /*search for the class name, thus we will get any names of the objects that were made*/

    Line *hold = list;
    while (hold != NULL){
        if (isEqual(hold,className)==1){
            do {
                hold = hold->next;
            } while(isWhiteSpace(hold->data)==1||isComment(hold->data)==1);
            Line * temp = hold->next;
            while (temp != NULL){
                if (isEqual(temp,hold->data)==1){
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
            if (isEqual(holdMethod,holdVars->data)){
                char *newVar = malloc(sizeof(char)*(strlen(structVarName)+strlen(holdMethod->data)+3));
                strcpy(newVar,holdMethod->data);
                strcat(newVar,"->");
                strcat(newVar,structVarName);
                check = 1;
            }
            holdMethod = holdMethod->next;
        }
        holdVars = holdVars->next;
    }
    if (check == 1){
        char * param = malloc(sizeof(char)*(strlen(structName)+strlen(structVarName)+10));
        strcpy(param,structVarName);
        strcat(param," *");
        strcat(param,structName);
        strcat(param,"struct ");
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
    char * name = malloc(sizeof(char)*(strlen(className)+strlen("constructor")+strlen("(struct ")));
    strcpy(name, "(struct ");
    strcat(name,className);
    strcat(name, "constructor");
    Line * funcName = createLine(name);
    conList = addBack(conList,funcName);
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
        strcpy(line1, "\n");
        strcat(line1,hold->data);
        strcat(line1, " = ");
        strcat(line1,hold->data);
        strcat(line1, "    sVar->");
        Line *line2 = createLine(line1);
        conList = addBack(conList,line2);
        hold = hold->next;
    }
    char *last = malloc(sizeof(char)*strlen("}\n"));
    Line *last2 = createLine(last);
    conList = addBack(conList,last2);
    return conList;
}
