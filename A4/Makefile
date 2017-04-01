FLAGS = -Wall -ansi -g

all: addauthor post readConfig db

addauthor.o: addauthor.c
	gcc $(FLAGS) addauthor.c -o addauthor.o -c

post.o: post.c
	gcc $(FLAGS) post.c -o post.o -c

addauthor: addauthor.o
	gcc $(FLAGS) addauthor.o -o addauthor -L. -lstream

post: a2/post.o
	gcc $(FLAGS) post.o -o post -L. -lstream

readConfig: textToHtml.c translateConfig.c
	gcc $(FLAGS) textToHtml.c translateConfig.c -o readConfig 

db: db.o dbFunctions.o
	gcc db.o dbFunctions.o -o db -lmysqlclient -L/usr/lib/x86_64-linux-gnu/
db.o:
	gcc db.c -o db.o -c

dbFunctions.o:
	gcc dbFunctions.c -o dbFunctions.o -c

clean:
	rm *.o post addauthor
