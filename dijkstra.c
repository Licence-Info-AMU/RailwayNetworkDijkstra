#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>

#define INFINI 99999999
int * d;

void define_lignesInVille(RR * RRInstance){
	int numeroslignetmp[RRInstance->nblignes];
	int ranksvilletmp[RRInstance->nblignes];
	for (int i = 0; i < RRInstance->nbvilles; ++i){
		RRInstance->villes[i].nblignesInVille=0;
		for (int j = 0; j < RRInstance->nblignes; ++j){
			for (int k = 0; k < RRInstance->lignes[j].nbvilles; ++k){
				if (RRInstance->lignes[j].villesInLigne[k]==i){
					numeroslignetmp[RRInstance->villes[i].nblignesInVille]=j;
					ranksvilletmp[RRInstance->villes[i].nblignesInVille]=k;
					RRInstance->villes[i].nblignesInVille++;
				}
			}
		}
		RRInstance->villes[i].lignesInVille=malloc(sizeof(lignesInVille) * RRInstance->villes[i].nblignesInVille);
		for (int j = 0; j < RRInstance->villes[i].nblignesInVille; ++j){
			RRInstance->villes[i].lignesInVille[j].numeroligne=numeroslignetmp[j];
			RRInstance->villes[i].lignesInVille[j].rankville=ranksvilletmp[j];
		}		
	}
}

void show_lignesInVille(RR * RRInstance){
	char numeroligne[50+4*RRInstance->nblignes],rankville[50+4*RRInstance->nblignes];
	for (int i = 0; i < RRInstance->nbvilles; ++i){
		printf("La ville %d a %d lignes :\n", i,RRInstance->villes[i].nblignesInVille);
		sprintf(numeroligne,"Numéro des lignes : \n");
		sprintf(rankville,	"Rank de la ville %d : \n",i);
		for (int j = 0; j < RRInstance->villes[i].nblignesInVille; ++j){
			sprintf(numeroligne,"%s%d\t",numeroligne,RRInstance->villes[i].lignesInVille[j].numeroligne);
			sprintf(rankville,"%s%d\t",rankville,RRInstance->villes[i].lignesInVille[j].rankville);
		}
		printf("%s \n%s \n",numeroligne,rankville);
		printf("______________________________________________ \n\n");
	}
}
/*																	//plus long que la version 2
void get_voisin1(RR * RRInstance,int nomville,int * voisins){ 		//voisin doit etre de la taille nbvilles
	int j=0;
	int i=0;
	while (i < RRInstance->villes[nomville].nblignesInVille){
		int numeroligne=RRInstance->villes[nomville].lignesInVille[i].numeroligne;
		int rankville=RRInstance->villes[nomville].lignesInVille[i].rankville;
		if (rankville < RRInstance->lignes[numeroligne].nbvilles-1){
			voisins[j]=RRInstance->lignes[numeroligne].villesInLigne[rankville+1];
			++j;
		}
		++i;
	}
	while (j < RRInstance->nblignes){													//no need if show_voisin2
		voisins[j]=-1;																	//no need if show_voisin2
		++j;																			//no need if show_voisin2
	}																					//no need if show_voisin2
}

void show_voisins1(RR * RRInstance,int nomville){
	int tab[RRInstance->nblignes];
	get_voisin1(RRInstance,nomville,tab);
	//printf("La ville %d a les voisins : ",nomville);
	for (int i = 0; i < RRInstance->nblignes ; ++i){
		if (tab[i]!=-1){
			//printf("%d\t",tab[i] );
		}
	}
	//printf("\n");
}
*/

int get_voisin(RR * RRInstance,int nomville,int * voisins){ 		//voisin doit etre de la taille nbvilles
	int j=0;
	int i=0;
	while (i < RRInstance->villes[nomville].nblignesInVille){
		int numeroligne=RRInstance->villes[nomville].lignesInVille[i].numeroligne;
		int rankville=RRInstance->villes[nomville].lignesInVille[i].rankville;
		if (rankville < RRInstance->lignes[numeroligne].nbvilles-1){
			voisins[j]=RRInstance->lignes[numeroligne].villesInLigne[rankville+1];
			++j;
		}
		++i;
	}
	return j;
}

void show_voisins(RR * RRInstance,int nomville){
	int tab[RRInstance->nblignes];
	int nbvoisins=get_voisin(RRInstance,nomville,tab);
	printf("La ville %d a les voisins : ",nomville);
	for (int i = 0; i < nbvoisins ; ++i){
		printf("%d ",tab[i]);
	}
	printf("\n");
}

/*
void show_voisins2(RR * RRInstance,int nomville){
	int tab[RRInstance->nblignes];
	int nbvoisins=get_voisin(RRInstance,nomville,tab);
	char str[25];
	sprintf(str,"La ville %d a les voisins : ",nomville);
	for (int i = 0; i < nbvoisins ; ++i){
		sprintf(str,"%s%d ",str,tab[i]);
	}
	printf("%s \n",str);
}
*/

void init_d(int tabSize){
	d = malloc (sizeof(int) * tabSize);
	if (d == NULL){
		trace("Allocation impossible de int * d",__FILE__,__LINE__ );
		exit(EXIT_FAILURE);
	}
}

void init_Dijkstra(RR * RRInstance,int sdeb){
	init_d(RRInstance->nbvilles);
	for(int s = 0; s < RRInstance->nbvilles;s++){ /* on initialise les sommets autres que sdeb à infini */
		d[s] = INFINI;
	}
	d[sdeb] = 0;
}

/*
int ** Dijkstra(RR * RRInstance,int sdeb, int h_deb){
	init_Dijkstra(RRInstance,sdeb);
	
	while(){ 
	
	}
	return d;
}
*/