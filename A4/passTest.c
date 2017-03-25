#include <stdio.h>

int main (int argc, char * argv[]){
	char password[100];
    char p;
    int i=0;
	printf("Enter password: ");
	while((p=getch())!= 13){
         password[i++] = p;
         printf("*");
    }

    printf("%s\n", password);
	return 0;
}