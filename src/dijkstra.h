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

void set_trajet_avec_arrive(Trajet * trajet);

void set_trajet_sans_arrive(Trajet * trajet);

int extraire_le_min(int * d,int * t,int tabSize);

int calcul_dureeTrajet(RailwayNetwork * RRInstance,int heure,int villeDep, int villeArr);

void dijkstra(RailwayNetwork * RRInstance,Trajet * trajet, int * result);

int extraireLeMin_tas(int * T, int * d,int * pos, int nbS);

void dijkstra_tas(RailwayNetwork * RRInstance,Trajet * trajet, int * result);

void Affichage_result_mono_trajet(Trajet * trajet,int *result);

void Affichage_result_multi_trajet(Trajet * trajet,int *result,int tabSize);

#endif
