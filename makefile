LFLAGS=-lreadline

all: csapp.o gangwarshell.o
	gcc csapp.o gangwarshell.o -o out.o ${LFLAGS}

csapp.o: csapp.c
	gcc -c -g csapp.c
	
gangwarshell.o: gangwarshell.c
	gcc -c -g gangwarshell.c

clean:
	rm -rf *.o
	
