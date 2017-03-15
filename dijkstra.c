#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "trace.h"
#include "dijkstra.h"
#include "railwayNetwork.h"

#define INFINI -1

int set_time(){
	int heure=-1,minute=-1;
	while (heure < 0 || heure >= 24){
		printf("heure de départ?\n");
		scanf("%d",&heure);
	}
	while (minute < 0 || minute >= 60){
		printf("minute de départ?\n");
		scanf("%d",&minute);
	}
	return heure*60+minute;
}

void show_trajet(Trajet * trajet){
	printf("\n Heure de départ %d:%d\n %d -> %d \n",trajet->horaireDep/60,trajet->horaireDep%60,trajet->villeDep,trajet->villeArr);
}

void set_trajet(Trajet * trajet){
	trajet->horaireDep = set_time();
	printf("Ville de départ?\n");
	scanf("%d",&trajet->villeDep);
	printf("Ville de arrivée?\n");
	scanf("%d",&trajet->villeArr);
	show_trajet(trajet);
}


int extraire_le_min1(int * d,int * t,int tabSize){
	int min=-1,rankmin=-1;
	for (int i = 0; i < tabSize; ++i){
		if(t[i] == 0 && d[i]>0){
			if(min==-1){
				min=d[i];
				if (min != -1){
					rankmin=i;
				}
			}
			else if(min > d[i]){
				min=d[i];
				rankmin=i;
			}	
		}
	}
	printf("%d %d extraire_le_min1\n",min,rankmin );
	return rankmin;
}

int calcul_dureeTrajet(RailwayNetwork * RRInstance,int heure,int villeDep, int villeArr){
 	ville * ville1 = &RRInstance->villes[villeDep], * ville2 = &RRInstance->villes[villeArr];
 	int min=-1;
 	while (heure >=1440){
 		heure -= 1440;
 	}
 	for (int i = 0; i < RRInstance->nblignes; ++i){
 		int rankvilleDep = ville1->lignesInVille[i];
 		int rankvilleArr = ville2->lignesInVille[i];
		if (rankvilleDep !=-1 && rankvilleArr == rankvilleDep+1){
			ligne * ligne = &RRInstance->lignes[i];
			for (int j = 0; j < ligne->nbhoraires; ++j){
				int tmp1=ligne->horaires[rankvilleArr][j]-ligne->horaires[rankvilleDep][j];
				if (tmp1<0){
					tmp1 +=1440;
				}
				int tmp2=ligne->horaires[rankvilleDep][j]-heure;
				if (tmp2<0){
					tmp2 +=1440;
				}
				int tmp=tmp1+tmp2;
				if(min==-1){
					min=tmp;
				}
				else if(tmp < min){
					min=tmp;
				}
			}
		}
	}
	return min;
}

void dijkstra(RailwayNetwork * RRInstance,Trajet * trajet, int * result){
	int tabSize=RRInstance->nbvilles;
	int d[tabSize],t[tabSize],precedent[tabSize];	
	precedent[trajet->villeDep]=-1;
	if (d == NULL){
		trace("Allocation impossible de int * d",__FILE__,__LINE__ );
		exit(EXIT_FAILURE);
	}
	for(int s = 0; s < tabSize;s++){ /* on initialise les sommets autres que trajet->villeDep à infini */
		d[s] = INFINI;
		t[s] = 0;
	}
	d[trajet->villeDep] = trajet->horaireDep;

	for (int i = 0; i < tabSize; ++i){
		int min = extraire_le_min1(d,t,tabSize);
		int voisinMin[RRInstance->nblignes];
		int nbvoisin = get_voisin(RRInstance,min,voisinMin);
		t[min]=1;
		
		for (int j = 0; j < nbvoisin; ++j){
			printf(" dmin %d min %d j %d \n",d[min],min,voisinMin[j]);
			int dureeTrajet = calcul_dureeTrajet(RRInstance,d[min],min,voisinMin[j]);
			if (d[voisinMin[j]]==-1){
				d[voisinMin[j]]=d[min]+dureeTrajet;
				printf("%d %d %d\n",d[voisinMin[j]],d[min],dureeTrajet);
				precedent[voisinMin[j]]=min;
			}
			else if (d[voisinMin[j]] > d[min]+dureeTrajet){
				d[voisinMin[j]]=d[min]+dureeTrajet;
				precedent[voisinMin[j]]=min;
			}
		}
	}
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
}

int ExtraireLeMin(int * F, int * d,int * pos, int nbS) {	//Recherche du minimum
    int min = F[0];
    swap_tab_int(F,0,nbS-1);
    swap_tab_int(pos,F[0],F[nbS-1]);
    nbS--;
    entasserVersLeBas(pos[F[0]],F,pos,d,nbS);
    return min;
}

void init_Tabs(int *F, int *d, int *pos,int tabSize){
	create_Tab_Int(F,tabSize);
	create_Tab_Int(d,tabSize);
	create_Tab_Int(pos,tabSize);
}

void init_Dijkstra(RR * RRInstance,int villeDepart,int *F, int *d,int *pos){
	init_Tabs(F, d, pos,RRInstance->nbvilles);
	for(int s = 0; s < RRInstance->nbvilles;s++){ /* on initialise les sommets autres que villeDepart à infini */
		d[s] = INFINI;
		F[s] = s;
		pos[s] = s;
	}
	}
	d[villeDepart] = 0;
}

int Dijkstra_tas(int villeDepart, int villeArrivee,int nbre_S, int h_deb,RR * RRInstance){
	int *F, *d, *pos;
	int heureActuelle = h_deb;
	int nbS = nbre_S;
	listeItineraire listeI = NULL;
	init_Dijkstra(RRInstance,sdeb,F, d, pos);
	construire_tas(F,pos,d,nbS);
	while(nbS > 0) {
        int u = ExtraireLeMin(F, d, pos, nbS);
        nbS--;
        if(d[u] != INFINI) {
			if(u != villeDepart) {		// l'heure d'arrivée à une ville est le temps de trajet entre la ville de départ et cette ville + l'heure du début
				if(d[u] + heureDebut >= 1440)		//reset pour chaque journée passée
					heureActuelle = d[u] + heureDebut - 1440;
				else 
					heureActuelle = d[u] + heureDebut;
			}
			int voisinMin[RRInstance->nblignes];
			int nbvoisin = get_voisin(RRInstance,min,voisinMin);
			for(int i = 0; i < tailleVoisins; i++) {
				//int trajetCourt = ??;
				if(d[voisinMin[i]] > (d[u] + trajetCourt)) {
					d[voisinMin[i]] = d[u] + trajetCourt;
					entasserVersLeHaut(pos[voisinMin[i]],F,pos,d,nbS);
				}
			}
			free(voisins);
		}
		// ToDo Mettre à jour liste
	}
	return d[villeArrivee];
}
