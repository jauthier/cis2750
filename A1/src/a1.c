#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

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
