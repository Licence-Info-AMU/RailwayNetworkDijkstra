#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "util.h"
#include "trace.h"
#include <assert.h>

void read_file(char * filename ,RR *RRInstance){
	RRInstance->nbvilles=0;
	FILE *file = fopen ( filename, "r" );
	
	if ( file != NULL ){

		char line [128];
		// char *line =malloc(sizeof(char)*128);
		// assert(line!=NULL);

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

				// RRInstance->villes[i].x=atoi(line);							//version je fait a ma façon
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
				RRInstance->lignes[nligne].nbvilles=atoi(line);
				RRInstance->lignes[nligne].villesInLigne=malloc(sizeof(int) * RRInstance->lignes[nligne].nbvilles);
			}
			else{
				trace ("Bad file",__FILE__,__LINE__ );
			}
			if(fgets ( line, sizeof(line), file ) != NULL){			//villes de la première ligne
				RRInstance->lignes[nligne].villesInLigne[0]=atoi(strtok(line," "));			//version propre
				for (int i = 1; i < RRInstance->lignes[nligne].nbvilles; ++i){
					RRInstance->lignes[nligne].villesInLigne[i]=atoi(strtok(NULL," "));
				}

				// char *tmp=line;
				// for (int i = 0; i < RRInstance->lignes[nligne].nbvilles; ++i){			//version je fait a ma façon
				// 	RRInstance->lignes[nligne].villesInLigne[i]=atoi(tmp);
				// 	tmp=skip_separator(tmp,' ');
				// }
			}
			else{
				trace ("Bad file",__FILE__,__LINE__ );
			}

			if(fgets ( line, sizeof(line), file ) != NULL){			//nb horaires de la ligne
				RRInstance->lignes[nligne].nbhoraires=atoi(line);
				RRInstance->lignes[nligne].horaires=malloc(sizeof(int *) * RRInstance->lignes[nligne].nbvilles);			//peut etre swap les ordonée absices du tableau?
				for (int j = 0; j < RRInstance->lignes[nligne].nbvilles ; ++j)
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

					for (int j = 1; j < RRInstance->lignes[nligne].nbvilles; ++j){
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

void show_RR(RR * RRInstance){
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
			printf("%i\n",RRInstance->lignes[nligne].nbvilles);						//show nbvilles in ligne
			for (int i = 0; i < RRInstance->lignes[nligne].nbvilles; ++i){			//show villes in ligne
				printf("%i ",RRInstance->lignes[nligne].villesInLigne[i]);
			}
			printf("\n");
			printf("%i\n",RRInstance->lignes[nligne].nbhoraires);					//show nbhoraires
			for (int i = 0; i < RRInstance->lignes[nligne].nbhoraires; ++i)			//show horraire
			{
				for (int j = 0; j < RRInstance->lignes[nligne].nbvilles; ++j)
				{
					printf("%i ",RRInstance->lignes[nligne].horaires[j][i]);
				}
				printf("\n");
			}
		}
	}
}
