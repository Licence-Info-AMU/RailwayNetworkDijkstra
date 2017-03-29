#ifndef TRAJET_H
#define TRAJET_H 
#include "railwayNetwork.h"

typedef struct{
	int horaireDep;
	int villeDep;
	int villeArr;
}Trajet;

static int const JOUR = 1440;
static int const HEURE = 60;

int set_time();

void show_trajet(Trajet * trajet);

void set_trajet_avec_arrive(Trajet * trajet);

void set_trajet_sans_arrive(Trajet * trajet);

void trajet_inverse(Trajet * trajet);

void set_trajet_user(RailwayNetwork * RRInstance,Trajet * trajet);

int calcul_dureeTrajet(RailwayNetwork * RRInstance,int heure,int villeDep, int villeArr, int * ligneutilise);

void Affichage_result_mono_trajet(Trajet * trajet,int result[]);

void Affichage_result_multi_trajet(Trajet * trajet,int result[],int tabSize);

#endif
