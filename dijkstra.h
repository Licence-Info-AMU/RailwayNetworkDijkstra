#include "railwayNetwork.h"
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

typedef struct trajet{
	int horaireDep;
	int villeDep;
	int villeArr;
}Trajet;

typedef trajet * listeTrajet;

typedef struct {

	int horaire;
	int ville;
	int numeroLigne;
}itineraire;

typedef itineraire * listeItineraire;

int set_time();

void show_trajet(Trajet * trajet);

void set_trajet(Trajet * trajet);

int extraire_le_min1(int * d,int * t,int tabSize);

int calcul_dureeTrajet(RailwayNetwork * RRInstance,int heure,int villeDep, int villeArr);

void dijkstra(RailwayNetwork * RRInstance,Trajet * trajet, int * result);

int ExtraireLeMin(int * F, int * d,int * pos, int nbS);

void init_Tabs(int *F, int *d, int *pos,int tabSize);

void init_Dijkstra(RR * RRInstance,int villeDepart,int *F, int *d,int *pos);

int Dijkstra_tas(int villeDepart, int villeArrivee,int sdeb, int h_deb,RR * RRInstance);

#endif
