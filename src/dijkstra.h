#include "railwayNetwork.h"
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

typedef struct trajet{
	int horaireDep;
	int villeDep;
	int villeArr;
}Trajet;

int set_time();

void show_trajet(Trajet * trajet);
void set_trajet(Trajet * trajet);


int extraire_le_min1(int * d,int * t,int tabSize);

int calcul_dureeTrajet(RailwayNetwork * RRInstance,int heure,int villeDep, int villeArr);

void dijkstra(RailwayNetwork * RRInstance,Trajet * trajet, int * result);


#endif
