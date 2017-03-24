#ifndef TRAJET_H
#define TRAJET_H 

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

void Affichage_result_mono_trajet(Trajet * trajet,int *result);

void Affichage_result_multi_trajet(Trajet * trajet,int *result,int tabSize);

#endif
