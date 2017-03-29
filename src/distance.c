#include <stdio.h>
#include <stdlib.h>
#include "railwayNetwork.h"
#include "util.h"
#include "trace.h"
#include "trajet.h"
#include "dijkstra.h"
#include "moyenne.h"
#include "distance.h"
/*
int calculDistance(RailwayNetwork * RRInstance, Trajet * trajet) {            //Calcule la distance moyenne entre deux villes
    if (trajet->villeDep == trajet->villeArr)
        return 0;
    //Ville dep vers ville arr
    int calculMoyenneDep = calculMoyenne(RRInstance,trajet);
    //Ville arr vers ville dep
    trajet_inverse(trajet);
    int calculMoyenneArr = calculMoyenne(RRInstance,trajet);
    return ((calculMoyenneDep + calculMoyenneArr)/2); //Renvoie la distance entre les deux villes
}

int ** matriceDistance(RailwayNetwork * RRInstance){                                    //Calcule la matrice des distances entre chaque paire de villes
    int ** mat = malloc(RRInstance->nbvilles*sizeof(int *));
    for (int i = 0; i< RRInstance->nbvilles; i++){
        mat[i] = malloc((RRInstance->nbvilles)*sizeof(int));
    }
	Trajet trajet;
    for (int i = 0; i< RRInstance->nbvilles; i++){
		trajet.villeDep = i;
        for(int j = 0; j< RRInstance->nbvilles; j++){
			trajet.villeArr = j;
            mat[i][j] = calculDistance(RRInstance,&trajet);
        }
    }
    return mat;//Renvoie la matrice des distances
}
*/
int ** matriceDistance(RailwayNetwork * RRInstance){
    int ** mat = malloc(RRInstance->nbvilles*sizeof(int *));
    Trajet trajet;
    for (int i = 0; i< RRInstance->nbvilles; i++){
        trajet.villeDep = i;
        mat[i] = calculMoyenne(RRInstance,&trajet);
    }
    for (int i = 0; i < RRInstance->nbvilles; ++i){
        for (int j = i; j < RRInstance->nbvilles; ++j){
            if (mat[i][j] == -1 || mat[j][i] == -1){
                mat[i][j]=-1;
                mat[j][i]=-1;
            }
            int tmp=(mat[i][j]+mat[j][i])/2;
            mat[i][j]=tmp;
            mat[j][i]=tmp;
        }
    }
    return mat;             //Renvoie la matrice des distances
}