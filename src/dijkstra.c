#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "trace.h"
#include "tas.h"
#include "railwayNetwork.h"
#include "dijkstra.h"

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
int set_time2(){
	int heure=-1,minute=-1;
	while (heure < 0 || heure >= 24 || minute < 0 || minute >= 60){
		printf("heure de départ? (\"heure\"h\"minute\")\n");
		scanf("%dh%d",&heure,&minute);
	}
	return heure*60+minute;
}

void show_trajet(Trajet * trajet){
	printf("\n Heure de départ %dh%d\n %d -> %d \n",trajet->horaireDep/60,trajet->horaireDep%60,trajet->villeDep,trajet->villeArr);
}

void set_trajet(Trajet * trajet){
	trajet->horaireDep = set_time2();
	trajet->villeDep = -1;
	trajet->villeArr = -1;
	while (trajet->villeDep < 0){
		printf("Ville de départ?\n");
		scanf("%d",&trajet->villeDep);
	}
	while (trajet->villeArr < 0){
		printf("Ville d'arrivée?\n");
		scanf("%d",&trajet->villeArr);
	}
	show_trajet(trajet);
}


int extraire_le_min1(int * duree,int * done,int tabSize){
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
	//printf("%d %d extraire_le_min1\n",min,rankmin );
	return rankmin;
}

int calcul_dureeTrajet(RailwayNetwork * RRInstance,int heure,int villeDep, int villeArr){
 	ville * ville1 = &RRInstance->villes[villeDep], * ville2 = &RRInstance->villes[villeArr];
 	int min=-1;
 	heure=heure%1440;
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
				if (tmp1<0){
					trace("temps d'atente négatif !",__FILE__,__LINE__);
					exit(EXIT_FAILURE);
				}
				int tmp2=ligne->horaires[rankvilleDep][j]-heure;
				if (tmp2<0){
					tmp2 +=1440;
				}
				if (tmp2<0){
					trace("temps trajet négatif !",__FILE__,__LINE__);
					exit(EXIT_FAILURE);
				}
				int tmp=tmp1+tmp2;
				if (tmp<0){
					trace("temps total négatif !",__FILE__,__LINE__);
					exit(EXIT_FAILURE);
				}
				if(min==-1){
					min=tmp;
				}
				else if(tmp < min){
					min=tmp;
				}
			}
		}
	}
	if (min < 0){
		trace("min negatif ! ville inaccessible ?",__FILE__,__LINE__);
	}
	return min;
}

void dijkstra(RailwayNetwork * RRInstance,Trajet * trajet, int * result){
	int tabSize=RRInstance->nbvilles;
	int duree[tabSize],done[tabSize],precedent[tabSize];	
	precedent[trajet->villeDep]=-1;
	if (duree == NULL){
		trace("Allocation impossible de int * duree",__FILE__,__LINE__ );
		exit(EXIT_FAILURE);
	}
	for(int s = 0; s < tabSize;s++){ /* on initialise les sommets autres que trajet->villeDep à infini */
		duree[s] = INFINI;
		done[s] = 0;
	}
	duree[trajet->villeDep] = trajet->horaireDep;

	for (int i = 0; i < tabSize; ++i){
		int min = extraire_le_min1(duree,done,tabSize);
		int voisinMin[RRInstance->nblignes];
		int nbvoisin = get_voisin(RRInstance,min,voisinMin);
		done[min]=1;
		
		for (int j = 0; j < nbvoisin; ++j){
			// printf(" dmin %d rmin %d rvoisin %d \n",duree[min],min,voisinMin[j]);
			int dureeTrajet = calcul_dureeTrajet(RRInstance,duree[min],min,voisinMin[j]);
			if (duree[voisinMin[j]]==-1){
				duree[voisinMin[j]]=duree[min]+dureeTrajet;
				// printf("%d %d %d\n",duree[voisinMin[j]],duree[min],dureeTrajet);
				precedent[voisinMin[j]]=min;
			}
			else if (duree[voisinMin[j]] > duree[min]+dureeTrajet){
				duree[voisinMin[j]]=duree[min]+dureeTrajet;
				precedent[voisinMin[j]]=min;
			}
		}
	}
	int tmp;
	result[tabSize]=duree[trajet->villeArr]-trajet->horaireDep;
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

void init_Dijkstra(RailwayNetwork * RRInstance,int villeDepart,int *F, int *d,int *pos){
	init_Tabs(F, d, pos,RRInstance->nbvilles);
	for(int s = 0; s < RRInstance->nbvilles;s++){ // on initialise les sommets autres que villeDepart à infini 
		d[s] = INFINI;
		F[s] = s;
		pos[s] = s;
	}
	d[villeDepart] = 0;
}

int Dijkstra_tas(int villeDepart, int villeArrivee,int nbre_S, int h_deb,RailwayNetwork * RRInstance){
	int *F, *d, *pos;
	int heureActuelle = h_deb;
	int nbS = nbre_S;
	listeItineraire listeI = NULL;
	init_Dijkstra(RRInstance,nbre_S,F, d, pos);
	construire_tas(F,pos,d,nbS);
	while(nbS > 0) {
        int u = ExtraireLeMin(F, d, pos, nbS);
        nbS--;
        if(d[u] != INFINI) {
			if(u != villeDepart) {		// l'heure d'arrivée à une ville est le temps de trajet entre la ville de départ et cette ville + l'heure du début
				if(d[u] + h_deb >= 1440)		//reset pour chaque journée passée
					heureActuelle = d[u] + h_deb - 1440;
				else 
					heureActuelle = d[u] + h_deb;
			}
			int voisinMin[RRInstance->nblignes];
			int nbvoisin = get_voisin(RRInstance,u,voisinMin);
			for(int i = 0; i < nbvoisin; i++) {
				//int trajetCourt = ??;
				
				// if(d[voisinMin[i]] > (d[u] + trajetCourt)) {
				// 	d[voisinMin[i]] = d[u] + trajetCourt;
				// 	entasserVersLeHaut(pos[voisinMin[i]],F,pos,d,nbS);
				// }

			}
			free(voisinMin);
		}
		// ToDo Mettre à jour liste
	}
	return d[villeArrivee];
}
