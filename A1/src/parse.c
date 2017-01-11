#include "parse.h"

void parseFile(FILE *fp) {

	char c = fgetc(fp);
	char last = ' ';
	FILE *fWrite = fopen("parsedProgram.txt","w")

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

		if (check == 3) //
			fprintf(fWrite,"%c", c);
		else if (check == 2 && (checkLast == 1 || checkLast == 2))
			fprintf(fWrite,"%c\n", c);
		else if (check == 2 && checkLast == 3)
			fprintf(fWrite,"\n%c\n", c);
		else if (check == 1 && checkLast == 3)
			fprintf(fWrite,"\n");		

		last = c;
		c = fgetc(fp);
	}
	
	fclose(fWrite);
}




int sort(char c) {

if (c==' '||c=='\t'||c=='\n'||c=='\r') 
	return 1;
else if (c==','||c==';'||c=='('||c==')'||c=='{'||c=='}')
	return 2;
else 
	return 3;
}
