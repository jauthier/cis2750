FLAGS = -Wall -ansi -g

all: addauthor post

addauthor.o: a2/addauthor.c
	gcc $(FLAGS) a2/addauthor.c -o a2/addauthor.o -c

post.o: a2/post.c
	gcc $(FLAGS) a2/post.c -o a2/post.o -c

addauthor: a2/addauthor.o
	gcc $(FLAGS) a2/addauthor.o -o a2/addauthor -L./a2 -lstream

post: a2/post.o
	gcc $(FLAGS) a2/post.o -o a2/post -L./a2 -lstream
