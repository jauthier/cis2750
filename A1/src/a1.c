#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

void parseFile(FILE *fp);
int sort(char c);

int main(int argc, char *argv[]) {
	
	char *fileName;
	if (argc == 2) {
		fileName = argv[1];
	} else {
		printf("Please enter the name of the file you wish to translate.\n");
		exit(0);
	} 	

	FILE *fp = fopen(fileName,"r");
	
	List *list = parseFile(fp);

	return 0;
}
