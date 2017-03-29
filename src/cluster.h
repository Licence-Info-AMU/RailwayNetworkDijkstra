#ifndef CLUSTER_H
#define CLUSTER_H 

typedef struct{
   int nbvilles;
   int *villes;
}Cluster;

void cluster_init(Cluster * cluster);

void cluster_addCity(Cluster * cluster, int Ville);

Cluster * clustering(RailwayNetwork * RRInstance,int nbCluster);

Cluster * clustering_algo_glouton(RailwayNetwork * RRInstance,int nbCluster);

#endif
