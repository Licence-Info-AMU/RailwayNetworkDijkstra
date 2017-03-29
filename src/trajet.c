#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "trajet.h"

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

void trajet_inverse(Trajet * trajet){
	int tmp = trajet->villeDep;
	trajet->villeDep = trajet->villeArr;
	trajet->villeArr = tmp;
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

void set_trajet_user(RailwayNetwork * RRInstance,Trajet * trajet){
	int test=0;
	printf("voulez vous définir une ville d'arrivée ? (OUI:1/NON:0)\n");
	scanf("%d",&test);
	if (test==1){
		set_trajet_avec_arrive(trajet);
		if (trajet->villeDep > RRInstance->nbvilles || trajet->villeArr > RRInstance->nbvilles){
			trace("ville du trajet incorrect !",__FILE__,__LINE__);
			exit(EXIT_FAILURE);
		}
	}
	if (test==0){
		set_trajet_sans_arrive(trajet);
		if (trajet->villeDep > RRInstance->nbvilles){
			trace("ville de départ incorrect !",__FILE__,__LINE__);
			exit(EXIT_FAILURE);
		}
	}
}

int calcul_dureeTrajet(RailwayNetwork * RRInstance,int heure,int villeDep, int villeArr, int * ligneutilise){
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
					*ligneutilise=i;
				}
				else if(tmp < min){
					min=tmp;
					*ligneutilise=i;
				}
			}
		}
	}
	if (min < 0){
		trace("min negatif ! ville inaccessible et voisin mal défini?",__FILE__,__LINE__);
	}
	return min;
}

void Affichage_result_mono_trajet(Trajet * trajet,int result[]){
	int dep=trajet->villeDep,arr=trajet->villeArr;
	printf("\n\t\t%d -> %d \n",dep,arr);
	int dureeTrajet=result[arr*3+1]-trajet->horaireDep;
	if (dureeTrajet >-1){
		char tmp[50]="";
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
		char numeroville[50],horaires[50],lignes[50];
		int villecourante=arr;

		sprintf(numeroville,"%d\t",villecourante);
		sprintf(horaires,"%dh%d\t",result[villecourante*3+1]/HEURE,result[villecourante*3+1]%HEURE);
		sprintf(lignes,"     %d",result[villecourante*3+2]);
		//printf("\n%d",result[villecourante*3+2]);
		villecourante=result[villecourante*3];
		while(villecourante!=-1){
			sprintf(tmp,"%s",numeroville);
			sprintf(numeroville,"%d\t->%s",villecourante,tmp);
			sprintf(tmp,"%s",horaires);
			sprintf(horaires,"%dh%d\t->%s",result[villecourante*3+1]/HEURE,result[villecourante*3+1]%HEURE,tmp);
			//printf("%d",result[villecourante*3+2]);
			if(result[villecourante*3+2] != -1){
				sprintf(tmp,"%s",lignes);
				sprintf(lignes,"     %d\t%s",result[villecourante*3+2],tmp);
			}

			villecourante=result[villecourante*3];
		}
		printf("%s\n",numeroville );
		printf("%s\n",horaires );
		printf("%s\n",lignes );
	}
	else{
		if (result[arr*3+1]==-1){
			printf("ville non atteignable !\n");
		}
		else{
			trace("WTF ! dureeTrajet négatif",__FILE__,__LINE__);
		}
	}
}

void Affichage_result_multi_trajet(Trajet * trajet,int result[],int tabSize){
	for (int i = 0; i < tabSize; ++i){
		if(i!= trajet->villeDep){
			trajet->villeArr=i;
			Affichage_result_mono_trajet(trajet,result);
		}
	}
	printf("\n");
}