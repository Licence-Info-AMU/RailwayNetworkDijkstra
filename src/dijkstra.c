#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "trace.h"
#include "tas.h"
#include "trajet.h"
#include "railwayNetwork.h"
#include "dijkstra.h"

#define INFINI -1

int extraire_le_min(int * duree,int * done,int tabSize){
	int min=-1,rankmin=-1;
	for (int i = 0; i < tabSize; ++i){
		if(done[i] == 0 && duree[i]>=0){
			if(min==-1){
				min=duree[i];
				if (min != -1){
					rankmin=i;
				}
			}
			else if(min > duree[i]){
				min=duree[i];
				rankmin=i;
			}	
		}
	}
	if (rankmin <0){
		trace("extraire_le_min negatif !",__FILE__,__LINE__);
		exit(EXIT_FAILURE);
	}
	return rankmin;
}


int * dijkstra(RailwayNetwork * RRInstance,Trajet * trajet){
	int tabSize=RRInstance->nbvilles;
	int d[tabSize],done[tabSize],precedent[tabSize],ligne[tabSize];	
	precedent[trajet->villeDep]=-1;
	if (d == NULL){
		trace("Allocation impossible de int * d",__FILE__,__LINE__ );
		exit(EXIT_FAILURE);
	}
	for(int s = 0; s < tabSize;s++){ /* on initialise les sommets autres que trajet->villeDep à infini */
		d[s] = INFINI;
		done[s] = 0;
		precedent[s]=-1;
		ligne[s]=-1;
	}
	d[trajet->villeDep] = trajet->horaireDep;

	for (int i = 0; i < tabSize; ++i){
		int min = extraire_le_min(d,done,tabSize);
		int voisinMin[RRInstance->nblignes];
		int nbvoisin = get_voisin(RRInstance,min,voisinMin);
		done[min]=1;
		
		for (int j = 0; j < nbvoisin; ++j){
			// printf(" dmin %d rmin %d rvoisin %d \n",d[min],min,voisinMin[j]);
			int ligneutilise;
			int dureeTrajet = calcul_dureeTrajet(RRInstance,d[min],min,voisinMin[j],&ligneutilise);
			if (d[voisinMin[j]]==-1){
				d[voisinMin[j]]=d[min]+dureeTrajet;
				// printf("%d %d %d\n",d[voisinMin[j]],d[min],dureeTrajet);
				precedent[voisinMin[j]]=min;
				ligne[voisinMin[j]]=ligneutilise;
			}
			else if (d[voisinMin[j]] > d[min]+dureeTrajet){
				d[voisinMin[j]]=d[min]+dureeTrajet;
				precedent[voisinMin[j]]=min;
				ligne[voisinMin[j]]=ligneutilise;
			}
		}
	}
	/*
	int tmp;
	result[tabSize]=d[trajet->villeArr]-trajet->horaireDep;
	tmp=trajet->villeArr;
	for (int i = 0; i < tabSize; ++i){
		if (tmp !=-1){
			result[i]=tmp;
			tmp=precedent[result[i]];
		}
		else{
			result[i]=-1;
		}
	}
	*/
	int * result = malloc(tabSize*3*sizeof(int *));
	for (int i = 0; i < tabSize; ++i){
		result[i*2]=precedent[i];
		result[i*2+1]=d[i];
		result[i*3+2]=ligne[i];
	}
	return result;
	
}

int extraireLeMin_tas(int * T, int * d,int * pos, int nbS) {	//Recherche du minimum
	int min = T[0];
	nbS--;
	swap_tab_int(T,0,nbS);
	swap_tab_int(pos,T[0],T[nbS]);
	entasserVersLeBas(pos[T[0]],T,pos,d,nbS);
	return min;
}


int * dijkstra_tas(RailwayNetwork * RRInstance,Trajet * trajet){
	int tabSize=RRInstance->nbvilles;
	int T[tabSize], d[tabSize], pos[tabSize],precedent[tabSize], ligne[tabSize];
	for(int s = 0; s < tabSize;s++){ 								// on initialise les s (sommets) autres que villeDepart à infini 
		d[s] = INFINI;
		T[s] = s;
		pos[s] = s;
		precedent[s]=-1;
		ligne[s]=-1;
	}
	d[trajet->villeDep] = trajet->horaireDep;
	construire_tas(T,pos,d,tabSize);
	int nbS = RRInstance->nbvilles;
	while(nbS > 0) {
		int min = extraireLeMin_tas(T, d, pos, nbS);						
		nbS--;
		if(d[min] != INFINI) {
			int voisinMin[RRInstance->nblignes];
			int nbvoisin = get_voisin(RRInstance,min,voisinMin);
			for(int i = 0; i < nbvoisin; i++){
				int ligneutilise;
				int dureeTrajet  = calcul_dureeTrajet(RRInstance,d[min],min,voisinMin[i],&ligneutilise);
				if(d[voisinMin[i]] > (d[min] + dureeTrajet)){
					d[voisinMin[i]] = d[min] + dureeTrajet;
					precedent[voisinMin[i]]=min;
					ligne[voisinMin[i]]=ligneutilise;
					entasserVersLeHaut(pos[voisinMin[i]],T,pos,d,nbS);
				}
				else if (d[voisinMin[i]]==-1){
					d[voisinMin[i]] = d[min] + dureeTrajet;
					precedent[voisinMin[i]]=min;
					ligne[voisinMin[i]]=ligneutilise;
					entasserVersLeHaut(pos[voisinMin[i]],T,pos,d,nbS);
				}
			}
		}
	}
	int * result = malloc(tabSize*3*sizeof(int *));
	for (int i = 0; i < tabSize; ++i){
		result[i*3]=precedent[i];
		result[i*3+1]=d[i];
		result[i*3+2]=ligne[i];
	}
	return result;
}