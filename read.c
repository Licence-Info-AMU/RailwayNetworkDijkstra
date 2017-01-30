#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "util.h"
#include "trace.h"

struct RR read_file(char * filename){
	struct RR RRInstance;
	int i=0,nligne=0,test;
	RRInstance.nbville=0;
	FILE *file = fopen ( filename, "r" );
	
	if ( file != NULL ){
		char line [128];
		if ( fgets (line, sizeof(line), file ) != NULL ){			//nombre de ville
			RRInstance.nbville=atoi(line);
			RRInstance.villes=malloc(sizeof(ville[RRInstance.nbville]));
		}
		else{
			trace ("Bad file",__FILE__,__LINE__ );
		}

		for (int i = 0; i <RRInstance.nbville ; ++i)						//coordonnées des villes
		{
			if ( fgets ( line, sizeof(line), file ) != NULL ){
				RRInstance.villes[i].x=atoi(line);
				RRInstance.villes[i].y=atoi(skip_separator(line,' '));
			}
			else{
				trace ("Bad file",__FILE__,__LINE__ );
			}

		}

		if ( fgets ( line, sizeof(line), file ) != NULL ){			//nombre de lignes
			RRInstance.nbligne=atoi(line);
			RRInstance.lignes=malloc(sizeof(ligne[RRInstance.nbligne]));
		}
		else{
			trace ("Bad file",__FILE__,__LINE__ );
		}

		for (int nligne = 0; nligne < RRInstance.nbligne; ++nligne)
		{
			if(fgets ( line, sizeof(line), file ) != NULL){			//nombre de villes dans la première ligne
				RRInstance.lignes[nligne].nbvilles=atoi(line);
				RRInstance.lignes[nligne].villes=malloc(sizeof(int[RRInstance.lignes[nligne].nbvilles]));
			}
			else{
				trace ("Bad file",__FILE__,__LINE__ );
			}

			if(fgets ( line, sizeof(line), file ) != NULL){			//villes de la première ligne


			}
			else{
				trace ("Bad file",__FILE__,__LINE__ );
			}

			if(fgets ( line, sizeof(line), file ) != NULL){			//nb horaires de la ligne
				RRInstance.lignes[nligne].nbhoraires=atoi(line);
				RRInstance.lignes[nligne].horaires=malloc(sizeof(int[RRInstance.lignes[nligne].nbvilles][RRInstance.lignes[nligne].nbhoraires]));	//peut etre swap les ordonée absices du tableau?
			}
			else{
				trace ("Bad file",__FILE__,__LINE__ );
			}

			for (int i = 0; i < RRInstance.lignes[nligne].nbhoraires ; ++i)
			{
				if(fgets ( line, sizeof(line), file ) != NULL){		//villes de la première ligne
					test=atoi(line);
					printf("%d\n", test);
					test=atoi(line+3);
					printf("%d\n", test);
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
	return RRInstance;
}

void show_RR(struct RR RRInstance){
	for (int i = 0; i < RRInstance.nbville; ++i){
		printf("%i",RRInstance.villes[i].x);
		printf(" %i\n",RRInstance.villes[i].y);
	}
}

int main (int argc , char * argv[]){
	char filename[] = "test.txt";
	struct RR RRInstance;
	RRInstance = read_file(filename);
	show_RR(RRInstance);
	return 0;
}
