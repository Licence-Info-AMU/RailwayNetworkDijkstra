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

//Demande l'heure de départ à l'utilisateur
int set_time();

//Affiche les valeurs d'un trajet
void show_trajet(Trajet * trajet);

//Initialise un trajet en demandant à l'utilisateur la ville de départ et d'arrivée
void set_trajet_avec_arrive(Trajet * trajet);

//Initialise un trajet en demandant à l'utilisateur la ville de départ
void set_trajet_sans_arrive(Trajet * trajet);

//Echange la ville de départ et d'arrivée d'un trajet
void trajet_inverse(Trajet * trajet);

//Demande à l'utilisateur si il veut un trajet avec ou sans ville d'arrivée
void set_trajet_user(RailwayNetwork * RRInstance,Trajet * trajet);

//Calcul la duree du trajet
int calcul_dureeTrajet(RailwayNetwork * RRInstance,int heure,int villeDep, int villeArr, int * ligneutilise);

//Affiche le résultat d'un trajet
void Affichage_result_mono_trajet(Trajet * trajet,int result[]);

//Affiche le résultat d'un trajet pour toutes les arrivées possible
void Affichage_result_multi_trajet(Trajet * trajet,int result[],int tabSize);

#endif
