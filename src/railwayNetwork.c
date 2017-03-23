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
			ligne * ligne = &RRInstance->lignes[nligne];
			if(fgets ( line, sizeof(line), file ) != NULL){			//nombre de villes dans la première ligne
				ligne->nbvillesInLigne=atoi(line);
				ligne->villesInLigne=malloc(sizeof(int) * ligne->nbvillesInLigne);
			}
			else{
				trace ("Bad file",__FILE__,__LINE__ );
			}
			if(fgets ( line, sizeof(line), file ) != NULL){			//villes de la première ligne
				ligne->villesInLigne[0]=atoi(strtok(line," "));						//version propre
				for (int i = 1; i < ligne->nbvillesInLigne; ++i){
					ligne->villesInLigne[i]=atoi(strtok(NULL," "));
				}

				// char *tmp=line;
				// for (int i = 0; i < ligne->nbvillesInLigne; ++i){			//version je fait a ma façon
				// 	ligne->villesInLigne[i]=atoi(tmp);
				// 	tmp=skip_separator(tmp,' ');
				// }
			}
			else{
				trace ("Bad file",__FILE__,__LINE__ );
			}

			if(fgets ( line, sizeof(line), file ) != NULL){			//nb horaires de la ligne
				ligne->nbhoraires=atoi(line);
				ligne->horaires=malloc(sizeof(int *) * ligne->nbvillesInLigne);			//peut etre swap les ordonée absices du tableau?
				for (int j = 0; j < ligne->nbvillesInLigne ; ++j)
				{
					ligne->horaires[j]=malloc(sizeof(int *) * ligne->nbhoraires);
				}
					
				
			}
			else{
				trace ("Bad file",__FILE__,__LINE__ );
			}

			for (int i = 0; i < ligne->nbhoraires ; ++i)
			{
				if(fgets ( line, sizeof(line), file ) != NULL){		//horaires
					ligne->horaires[0][i]=atoi(strtok(line," h"))*60 +atoi(strtok(NULL," h"));

					for (int j = 1; j < ligne->nbvillesInLigne; ++j){
						ligne->horaires[j][i]=atoi(strtok(NULL," h"))*60+atoi(strtok(NULL," h"));
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
	for (int i = 0; i < RRInstance->nbvilles; ++i){
		ville * ville = &RRInstance->villes[i];
		ville->lignesInVille=malloc(sizeof(int) * RRInstance->nblignes);
		ville->nblignesInVille=0;
		for (int j = 0; j < RRInstance->nblignes; ++j){
			ligne * ligne = &RRInstance->lignes[j];
			ville->lignesInVille[j]=-1;
			for (int k = 0; k < ligne->nbvillesInLigne; ++k){
				if (ligne->villesInLigne[k]==i){
					ville->lignesInVille[j]=k;
					ville->nblignesInVille++;
				}
			}
		}	
	}
}

int get_voisin(RailwayNetwork * RRInstance,int nomville,int * voisins){ 		//voisins doit etre de la taille nbligne
	ville * ville = &RRInstance->villes[nomville];
	int j=0;
	for (int i = 0; i < RRInstance->nblignes; ++i){
		ligne * ligne = &RRInstance->lignes[i];
		int rankville = ville->lignesInVille[i];
		int voisin = ligne->villesInLigne[rankville+1];
		if (rankville >=0 && rankville < ligne->nbvillesInLigne-1){
			int alreadyinvoisins=0;
			for (int k = 0; k < j && alreadyinvoisins==0; ++k){
				if (voisin==voisins[k]){
					alreadyinvoisins=1;
				}
			}
			if (alreadyinvoisins==0){
				voisins[j]=voisin;
				++j;
			}
		}
	}
	return j;
}

void show_RR(RailwayNetwork * RRInstance){
	printf("%i\n",RRInstance->nbvilles );										//show nbvilles
	for (int i = 0; i < RRInstance->nbvilles; ++i){								//show coordonée ville
		printf("%i",RRInstance->villes[i].x);
		printf("\t%i\n",RRInstance->villes[i].y);
	}
	printf("%i\n",RRInstance->nblignes);										//show nb ligne
	for (int nligne = 0; nligne < RRInstance->nblignes; ++nligne){				//show ligne
		ligne * ligne = &RRInstance->lignes[nligne];
		printf("%i\n",ligne->nbvillesInLigne);				//show nbvillesInLigne
		for (int i = 0; i < ligne->nbvillesInLigne; ++i){	//show villes in ligne
			printf("%i\t",ligne->villesInLigne[i]);
		}
		printf("\n");
		printf("%i\n",ligne->nbhoraires);					//show nbhoraires
		for (int i = 0; i < ligne->nbhoraires; ++i)			//show horraire
		{
			for (int j = 0; j < ligne->nbvillesInLigne; ++j)
			{
				printf("%i\t",ligne->horaires[j][i]);
			}
			printf("\n");
		}
	}
}

void show_lignesInVille(RailwayNetwork * RRInstance){
	for (int i = 0; i < RRInstance->nbvilles; ++i){
		ville * ville = &RRInstance->villes[i];
		printf("La ville %d a %d lignes :\n", i,ville->nblignesInVille);
		printf("Numéro des lignes : \n");
		for (int j = 0; j < RRInstance->nblignes; ++j){
			if (ville->lignesInVille[j] != -1){
				printf("%d\t",j);
			}
		}
		printf("\nRank de la ville %d : \n",i);
		for (int j = 0; j < RRInstance->nblignes; ++j){
			if (ville->lignesInVille[j] != -1){
				printf("%d\t",ville->lignesInVille[j]);
			}
		}
		printf("\n______________________________________________ \n\n");
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
