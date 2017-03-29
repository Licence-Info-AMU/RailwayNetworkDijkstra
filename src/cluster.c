#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "railwayNetwork.h"
#include "util.h"
#include "trace.h"
#include "trajet.h"
#include "dijkstra.h"
#include "moyenne.h"
#include "distance.h"
#include "cluster.h"

//Initialisation du Cluster
void cluster_init(Cluster * cluster){
	cluster->villes = NULL;
	cluster->nbvilles = 0;
}

//Ajouter une ville à un Cluster
void cluster_addCity(Cluster * cluster, int Ville){
	cluster->nbvilles++;
	cluster->villes = realloc(cluster->villes, cluster->nbvilles * sizeof(int));
	cluster->villes[cluster->nbvilles - 1] = Ville;
}

//Supprimer une ville d'un Cluster
int cluster_removeCity(Cluster * cluster, int Ville){
	for (int i = 0; i < cluster->nbvilles; i++){
		if (cluster->villes[i] == Ville){
			cluster->villes[i] = cluster->villes[cluster->nbvilles - 1];
			cluster->nbvilles--;
			cluster->villes = realloc(cluster->villes, cluster->nbvilles * sizeof(ville));
			return 1;
		}
	}
	return -1;
}

//Algo final de clustering
void clustering(RailwayNetwork * RRInstance,Cluster * clusters,int nbCluster){
	
}

//Algo glouton de clustering
void clustering_algo_glouton(RailwayNetwork * RRInstance,Cluster * clusters,int nbClusters){
	//Soient v1 et v2 les deux villes les plus éloignées (d(v1, v2) est max.)
	int maximum = 0, v1,v2;
	clusters = malloc(nbClusters * sizeof(Cluster));
	for (int i = 0; i < nbClusters; i++)
		cluster_init(clusters + i);
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
	//Initialisation du tableau des villes déjà dans un cluster
	int * done = malloc(RRInstance->nbvilles * sizeof(int));
	for (int i = 0; i < RRInstance->nbvilles; i++)
		done[i] = 0;
	//Placer v1 dans V1 et v2 dans V2.
	cluster_addCity(&clusters[0], v1); //v1
	cluster_addCity(&clusters[1], v2); //v2
	//Ville v1 et v2 noté comme faites
	done[v1] = 1;
	done[v2] = 1;
	//Pour i = 2, ..., k faire
	int vi = -1;
	int clustersAlreadyFilled = 2;
	for(int i = 2; i < nbClusters;i++){
		//Trouver une ville vi à distance maximum des villes {v1, ..., vi−1}
		int max = 0;
		for (int j = 0; j < RRInstance->nbvilles; j++){
			int min = INT_MAX;
			for (int c = 0; c < clustersAlreadyFilled; c++){
				if (min > matrix[j][clusters[c].villes[0]])
					min = matrix[j][clusters[c].villes[0]];
			}
			if (min > max){
				max = min;
				vi = j;
			}
		}
		cluster_addCity(&clusters[i], vi);
		done[vi] = 1;
		clustersAlreadyFilled++;
	}
	//Pour chaque ville v n'appartient pas à V{v1, ..., vk}, placer v dans le groupe de la ville vi la plus proche de lui.
	for (int i = 0; i < RRInstance->nbvilles; i++){
		if (done[i])
			continue;

		for (int c = 0; c < nbClusters; c++){
		
		}	
	}
	free(done);
}
/*
Déf. La distance entre une ville v et un sous-ensemble S de villes est
d(v, S) = min{d(v, u) : u 2 S}.
*/

//Affichage d'un Cluster
void cluster_print(Cluster * cluster){
	printf("{");
	for (int i = 0; i < cluster->nbvilles; i++){
		printf("%d", cluster->villes[i]);
		if (i < cluster->nbvilles - 1)
			printf(", ");
	}
	printf("}\n");
}

//Affichage de plusieurs Cluster
void cluster_printAll(Cluster * clusters, int nbClusters){
	printf("Clustering : \n");
	for (int i = 0; i < nbClusters; i++){
		printf("%d : ", i);
		cluster_print(&clusters[i]);
	}
}
