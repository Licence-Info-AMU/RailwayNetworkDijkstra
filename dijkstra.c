#include <stdio.h>
#include <stdlib.h>
#include "read.h"
#include "trace.h"

#define INFINI 99999999
int * d;

void init_d(int tabTaille){
	d = malloc (sizeof(int) * tabTaille);
	if (d == NULL){
		trace("Allocation impossible de int * d",__FILE__,__LINE__ );
		exit(EXIT_FAILURE);
	}
}

void init_Dijkstra(RR * RRInstance,int sdeb){
	init_d(RRInstance->nbville);
	for(int s = 0; s < RRInstance->nbville;s++){ /* on initialise les sommets autres que sdeb à infini */
		d[s] = INFINI;
	}
	d[sdeb] = 0;
}

int ** Dijkstra(RR * RRInstance,int sdeb, int h_deb){
	init_Dijkstra(RRInstance,sdeb);
	
	while(){ 
	
	}
	return d;
}
