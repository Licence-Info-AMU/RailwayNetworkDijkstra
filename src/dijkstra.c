#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "trace.h"
#include "tas.h"
#include "railwayNetwork.h"
#include "dijkstra.h"

#define INFINI -1
#define JOUR 1440
#define HEURE 60


int set_time(){
	int heure=-1,minute=-1;
	while (heure < 0 || heure >= 24 || minute < 0 || minute >= HEURE){
		printf("Heure de départ? (\"heure\"h\"minute\")\n");
		scanf("%dh%d",&heure,&minute);
	}
	return heure*HEURE+minute;
}

void show_trajet(Trajet * trajet){
	if (trajet->villeArr !=-1){
		printf("\n Heure de départ %dh%d\n %d -> %d \n",trajet->horaireDep/HEURE,trajet->horaireDep%HEURE,trajet->villeDep,trajet->villeArr);
	}
	else{
		printf("\n Heure de départ %dh%d\n ville de départ :%d \n",trajet->horaireDep/HEURE,trajet->horaireDep%HEURE,trajet->villeDep);
	}
}

void set_trajet_avec_arrive(Trajet * trajet){
	trajet->horaireDep = set_time();
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

void set_trajet_sans_arrive(Trajet * trajet){
	trajet->horaireDep = set_time();
	trajet->villeDep = -1;
	trajet->villeArr = -1;
	while (trajet->villeDep < 0){
		printf("Ville de départ?\n");
		scanf("%d",&trajet->villeDep);
	}
	show_trajet(trajet);
}


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
	//printf("%d %d extraire_le_min1\n",min,rankmin );
	return rankmin;
}

int calcul_dureeTrajet(RailwayNetwork * RRInstance,int heure,int villeDep, int villeArr){
 	ville * ville1 = &RRInstance->villes[villeDep], * ville2 = &RRInstance->villes[villeArr];
 	int min=-1;
 	heure=heure%JOUR;
 	for (int i = 0; i < RRInstance->nblignes; ++i){
 		int rankvilleDep = ville1->lignesInVille[i];
 		int rankvilleArr = ville2->lignesInVille[i];
		if (rankvilleDep !=-1 && rankvilleArr == rankvilleDep+1){
			ligne * ligne = &RRInstance->lignes[i];
			for (int j = 0; j < ligne->nbhoraires; ++j){
				int tmp1=ligne->horaires[rankvilleArr][j]-ligne->horaires[rankvilleDep][j];
				if (tmp1<0){
					tmp1 +=JOUR;
				}
				if (tmp1<0){
					trace("temps d'atente négatif !",__FILE__,__LINE__);
					exit(EXIT_FAILURE);
				}
				int tmp2=ligne->horaires[rankvilleDep][j]-heure;
				if (tmp2<0){
					tmp2 +=JOUR;
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
	int d[tabSize],done[tabSize],precedent[tabSize];	
	precedent[trajet->villeDep]=-1;
	if (d == NULL){
		trace("Allocation impossible de int * d",__FILE__,__LINE__ );
		exit(EXIT_FAILURE);
	}
	for(int s = 0; s < tabSize;s++){ /* on initialise les sommets autres que trajet->villeDep à infini */
		d[s] = INFINI;
		done[s] = 0;
	}
	d[trajet->villeDep] = trajet->horaireDep;

	for (int i = 0; i < tabSize; ++i){
		int min = extraire_le_min(d,done,tabSize);
		int voisinMin[RRInstance->nblignes];
		int nbvoisin = get_voisin(RRInstance,min,voisinMin);
		done[min]=1;
		
		for (int j = 0; j < nbvoisin; ++j){
			// printf(" dmin %d rmin %d rvoisin %d \n",d[min],min,voisinMin[j]);
			int dureeTrajet = calcul_dureeTrajet(RRInstance,d[min],min,voisinMin[j]);
			if (d[voisinMin[j]]==-1){
				d[voisinMin[j]]=d[min]+dureeTrajet;
				// printf("%d %d %d\n",d[voisinMin[j]],d[min],dureeTrajet);
				precedent[voisinMin[j]]=min;
			}
			else if (d[voisinMin[j]] > d[min]+dureeTrajet){
				d[voisinMin[j]]=d[min]+dureeTrajet;
				precedent[voisinMin[j]]=min;
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
	
	for (int i = 0; i < tabSize; ++i){
		result[i*2]=precedent[i];
		result[i*2+1]=d[i];
	}
	
}

int extraireLeMin_tas(int * T, int * d,int * pos, int nbS) {	//Recherche du minimum
	int min = T[0];
	nbS--;
	swap_tab_int(T,0,nbS);
	swap_tab_int(pos,T[0],T[nbS]);
	entasserVersLeBas(pos[T[0]],T,pos,d,nbS);
	return min;
}


void dijkstra_tas(RailwayNetwork * RRInstance,Trajet * trajet, int * result){
	int tabSize=RRInstance->nbvilles;
	int T[tabSize], d[tabSize], pos[tabSize],precedent[tabSize];
	for(int s = 0; s < tabSize;s++){ 								// on initialise les s (sommets) autres que villeDepart à infini 
		d[s] = INFINI;
		T[s] = s;
		pos[s] = s;
		precedent[s]=-1;
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
				int dureeTrajet  = calcul_dureeTrajet(RRInstance,d[min],min,voisinMin[i]);
				if(d[voisinMin[i]] > (d[min] + dureeTrajet)){
					d[voisinMin[i]] = d[min] + dureeTrajet;
					precedent[voisinMin[i]]=min;
					entasserVersLeHaut(pos[voisinMin[i]],T,pos,d,nbS);
				}
				else if (d[voisinMin[i]]==-1){
					d[voisinMin[i]] = d[min] + dureeTrajet;
					precedent[voisinMin[i]]=min;
					entasserVersLeHaut(pos[voisinMin[i]],T,pos,d,nbS);
				}
			}
		}
	}
	for (int i = 0; i < tabSize; ++i){
		result[i*2]=precedent[i];
		result[i*2+1]=d[i];
	}
}

void Affichage_result_mono_trajet(Trajet * trajet,int *result){
	int dep=trajet->villeDep,arr=trajet->villeArr;
	printf("\n\t\t%d -> %d \n",dep,arr);
	int dureeTrajet=result[arr*2+1]-trajet->horaireDep;
	if (dureeTrajet >-1){
		char tmp[30]="";
		if (dureeTrajet > JOUR){
			sprintf(tmp,"%d Jour(s) ",dureeTrajet/JOUR);
			dureeTrajet=dureeTrajet%JOUR;
		}
		if (dureeTrajet > HEURE){
			sprintf(tmp,"%s%d Heure(s) ",tmp,dureeTrajet/HEURE);
			dureeTrajet=dureeTrajet%HEURE;
		}
		sprintf(tmp,"%s%d Minute(s)",tmp,dureeTrajet);
		printf("Durée du trajet : %s\n",tmp);
		char numeroville[30],horaires[30];
		int villecourante=arr;

		sprintf(numeroville,"%d\t",villecourante);
		sprintf(horaires,"%dh%d\t",result[villecourante*2+1]/HEURE,result[villecourante*2+1]%HEURE);
		villecourante=result[villecourante*2];
		while(villecourante!=-1){
			sprintf(tmp,"%s",numeroville);
			sprintf(numeroville,"%d\t->%s",villecourante,tmp);
			sprintf(tmp,"%s",horaires);
			sprintf(horaires,"%dh%d\t->%s",result[villecourante*2+1]/HEURE,result[villecourante*2+1]%HEURE,tmp);
			villecourante=result[villecourante*2];
		}
		printf("%s\n%s\n",numeroville,horaires);
	}
	else{
		if (result[arr*2+1]==-1){
			printf("ville non atteignable !\n");
		}
		else{
			trace("WTF ! dureeTrajet négatif",__FILE__,__LINE__);
		}
	}
}

void Affichage_result_multi_trajet(Trajet * trajet,int *result,int tabSize){
	for (int i = 0; i < tabSize; ++i){
		if(i!= trajet->villeDep){
			trajet->villeArr=i;
			Affichage_result_mono_trajet(trajet,result);
		}
	}
}