read: read.o trace.o util.o
	gcc read.o trace.o util.o -o read

read.o: read.c
	gcc -Wall -c read.c

trace.o: trace.c
	gcc -Wall -c trace.c

util.o: util.c
	gcc -Wall -c util.c

clean :
	rm -f *.o
	rm -f read