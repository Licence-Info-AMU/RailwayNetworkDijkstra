#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "railwayNetwork.h"

int extraire_le_min(int * d,int * t,int tabSize);

void dijkstra(RailwayNetwork * RRInstance,Trajet * trajet, int * result); //result[3*nbville]

int extraireLeMin_tas(int * T, int * d,int * pos, int nbS);

void dijkstra_tas(RailwayNetwork * RRInstance,Trajet * trajet,int * result);	//result[3*nbville]

#endif
