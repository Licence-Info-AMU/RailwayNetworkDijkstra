#ifndef DIJKSTRA_H
#define DIJKSTRA_H

int extraire_le_min(int * d,int * t,int tabSize);

int * dijkstra(RailwayNetwork * RRInstance,Trajet * trajet); 		//result[3*nbville]

int extraireLeMin_tas(int * T, int * d,int * pos, int nbS);

int * dijkstra_tas(RailwayNetwork * RRInstance,Trajet * trajet);	//result[3*nbville]

#endif
