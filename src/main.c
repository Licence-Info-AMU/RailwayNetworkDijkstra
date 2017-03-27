#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "railwayNetwork.h"
#include "util.h"
#include "trace.h"
#include "trajet.h"
#include "dijkstra.h"
#include "distance.h"
#include "moyenne.h"

void infos(){
	printf("Ce fichier a ete compile le %s a %s\n", __DATE__, __TIME__);
}

void usage(){
	printf("ToDo");
}

int main (int argc , char * argv[]){
	char filename[] = "test.txt";
	RailwayNetwork RRInstance;
	railwayNetwork(filename,&RRInstance);
	int test=0;
/*
	printf("afficher les valeurs lue ? (OUI:1/NON:0)\n");
	scanf("%d",&test);
*/
	if (test==1)
	{
		show_RR(&RRInstance);
		show_lignesInVille(&RRInstance);
		show_voisins(&RRInstance);
	}

	Trajet trajet;
	test=0;
/*
	printf("voulez vous définir une ville d'arrivée ? (OUI:1/NON:0)\n");
	scanf("%d",&test);
*/
	if (test==1){
		set_trajet_avec_arrive(&trajet);
		if (trajet.villeDep>RRInstance.nbvilles || trajet.villeArr>RRInstance.nbvilles){
			trace("ville du trajet incorrect !",__FILE__,__LINE__);
			exit(EXIT_FAILURE);
		}
	}
	if (test==0){
		set_trajet_sans_arrive(&trajet);
		if (trajet.villeDep>RRInstance.nbvilles){
			trace("ville de départ incorrect !",__FILE__,__LINE__);
			exit(EXIT_FAILURE);
		}
	}

	if (trajet.villeDep != trajet.villeArr || test==0){
		int result[RRInstance.nbvilles*3];
		dijkstra_tas(&RRInstance,&trajet,result);
		if(trajet.villeArr !=-1){
			Affichage_result_mono_trajet(&trajet,result);
		}
		else{
			Affichage_result_multi_trajet(&trajet,result,RRInstance.nbvilles);
		}
	}
	else {
		printf("ville de depart identique a la ville d'arrivée\n");
	}
	calculMoyenne(&RRInstance,&trajet);

	return 0;
}
