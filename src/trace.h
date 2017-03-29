#ifndef TRACE_H
#define TRACE_H

//Ecrit une trace(char *) dans un fichier
void write_trace(char * trace);

//Prépare et écrit la trace dans un fichier
void trace(char * trace,char * filename,int lineNumber);

#endif
