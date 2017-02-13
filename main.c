#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "railwayNetwork.h"
#include "util.h"
#include "trace.h"
#include "dijkstra.h"
#include "generate.h"

void infos(){
	printf("Ce fichier a ete compile le %s a %s\n", __DATE__, __TIME__);
}

void usage(){
	printf("ToDo");
}

int main (int argc , char * argv[]){
	char filename[] = "test.txt";
	struct RailwayNetwork RRInstance;
	railwayNetwork(filename,&RRInstance);
	show_RR(&RRInstance);
	define_lignesInVille(&RRInstance);
	show_lignesInVille(&RRInstance);
	show_voisins(&RRInstance);
	return 0;
}
