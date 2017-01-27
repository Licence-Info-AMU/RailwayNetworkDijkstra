#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOGFILE "log.log"

void write_trace(char * trace){
	FILE* file = NULL;
	file = fopen (LOGFILE, "a+");
	if (file != NULL){
		fputs(trace,file);
        fclose(file);
    }else{
		perror("Fatal Error : can't write on log.log !");
	}
}

void trace(char * trace,char * filename,int lineNumber){
	time_t t;
    time(&t);
	char str[30 + (strlen(trace))];
	sprintf(str,"Error : %s \nFile : %s \nLine : %d \nDate : %s",trace,filename,lineNumber,ctime(&t));
	write_trace(str);
	perror(str);
}
