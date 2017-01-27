#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void infos(){
	printf("Ce fichier a ete compile le %s a %s\n", __DATE__, __TIME__);
}

void usage(){
	printf("ToDo");
}

int main (int argc , char * argv[]){
	if(argc > 1){
		//ToDo
	}else{
		usage();
	}
	return 0;
}
