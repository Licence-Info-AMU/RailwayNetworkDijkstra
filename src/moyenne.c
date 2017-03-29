#include <stdio.h>
#include <stdlib.h>
#include "railwayNetwork.h"
#include "util.h"
#include "trace.h"
#include "trajet.h"
#include "dijkstra.h"
#include "moyenne.h"

int calculMoyenne(RailwayNetwork * RRInstance, Trajet * trajet) {
	int nbdeparts=0;
	ville * ville=&RRInstance->villes[trajet->villeDep];
	for (int i = 0; i < RRInstance->nblignes; ++i){
		if (ville->lignesInVille[i] != -1){
			nbdeparts+=RRInstance->lignes[i].nbhoraires;
		}
	}
	int departs[nbdeparts];
	int k=0;
	for (int i = 0; i < RRInstance->nblignes; ++i){
		if (ville->lignesInVille[i] != -1){
			for (int j = 0; j < RRInstance->lignes[i].nbhoraires; ++j){
				if (k<nbdeparts){
					departs[k]=RRInstance->lignes[i].horaires[ville->lignesInVille[i]][j];
					k++;
				}
				else{
					trace ("Bad init calculMoyenne",__FILE__,__LINE__ );
				}
			}
		}
	}
	quicksort(departs,0,nbdeparts);
	int * moyenne = calloc(RRInstance->nbvilles, sizeof(int));
	int result[RRInstance->nbvilles*3];
	for (int i = 0; i < nbdeparts; ++i){
		trajet->horaireDep=departs[i];
		int facteur;
		if (i==0){
			facteur= departs[i] - departs[nbdeparts-1];
			facteur+=JOUR;
		}
		else{
			facteur= departs[i] - departs[i-1];
		}
		if(facteur<0){
			trace("facteur calculMoyenne negatif",__FILE__,__LINE__ );
		}
		dijkstra_tas(RRInstance,trajet,result);
		for (int j = 0; j < RRInstance->nbvilles; ++j){
			if(j != trajet->villeDep){
				moyenne[j]+=(result[j*3+1]+facteur/2)*facteur;
			}
		}
	}
	for (int i = 0; i < RRInstance->nbvilles; ++i){
		moyenne[i]/=JOUR;
		printf("ville %d vers ville %d moyenne %d\n",trajet->villeDep,i,moyenne[i]);
	}
	return moyenne[trajet->villeArr];
}
