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

Cluster * clusters_init(int nbClusters){
	Cluster * clusters = malloc(nbClusters * sizeof(Cluster));
	for (int i = 0; i < nbClusters; i++)
		cluster_init(clusters + i);
	return clusters;
}

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

//Algo glouton de clustering
void clustering_algo_glouton(RailwayNetwork * RRInstance,Cluster * clusters,int nbClusters){
	int ** matrix = matriceDistance(RRInstance);	//Matrice des distances
	//Initialisation du tableau des villes déjà dans un cluster
	int * done = malloc(RRInstance->nbvilles * sizeof(int));
	for (int i = 0; i < RRInstance->nbvilles; i++)
		done[i] = 0;
	int Ville;
	for (int i = 0; i < nbClusters; i++) {
    	do{                							//tirage aléatoire d'une k villes constituant un groupe
			Ville = rand() % RRInstance->nbvilles;
      	}while (done[Ville] == 1);
      	cluster_addCity(clusters + i,Ville);
    	done[Ville] = 1;
	}
	//Pour chaque ville v n'appartient pas à V{v1, ..., vk}, placer v dans le groupe de la ville vi la plus proche de lui.
	int distance_min = INT_MAX, current_cluster;
	for (int i = 0; i < RRInstance->nbvilles; i++){
		 if (done[i] == 0) {														//si la ville ne constitue pas un cluster
        	distance_min = INT_MAX;													//intinialisation à INT_MAX
            for (int j = 0; j < nbClusters; j++) { 									//Déf. La distance entre une ville v et un sous-ensemble S de villes est d(v, S) = min{d(v, u) : u 2 S}.
            	if (matrix[i][clusters[j].villes[0]] < distance_min) {   			// on compare la ville i avec chaque les k villes constituant les groupes
                	distance_min = matrix[i][clusters[j].villes[0]];
                    current_cluster = j;											// la ville i va dans le groupe dont la durée moyenne entre i et k est la plus basse
                }
            }
            cluster_addCity(&clusters[current_cluster],i);							// on ajoute la ville au clusters[k]
    	}
	}
	free(done);
}

//Retourne le nombre de clusters voulu par l'utilisateur
int set_nbClusters(int nbvilles){
	int nbClusters = nbvilles +1;
	do{
		printf("Nombre de clusters ?\n");
		scanf("%d",&nbClusters);
	}while((nbClusters > nbvilles) || (nbClusters <= 0));
	return nbClusters;
}

//Affichage d'un Cluster
void show_cluster(Cluster * cluster){
	printf("{");
	for (int i = 0; i < cluster->nbvilles; i++){
		printf("%d", cluster->villes[i]);
		if (i < cluster->nbvilles - 1)
			printf(", ");
	}
	printf("}\n");
}

//Affichage de plusieurs Cluster
void show_clusters(Cluster * clusters, int nbClusters){
	printf("Clustering : \n");
	for (int i = 0; i < nbClusters; i++){
		printf("%d : ", i);
		show_cluster(clusters + i);
	}
}
