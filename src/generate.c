#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "trace.h"

#define MAX_COORDONNEE 999
#define MAX_PASSAGE_JOURNA 4  

void generateCoordonnees(char * donnees,int nbVille){
	int x;
	int y;
	for(int i = 0; i < nbVille;++i){
		x = rand() % MAX_COORDONNEE;
		y = rand() % MAX_COORDONNEE;
		sprintf(donnees,"%s%d %d\n",donnees,x,y);
	}
}

void generateHorraires(char * donnees,int nbVilleInLigne,int * villes){ // A revoir
	int nbPassageJournalier = rand() % MAX_PASSAGE_JOURNA;
	sprintf(donnees,"%s%d\n",donnees,nbVilleInLigne);
	//ToDo villes
	sprintf(donnees,"%s%d\n",donnees,nbPassageJournalier);
	//ToDo Horraires
}

void generateDonnees(char * donnees,int nbVille){
	srand (time (NULL));
	int nbLigne = rand() % nbVille;
	int nbVilleTmp = nbVille;
	int nbVilleInLigne = 0;	
	sprintf(donnees,"%s%d\n",donnees,nbVille);
	generateCoordonnees(donnees,nbVille);
	sprintf(donnees,"%s%d\n",donnees,nbLigne);
	for(int i = 0; i < nbLigne;++i){
		nbVilleInLigne = rand() % nbVilleTmp;
		nbVilleTmp -= nbVilleInLigne;
		generateHorraires(donnees,nbVilleInLigne,villes);
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
