#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <stdio.h>
#include <stdlib.h>
#include "read.h"
#include "trace.h"
#include "util.h"
#include <string.h>


typedef struct trajet{
    
	int horaireDep;
	int horaireArr;
	int numeroLigne;
}trajet;

void define_lignesInVille(RR * RRInstance);

void show_lignesInVille(RR * RRInstance);

int get_voisin(RR * RRInstance,int nomville,int * voisins);

void show_voisins(RR * RRInstance,int nomville);

void init_d(int tabTaille);
void init_Dijkstra(RR * RRInstance,int sdeb);

#endif
