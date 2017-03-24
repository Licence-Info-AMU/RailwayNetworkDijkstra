#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "trace.h"
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
