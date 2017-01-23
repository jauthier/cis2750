
// read in a line
// if the line says class
// comments


typedef struct Variable {
	char *type;
	char *name;

} Variable;

typedef struct Element {
	void * elementPtr;
	Element * next;
} Element;

typedef struct Function {
	Element *varList;
};

typedef struct Structure { 

	Element *varList;
	Element *funcPtrList;
	
}Structure;

void translate(char *readFile) {
	FILE *fRead = fopen(readFile, "r");
	FILE *fWrite = fopen("prog.c","w");

	char token[50];
	fgets(token, 50, fRead);

	if (strcmp(token,"class")==0){
		//go to translatelass()
	} else {
		//we either have a global variable or a function
	}

}

void* translateClass(FILE *fRead, FILE *fWrite) {
	
	// next line is the name of the class
	char className[20];
	fgets(className, 20, fRead);

	// if the next line is a "{" then we have a normal class
	char next[20];
	fgets(next, 20 ,fRead);
	if (strcmp(next,"{") == 0){

	}


	// if the next line is a "{" then we have a normal class

		char *typeHold;
		char *nameHold;
}

void *createStruct(char *name, FILE *fRead){

	char hold[200];
	fgets(hold, 200, fRead);
	while (strcmp(hold, "}") != 0){ // while we are not at the end of the struct
		if (strcmp() == 0)
	}
}



// make a struct to hold each method, type, name, list of contents