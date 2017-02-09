main: main.o read.o trace.o util.o dijkstra.o generate.o
	gcc main.o read.o trace.o util.o dijkstra.o generate.o -o projet

main.o: main.c
	gcc -Wall -c main.c

read.o: read.c
	gcc -Wall -c read.c

trace.o: trace.c
	gcc -Wall -c trace.c

util.o: util.c
	gcc -Wall -c util.c

dijkstra.o: dijkstra.c
	gcc -Wall -c dijkstra.c

generate.o: generate.c
	gcc -Wall -c generate.c

clean :
	rm -f *.o
	rm -f projet