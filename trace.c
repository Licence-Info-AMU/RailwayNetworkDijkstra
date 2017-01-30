#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "trace.h"

#define LOGFILE "log.log"

void write_trace(char * trace){
	FILE* file = NULL;
	file = fopen (LOGFILE, "a+");
	if (file != NULL){
		fputs(trace,file);
        fclose(file);
    }else{
		perror(LOGFILE);
	}
}

void trace(char * trace,char * filename,int lineNumber){
	time_t t;
    time(&t);
	char str[30 + (strlen(trace))];
	sprintf(str,"Date : %s\nFile : %s\nLine : %d\nError : %s",ctime(&t),filename,lineNumber,trace);
	write_trace(str);
	perror(str);
}
