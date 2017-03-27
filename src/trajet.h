#ifndef TRAJET_H
#define TRAJET_H

#include "railwayNetwork.h"

#define JOUR 1440
#define HEURE 60


typedef struct trajet{
	int horaireDep;
	int villeDep;
	int villeArr;
}Trajet;

int set_time();

void show_trajet(Trajet * trajet);

void set_trajet_avec_arrive(Trajet * trajet);

void set_trajet_sans_arrive(Trajet * trajet);

int calcul_dureeTrajet(RailwayNetwork * RRInstance,int heure,int villeDep, int villeArr, int * ligneutilise);

void Affichage_result_mono_trajet(Trajet * trajet,int result[]);

void Affichage_result_multi_trajet(Trajet * trajet,int result[],int tabSize);

#endif