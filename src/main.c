#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "railwayNetwork.h"
#include "util.h"
#include "trace.h"
#include "trajet.h"
#include "dijkstra.h"
#include "moyenne.h"
#include "distance.h"
#include "cluster.h"

void affiche_trajet(RailwayNetwork * RRInstance,Trajet * trajet){
	if (trajet->villeDep != trajet->villeArr){
		int * result=dijkstra_tas(RRInstance,trajet);
		if(trajet->villeArr !=-1){
			Affichage_result_mono_trajet(trajet,result);
		}
		else{
			Affichage_result_multi_trajet(trajet,result,RRInstance->nbvilles);
		}
	}
	else {
		printf("ville de depart identique a la ville d'arrivée\n");
	}
}

int main (int argc , char * argv[]){
	char filename[] = "test.txt";
	RailwayNetwork RRInstance;
	railwayNetwork(filename,&RRInstance);
	show_all_RR(&RRInstance);
	Trajet trajet;
	set_trajet_user(&RRInstance,&trajet);
	affiche_trajet(&RRInstance,&trajet);
	int ** mat=matriceDistance(&RRInstance);
	showmatrice(mat,RRInstance.nbvilles,RRInstance.nbvilles);
	int nbClusters = set_nbClusters(RRInstance.nbvilles);
	Cluster *clusters = clusters_init(nbClusters);
	clustering_algo_glouton(&RRInstance,clusters,nbClusters);
	show_clusters(clusters, nbClusters);
	return 0;
}
