/*
	parse.c
	Jessica Authier
	2017/01/16
*/

#include "parse.h"

void parseFile(FILE *fp) {

	char c = fgetc(fp);
	char last = ' ';
	char *fileName = "parsedProgram.txt";
	FILE *fWrite = fopen(fileName,"w");

	while (!feof(fp)) {

		int check = sort(c);
		int checkLast = sort(last);

		// deals with strings ---- need to deal with quotes in strings
		if (c == '"'){
			// print first quotation mark
			fprintf(fWrite,"%c", c);
			c = fgetc(fp);
			// print the letters in between
			while (c != '"') {
				fprintf(fWrite,"%c", c);
				c =fgetc(fp);
			}
			fprintf(fWrite,"%c\n", c);
			last = c;
			c = fgetc(fp);
		}

		if (check == 3 && checkLast == 3) // current is 'regular' character, last is 'regular' character
			fprintf(fWrite,"%c", c);
		else if (check == 1 && checkLast == 1) // current is whitespace, last is whitespace -- store the whitespace
			fprintf(fWrite,"%c", c);
		else
			fprintf(fWrite,"\n%c", c);		

		last = c;
		c = fgetc(fp);
	}
	
	fclose(fWrite);
	printf("here\n");
	fileToList(fileName);
}

int sort(char c) {

if (c==' '||c=='\t'||c=='\n'||c=='\r') 
	return 1;
else if (c==','||c==';'||c=='('||c==')'||c=='{'||c=='}')
	return 2;
else 
	return 3;
}

List *fileToList(char *fileName){

	FILE *fp = fopen(fileName,"r");

	char hold[200];
	List *tokenList = createList();

	while (fgets(hold,200,fp) != NULL){
		char * token = malloc(sizeof(char)*strlen(hold));
		strcpy(token, hold);
		Element * toAdd = createElement(token);
		tokenList = addBack(tokenList, toAdd);
	}
	fclose(fp);
	return tokenList;
}
