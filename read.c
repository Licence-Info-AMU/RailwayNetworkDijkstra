#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "util.h"
#include "trace.h"
#include <assert.h>

void read_file(char * filename ,RR *RRInstance){
	RRInstance->nbville=0;
	FILE *file = fopen ( filename, "r" );
	
	if ( file != NULL ){

		char line [128];
		// char *line =malloc(sizeof(char)*128);
		// assert(line!=NULL);

		if ( fgets (line, sizeof(line), file ) != NULL ){			//nombre de ville
			RRInstance->nbville=atoi(line);
			RRInstance->villes=malloc(sizeof(ville)* RRInstance->nbville );
		}
		else{
			trace ("Bad file",__FILE__,__LINE__ );
		}

		for (int i = 0; i <RRInstance->nbville ; ++i)						//coordonnées des villes
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
			RRInstance->nbligne=atoi(line);
			RRInstance->lignes=malloc(sizeof(ligne) * RRInstance->nbligne);
		}
		else{
			trace ("Bad file",__FILE__,__LINE__ );
		}
		for (int nligne = 0; nligne < RRInstance->nbligne; ++nligne)
		{
			if(fgets ( line, sizeof(line), file ) != NULL){			//nombre de villes dans la première ligne
				RRInstance->lignes[nligne].nbvilles=atoi(line);
				RRInstance->lignes[nligne].villes=malloc(sizeof(int) * RRInstance->lignes[nligne].nbvilles);
			}
			else{
				trace ("Bad file",__FILE__,__LINE__ );
			}
			if(fgets ( line, sizeof(line), file ) != NULL){			//villes de la première ligne
				RRInstance->lignes[nligne].villes[0]=atoi(strtok(line," "));			//version propre
				for (int i = 1; i < RRInstance->lignes[nligne].nbvilles; ++i){
					RRInstance->lignes[nligne].villes[i]=atoi(strtok(NULL," "));
				}

				// char *tmp=line;
				// for (int i = 0; i < RRInstance->lignes[nligne].nbvilles; ++i){			//version je fait a ma façon
				// 	RRInstance->lignes[nligne].villes[i]=atoi(tmp);
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
		trace ("Bad file",__FILE__,__LINE__ );
	}
}

void show_RR(RR * RRInstance){		
	printf("%i\n",RRInstance->nbville );										//show nbville
	for (int i = 0; i < RRInstance->nbville; ++i){								//show coordonée ville
		printf("%i",RRInstance->villes[i].x);
		printf(" %i\n",RRInstance->villes[i].y);
	}
	printf("%i\n",RRInstance->nbligne);											//show nb ligne
	for (int nligne = 0; nligne < RRInstance->nbligne; ++nligne){				//show ligne
		printf("%i\n",RRInstance->lignes[nligne].nbvilles);						//show nbville in ligne
		for (int i = 0; i < RRInstance->lignes[nligne].nbvilles; ++i){			//show villes in ligne
			printf("%i ",RRInstance->lignes[nligne].villes[i]);
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

int main (int argc , char * argv[]){
	char filename[] = "test.txt";
	struct RR RRInstance;
	read_file(filename,&RRInstance);
	show_RR(&RRInstance);
	return 0;
}
