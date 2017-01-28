/*
	parse.c
	Jessica Authier
	2017/01/24
*/

#include "parse.h"

List *parseFile (FILE *fp) {

	char c = fgetc(fp);
	char last = ' ';
	char *fileName = "docs/parsedProgram.txt";
	FILE *fWrite = fopen(fileName,"w");

	while (!feof(fp)) {

		int check = sort(c);
		int checkLast = sort(last);
		
		if (c == '"'){ /*deals with strings*/
			fprintf(fWrite,"\n%c", c); /*print first quotation mark*/
			c = fgetc(fp);
			/*print the letters in between*/
			while (c != '"' || last == '\\') { /*if c is " and last is not / then stop, we have reached the end of the string*/
				fprintf(fWrite,"%c", c);
				c = fgetc(fp);
			}
			fprintf(fWrite,"%c\n", c);
			last = c;
			c = fgetc(fp);
		} else if (c == '/') {
			last = c;
			c = fgetc(fp); /*check the next*/
			if (c == '/') { /* single line comment*/
				fprintf(fWrite, "%c",last);
				while (c != '\n') { /*print out the line*/
					fprintf(fWrite, "%c", c);
					last = c;
					c = fgetc(fp);
				}
			} else if (c == '*') { /*multi line comment*/
				fprintf(fWrite, "%c%c", last, c);
				c = fgetc(fp);
				fprintf(fWrite, "%c", c);
				last = c;
				c = fgetc(fp);
				while (last != '*' || c != '/'){
					fprintf(fWrite, "%c", c);
					last = c;
					c = fgetc(fp);
				}
				fprintf(fWrite, "%c", c);
				last = c;
				c = fgetc(fp);
			} else {
				fprintf(fWrite, "%c", last);
			}

		} else if (check == 3 && checkLast == 3) /* current is 'regular' character, last is 'regular' character*/
			fprintf(fWrite,"%c", c);
		else if (check == 1 && checkLast == 1) /* current is whitespace, last is whitespace -- store the whitespace*/
			fprintf(fWrite,"%c", c);
		else
			fprintf(fWrite,"\n%c", c);		

		last = c;
		c = fgetc(fp);
	}
	
	fclose(fWrite);
	List *list = fileToList(fileName);
	return list;
}

int sort (char c) {

if (c==' '||c=='\t'||c=='\n'||c=='\r') 
	return 1;
else if (c==','||c==';'||c=='('||c==')'||c=='{'||c=='}'||c=='+'||c=='*'||c=='=')
	return 2;
else 
	return 3;
}

List *fileToList (char *fileName){

	FILE *fp = fopen(fileName,"r");

	char hold[200];
	List *tokenList = createList();

	while (fgets(hold,200,fp) != NULL){
		int len = strlen(hold);

		if (hold[0]=='\n')
			printf("only and new line \n");

		/*if (hold[len-1]=='\n'&&strcmp(hold,"\n")!=1){

			hold[len-1]='\0';
		}*/

		char * token = malloc(sizeof(char)*len);
		strcpy(token, hold);
		Line * toAdd = createLine(token);
		tokenList = addBack(tokenList, toAdd);
	}
	fclose(fp);
	return tokenList;
}
