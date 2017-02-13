#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "trace.h"
#include "dijkstra.h"

#define INFINI 99999999
int * d;

void init_d(int tabSize){
	d = malloc (sizeof(int) * tabSize);
	if (d == NULL){
		trace("Allocation impossible de int * d",__FILE__,__LINE__ );
		exit(EXIT_FAILURE);
	}
}

void init_Dijkstra(RailwayNetwork * RRInstance,int sdeb){
	init_d(RRInstance->nbvilles);
	for(int s = 0; s < RRInstance->nbvilles;s++){ /* on initialise les sommets autres que sdeb à infini */
		d[s] = INFINI;
	}
	d[sdeb] = 0;
}

/*
int ** Dijkstra(RailwayNetwork * RRInstance,int sdeb, int h_deb){
	init_Dijkstra(RRInstance,sdeb);
	
	while(){ 
	
	}
	return d;
}
*/
