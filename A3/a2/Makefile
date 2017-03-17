all: addauthor post

addauthor.o:
	gcc -Wall -ansi -g addauthor.c -o addauthor.o -c

post.o:
	gcc -Wall -ansi -g post.c -o post.o -c

addauthor: addauthor.o
	gcc -Wall -ansi -g addauthor.o -o addauthor -L. -lstream

post: post.c
	gcc -Wall -ansi -g post.c -o post -L. -lstream
