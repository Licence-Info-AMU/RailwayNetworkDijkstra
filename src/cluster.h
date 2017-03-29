#ifndef CLUSTER_H
#define CLUSTER_H 

//Définition d'un Cluster
typedef struct{
   int nbvilles;
   int *villes;
}Cluster;

//Initialisation d'un tableau de Cluster
Cluster * clusters_init(int nbCluster);

//Initialisation du Cluster
void cluster_init(Cluster * cluster);

//Ajouter une ville à un Cluster
void cluster_addCity(Cluster * cluster, int Ville);

//Supprimer une ville d'un Cluster
int cluster_removeCity(Cluster * cluster, int Ville);

//Algo glouton de clustering
void clustering_algo_glouton(RailwayNetwork * RRInstance,Cluster * clusters,int nbClusters);

//Retourne le nombre de clusters voulu par l'utilisateur
int set_nbClusters(int nbvilles);

//Affichage d'un Cluster
void show_cluster(Cluster * cluster);

//Affichage de plusieurs Cluster
void show_clusters(Cluster * clusters, int nbClusters);

#endif
