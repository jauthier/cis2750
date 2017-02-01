// post.c  



int main (int argc, char *argv[]){
	// take in user name
    char buffer[200];

    if (argc == 1){
        printf("Please enter your username.\n");
        exit(0);
    } else {
        int i;
        strcpy(buffer,argv[1]);
        for (i=2;i<argc;i++){
            //put all strings into one
            strcat(buffer, " ");
            strcat(buffer, argv[i])
        }

        printf("%s\n",buffer);
    }

    //check if the user has permission to post on the stream

    //if the don't then send an error message and exit


    //if they do, check if the file exists for the stream

    // if it does exist get that file
    //if it doesn't then make a file for it


}