#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
void infos(){
	printf("Ce fichier a ete compile le %s a %s\n", __DATE__, __TIME__);
}

void usage(){
	printf("ToDo");
}

int main (int argc , char * argv[]){
	char filename[] = "test.txt";
	struct RR RRInstance;
	read_file(filename,&RRInstance);
	show_RR(&RRInstance);
	return 0;
}
