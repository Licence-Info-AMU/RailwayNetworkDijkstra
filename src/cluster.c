#include <stdio.h>
#include <stdlib.h>
#include "railwayNetwork.h"
#include "util.h"
#include "trace.h"
#include "trajet.h"
#include "dijkstra.h"
#include "moyenne.h"
#include "distance.h"
#include "cluster.h"

void cluster_init(Cluster * cluster){
	cluster->villes = NULL;
	cluster->nbvilles = 0;
}

void cluster_addCity(Cluster * cluster, int Ville){
	cluster->nbvilles++;
	cluster->villes = realloc(cluster->villes, cluster->nbvilles * sizeof(int));
	cluster->villes[cluster->nbvilles - 1] = Ville;
}

Cluster * clustering(RailwayNetwork * RRInstance,int nbCluster){
	
}

Cluster * clustering_algo_glouton(RailwayNetwork * RRInstance,int nbCluster){
	//Soient v1 et v2 les deux villes les plus éloignées (d(v1, v2) est max.)
	int maximum = 0, v1,v2;
	Cluster cluster[nbCluster];
	int ** matrix = matriceDistance(RRInstance);
	for(int i = 0 ; i < RRInstance->nbvilles ; i++ ){
		for(int j = 0 ;j < RRInstance->nbvilles ; j++ ){
			if ( matrix[i][j] > maximum ){
				maximum = matrix[i][j];
				v1 = i;
				v2 = j;
			}
		}
	}
	//Placer v1 dans V1 et v2 dans V2.
	cluster[0].villes[0] = v1; //V1
	cluster[1].villes[0] = v2; //V2
	
}
/*
Pour i = 3, ..., k faire
Trouver une ville vi à distance maximum des villes {v1, ..., vi−1}.
Placer la ville vi dans un nouveau groupe Vi.
Pour chaque ville v /2 {v1, ..., vk}, placer v dans le groupe de la ville
vi la plus proche de lui.
Déf. La distance entre une ville v et un sous-ensemble S de villes est
d(v, S) = min{d(v, u) : u 2 S}.
*/
