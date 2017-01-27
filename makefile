lecture: lecture.o
	gcc lecture.o -o lecture

lecture.o: lecture.c
	gcc -Wall -c lecture.c
