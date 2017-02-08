#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]){
	
    char * test = readInput();
    
    return 0;	
}

char * readInput (){
    char buffer[100];
    char *hold = malloc(sizeof(char)*1000);
    printf("Enter text: ");
    if (fgets(buffer, 100, stdin) != NULL){
        strcpy(hold, buffer);
        while (fgets(buffer, 100, stdin) != NULL){
            strcat(hold, buffer);
        }
    }
    printf("%s\n", hold);
    char *text = malloc(sizeof(char)*strlen(hold));
    return text;
}