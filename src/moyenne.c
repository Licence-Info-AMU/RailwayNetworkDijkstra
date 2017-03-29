#include <stdio.h>
#include <stdlib.h>
#include "railwayNetwork.h"
#include "util.h"
#include "trace.h"
#include "trajet.h"
#include "dijkstra.h"
#include "moyenne.h"



int * calculMoyenne(RailwayNetwork * RRInstance, Trajet * trajet) {
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
	quicksort(departs,0,nbdeparts-1);
	int * moyenne=calloc(RRInstance->nbvilles,sizeof(int));
	int * result;
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
		result=dijkstra_tas(RRInstance,trajet);
		
		for (int j = 0; j < RRInstance->nbvilles; ++j){
			int tmp=result[j*3+1];
			if(tmp > 0){
				tmp-=departs[i];
			}
			if(tmp > 0){
				tmp+=facteur/2;
				tmp*=facteur;
			}
			moyenne[j]+=tmp;
		}
	}
	for (int i = 0; i < RRInstance->nbvilles; ++i){
		if(moyenne[i]>=0){
			moyenne[i]=moyenne[i]/JOUR;
		}
		else{
			moyenne[i]=-1;
		}
	}
	return moyenne;
}
