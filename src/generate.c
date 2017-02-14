#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "trace.h"

#define MAX_COORDONNEE 999

void generateCoordonnees(char * donnees,int nbVille){
	int x;
	int y;
	for(int i = 0; i < nbVille;++i){
		x = rand % MAX_COORDONNEE;
		y = rand % MAX_COORDONNEE;
		sprintf(donnees,"%s%d %d\n",donnees,x,y);
	}
}

void generateHorraires(char * donnees,int nbVilleInLigne,int nbPassageJournalier){ // A revoir

}

void generateDonnees(char * donnees,int nbVille){
	srand (time (NULL));
	int nbLigne = rand % nbVille;
	int nbVilleTmp = nbVille;
	int nbVilleInLigne = 0;
	int nbPassageJournalier = 0;
	sprintf(donnees,"%s%d\n",donnees,nbVille);
	generateCoordonnees(donnees,nbVille);
	sprintf(donnees,"%s%d\n",donnees,nbLigne);
	for(int i = 0; i < nbLigne;++i){
		
		//generateHorraires(donnees,nbVilleInLigne,nbPassageJournalier);
	}
	
}

void generateFile(char * fileName,int nbVille){
	char donnees[20];
	FILE* file = NULL;
	file = fopen (fileName, "a+");
	generateDonnees(donnees,nbVille);
	if (file != NULL){
		fputs(donnees,file);
        fclose(file);
    }else{
		trace("Bad file",__FILE__,__LINE__ );
	}
}
