#ifndef CLUSTER_H
#define CLUSTER_H 

//Définition d'un Cluster
typedef struct{
   int nbvilles;
   int *villes;
}Cluster;

//Initialisation du Cluster
void cluster_init(Cluster * cluster);

//Ajouter une ville à un Cluster
void cluster_addCity(Cluster * cluster, int Ville);

//Supprimer une ville d'un Cluster
int cluster_removeCity(Cluster * cluster, int Ville);

//Algo final de clustering
void clustering(RailwayNetwork * RRInstance,Cluster * clusters,int nbCluster);

//Algo glouton de clustering
void clustering_algo_glouton(RailwayNetwork * RRInstance,Cluster * clusters,int nbClusters);

//Affichage d'un Cluster
void cluster_print(Cluster * cluster);

//Affichage de plusieurs Cluster
void cluster_printAll(Cluster * clusters, int nbClusters);

#endif
