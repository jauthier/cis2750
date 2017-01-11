#include "parse.h"

void parseFile(FILE *fp) {

	char c = fgetc(fp);
	char last = ' ';

	while (!feof(fp)) {

		int check = sort(c);
		int checkLast = sort(last);

		// deals with strings ---- need to deal with quotes in strings
		if (c == '"'){
			// print first quotation mark
			printf("%c", c);
			c = fgetc(fp);
			// print the letters in between
			while (c != '"') {
				printf("%c", c);
				c =fgetc(fp);
			}
			printf("%c\n", c);
			last = c;
			c = fgetc(fp);
		}

		if (check == 3) //
			printf("%c", c);
		else if (check == 2 && (checkLast == 1 || checkLast == 2))
			printf("%c\n", c);
		else if (check == 2 && checkLast == 3)
			printf("\n%c\n", c);
		else if (check == 1 && checkLast == 3)
			printf("\n");

		last = c;
		c = fgetc(fp);
	}
}




int sort(char c) {

if (c==' '||c=='\t'||c=='\n'||c=='\r') 
	return 1;
else if (c==','||c==';'||c=='('||c==')'||c=='{'||c=='}')
	return 2;
else 
	return 3;
}
