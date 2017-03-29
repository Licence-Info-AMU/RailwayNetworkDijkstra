#ifndef DIJKSTRA_H
#define DIJKSTRA_H

//Extraire le min
int extraire_le_min(int * d,int * t,int tabSize);

//Algorithme de Dijkstra
int * dijkstra(RailwayNetwork * RRInstance,Trajet * trajet); 		//result[3*nbville]

//Extraire le min avec les tas
int extraireLeMin_tas(int * T, int * d,int * pos, int nbS);

//Algorithme de Dijkstra avec utilisation des tas
int * dijkstra_tas(RailwayNetwork * RRInstance,Trajet * trajet);	//result[3*nbville]

#endif
