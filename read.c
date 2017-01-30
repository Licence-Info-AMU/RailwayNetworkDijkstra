#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "trace.h"


char * skip_separator(char * line,char separator){    //magic thing are magic
	for (int i = 0; i < strlen(line); ++i){
		if (line[i]==separator){
			return line+i+1;
		}
	}
	return line;
}

struct RR read_file(char * filename){
	struct RR RRInstance;
	int i=-1,nligne=0,test;
	RRInstance.nbville=0;
	FILE *file = fopen ( filename, "r" );
	
	if ( file != NULL ){
		char line [128];
		while ( fgets ( line, sizeof line, file ) != NULL ){
			if (i==-1){                                              //nombre de ville
				RRInstance.nbville=atoi(line);
				RRInstance.villes=malloc(sizeof(ville[RRInstance.nbville]));
			}else if (i>=0 && i<RRInstance.nbville){                          //coordonnées des villes
				RRInstance.villes[i].x=atoi(line);
				RRInstance.villes[i].y=atoi(skip_separator(line,' '));
			}else if (i==RRInstance.nbville){                                 //nombre de lignes
				RRInstance.nbligne=atoi(line);
				RRInstance.lignes=malloc(sizeof(ligne[RRInstance.nbligne]));
			 }else if(i==RRInstance.nbville+1){                                //nombre de villes dans la première ligne
				RRInstance.lignes[nligne].nbvilles=atoi(line);
				RRInstance.lignes[nligne].villes=malloc(sizeof(int[RRInstance.lignes[nligne].nbvilles]));
			 }else if(i==RRInstance.nbville+2){                                //ville de la première ligne
				
			 }else if(i==RRInstance.nbville+3){                                //
				RRInstance.lignes[nligne].nbhoraires=atoi(line);
				RRInstance.lignes[nligne].horaires=malloc(sizeof(int[RRInstance.lignes[nligne].nbvilles][RRInstance.lignes[nligne].nbhoraires]));
			 }else if(i>=RRInstance.nbville+4 && i<RRInstance.nbville+RRInstance.lignes[nligne].nbhoraires+4){
				test=atoi(line);
				printf("%d\n", test);
				test=atoi(line+3);
				printf("%d\n", test);
			}else if(i==RRInstance.nbville+RRInstance.lignes[nligne].nbhoraires+4){
				i=(i-RRInstance.lignes[nligne].nbhoraires-3);
				nligne++;
				RRInstance.lignes[nligne].nbvilles=atoi(line);
				RRInstance.lignes[nligne].villes=malloc(sizeof(int[RRInstance.lignes[nligne].nbvilles]));
			}
			i++;
		}
		fclose ( file );
	}else{
		trace (filename,__FILE__,__LINE__ );
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
