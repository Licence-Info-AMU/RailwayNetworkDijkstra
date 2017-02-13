#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "util.h"
#include "trace.h"
#include "dijkstra.h"
#include "generate.h"
#include <assert.h>

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
	define_lignesInVille(&RRInstance);
	show_lignesInVille(&RRInstance);
	for (int i = 0; i < RRInstance.nbvilles; ++i)
	{
		show_voisins(&RRInstance,i);
	}
	
	return 0;
}
