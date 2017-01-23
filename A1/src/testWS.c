#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {

	printf("Enter a string: ");
	char buffer[200];
	fgets(buffer, 200, stdin);

	int check = isWhiteSpace(buffer);
	if (check == 1)
		printf("all white space\n");
	else 
		printf("not all white space\n");

	return 0;
}

int isWhiteSpace(char * str) {
	int len = strlen(str);
	int i = 0;
	for (i=0;i<len;i++) {
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r'){
			printf("here \"%c\"\n", str[i]);
			return 0;
		}
	}
	return 1;
}