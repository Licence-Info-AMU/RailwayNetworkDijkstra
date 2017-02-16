#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "railwayNetwork.h"
#include "util.h"
#include "trace.h"

void railwayNetwork(char * filename ,RailwayNetwork *RRInstance){
	read_File(filename,RRInstance);
	define_lignesInVille(RRInstance);
}

void read_File(char * filename ,RailwayNetwork *RRInstance){
	RRInstance->nbvilles=0;
	FILE *file = fopen ( filename, "r" );
	
	if ( file != NULL ){
		char line [128];
		if ( fgets (line, sizeof(line), file ) != NULL ){			//nombre de ville
			RRInstance->nbvilles=atoi(line);
			RRInstance->villes=malloc(sizeof(ville)* RRInstance->nbvilles );
		}
		else{
			trace ("Bad file",__FILE__,__LINE__ );
		}

		for (int i = 0; i <RRInstance->nbvilles ; ++i)						//coordonnées des villes
		{
			if ( fgets ( line, sizeof(line), file ) != NULL ){
				RRInstance->villes[i].x=atoi(strtok(line," "));					//version propre
				RRInstance->villes[i].y=atoi(strtok(NULL," "));

				// RRInstance->villes[i].x=atoi(line);							//version je fais à ma façon
				// RRInstance->villes[i].y=atoi(skip_separator(line,' '));
			}
			else{
				trace ("Bad file",__FILE__,__LINE__ );
			}

		}

		if ( fgets ( line, sizeof(line), file ) != NULL ){			//nombre de lignes
			RRInstance->nblignes=atoi(line);
			RRInstance->lignes=malloc(sizeof(ligne) * RRInstance->nblignes);
		}
		else{
			trace ("Bad file",__FILE__,__LINE__ );
		}
		for (int nligne = 0; nligne < RRInstance->nblignes; ++nligne)
		{
			if(fgets ( line, sizeof(line), file ) != NULL){			//nombre de villes dans la première ligne
				RRInstance->lignes[nligne].nbvillesInLigne=atoi(line);
				RRInstance->lignes[nligne].villesInLigne=malloc(sizeof(int) * RRInstance->lignes[nligne].nbvillesInLigne);
			}
			else{
				trace ("Bad file",__FILE__,__LINE__ );
			}
			if(fgets ( line, sizeof(line), file ) != NULL){			//villes de la première ligne
				RRInstance->lignes[nligne].villesInLigne[0]=atoi(strtok(line," "));			//version propre
				for (int i = 1; i < RRInstance->lignes[nligne].nbvillesInLigne; ++i){
					RRInstance->lignes[nligne].villesInLigne[i]=atoi(strtok(NULL," "));
				}

				// char *tmp=line;
				// for (int i = 0; i < RRInstance->lignes[nligne].nbvillesInLigne; ++i){			//version je fait a ma façon
				// 	RRInstance->lignes[nligne].villesInLigne[i]=atoi(tmp);
				// 	tmp=skip_separator(tmp,' ');
				// }
			}
			else{
				trace ("Bad file",__FILE__,__LINE__ );
			}

			if(fgets ( line, sizeof(line), file ) != NULL){			//nb horaires de la ligne
				RRInstance->lignes[nligne].nbhoraires=atoi(line);
				RRInstance->lignes[nligne].horaires=malloc(sizeof(int *) * RRInstance->lignes[nligne].nbvillesInLigne);			//peut etre swap les ordonée absices du tableau?
				for (int j = 0; j < RRInstance->lignes[nligne].nbvillesInLigne ; ++j)
				{
					RRInstance->lignes[nligne].horaires[j]=malloc(sizeof(int *) * RRInstance->lignes[nligne].nbhoraires);
				}
					
				
			}
			else{
				trace ("Bad file",__FILE__,__LINE__ );
			}

			for (int i = 0; i < RRInstance->lignes[nligne].nbhoraires ; ++i)
			{
				if(fgets ( line, sizeof(line), file ) != NULL){		//horaires
					RRInstance->lignes[nligne].horaires[0][i]=atoi(strtok(line," h"))*60 +atoi(strtok(NULL," h"));

					for (int j = 1; j < RRInstance->lignes[nligne].nbvillesInLigne; ++j){
						RRInstance->lignes[nligne].horaires[j][i]=atoi(strtok(NULL," h"))*60+atoi(strtok(NULL," h"));
					}
				}
				else{
					trace ("Bad file",__FILE__,__LINE__ );
				}
			}
		}
		fclose ( file );
	}
	else{
		trace ("No such file or directory",__FILE__,__LINE__ );
	}
}

void define_lignesInVille(RailwayNetwork * RRInstance){
	int numeroslignetmp[RRInstance->nblignes];
	int ranksvilletmp[RRInstance->nblignes];
	for (int i = 0; i < RRInstance->nbvilles; ++i){
		RRInstance->villes[i].nblignesInVille=0;
		for (int j = 0; j < RRInstance->nblignes; ++j){
			for (int k = 0; k < RRInstance->lignes[j].nbvillesInLigne; ++k){
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

int get_voisin(RailwayNetwork * RRInstance,int nomville,int * voisins){ 		//voisin doit etre de la taille nbligne
	int j=0;
	int i=0;
	while (i < RRInstance->villes[nomville].nblignesInVille){
		int numeroligne=RRInstance->villes[nomville].lignesInVille[i].numeroligne;
		int rankville=RRInstance->villes[nomville].lignesInVille[i].rankville;
		if (rankville < RRInstance->lignes[numeroligne].nbvillesInLigne-1){
			voisins[j]=RRInstance->lignes[numeroligne].villesInLigne[rankville+1];
			++j;
		}
		++i;
	}
	return j;
}

void show_RR(RailwayNetwork * RRInstance){
	int test=1;
	printf("afficher les valeurs lue ? (OUI:1/NON:0)\n");
	//scanf("%d",&test);
	if (test==1){
		printf("%i\n",RRInstance->nbvilles );										//show nbvilles
		for (int i = 0; i < RRInstance->nbvilles; ++i){								//show coordonée ville
			printf("%i",RRInstance->villes[i].x);
			printf(" %i\n",RRInstance->villes[i].y);
		}
		printf("%i\n",RRInstance->nblignes);										//show nb ligne
		for (int nligne = 0; nligne < RRInstance->nblignes; ++nligne){				//show ligne
			printf("%i\n",RRInstance->lignes[nligne].nbvillesInLigne);				//show nbvillesInLigne
			for (int i = 0; i < RRInstance->lignes[nligne].nbvillesInLigne; ++i){	//show villes in ligne
				printf("%i ",RRInstance->lignes[nligne].villesInLigne[i]);
			}
			printf("\n");
			printf("%i\n",RRInstance->lignes[nligne].nbhoraires);					//show nbhoraires
			for (int i = 0; i < RRInstance->lignes[nligne].nbhoraires; ++i)			//show horraire
			{
				for (int j = 0; j < RRInstance->lignes[nligne].nbvillesInLigne; ++j)
				{
					printf("%i ",RRInstance->lignes[nligne].horaires[j][i]);
				}
				printf("\n");
			}
		}
	}
}

void show_lignesInVille(RailwayNetwork * RRInstance){
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

void show_voisin(RailwayNetwork * RRInstance,int nomville){
	int tab[RRInstance->nblignes];
	int nbvoisins=get_voisin(RRInstance,nomville,tab);
	printf("La ville %d a les voisins : ",nomville);
	for (int i = 0; i < nbvoisins ; ++i){
		printf("%d ",tab[i]);
	}
	printf("\n");
}

void show_voisins(RailwayNetwork * RRInstance){
	for (int i = 0; i < RRInstance->nbvilles; ++i){
		show_voisin(RRInstance,i);
	}
}
