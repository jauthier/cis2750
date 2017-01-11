#include <stdio.h>

void parseFile(FILE *fp);
int sort(char c);

int main(int argc, char *argv[]) {
	
	char *fileName;
	if (argc == 2)
		fileName = argv[1];
	else 
		fileName = "Sample.c";

	FILE *fp = fopen(fileName,"r");
	
	parseFile(fp);

	return 0;
}

void parseFile(FILE *fp) {

	char c = fgetc(fp);
	char last = ' ';

	while (!feof(fp)) {

		int check = sort(c);
		int checkLast = sort(last);

		if (check == 3)
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
else if (c==','||c==';'||c=='('||c==')'||c=='{'||c=='}'||c=='"')
	return 2;
else 
	return 3;
}
