#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "railwayNetwork.h"
#include "util.h"

//Construction d'un Réseau de gare à partir d'un fichier
void railwayNetwork(char * filename ,RailwayNetwork *RRInstance){
	read_File(filename,RRInstance);
	define_lignesInVille(RRInstance);
}

//Lecture du fichier pour construire le Réseau de gare
void read_File(char * filename ,RailwayNetwork *RRInstance){
	RRInstance->nbvilles=0;
	FILE *file = fopen ( filename, "r" );
	
	if ( file != NULL ){
		char line [128];
		if ( fgets (line, sizeof(line), file ) != NULL ){			//nombre de ville
			RRInstance->nbvilles=atoi(line);
			if (RRInstance->nbvilles <= 0){
				trace ("Bad file nbvilles<=0",__FILE__,__LINE__ );
				exit(EXIT_FAILURE);
			}
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
			if (RRInstance->nblignes <= 0){
				trace ("Bad file nblignes<=0",__FILE__,__LINE__ );
				exit(EXIT_FAILURE);
			}
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
				if (ligne->nbvillesInLigne <= 0){
					trace ("Bad file villeinligne<=0",__FILE__,__LINE__ );
					exit(EXIT_FAILURE);
				}
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
				if (ligne->nbhoraires <= 0){
					trace ("Bad file nbhoraires<=0",__FILE__,__LINE__ );
					exit(EXIT_FAILURE);
				}
				ligne->horaires=malloc(sizeof(int *) * ligne->nbvillesInLigne);			//peut etre swap les ordonée absices du tableau?
				for (int j = 0; j < ligne->nbvillesInLigne ; ++j)
				{
					ligne->horaires[j]=malloc(sizeof(int) * ligne->nbhoraires);
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

//Définit lignesInVille
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

//Récupère les voisins, renvoi les nombre de voisins et stocke les voisins dans le tableau voisins passé en paramètre
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

//Affiche un Réseau de gare
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

//Affiche lignesInVille
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

//Affiche les voisins d'une ville
void show_voisin(RailwayNetwork * RRInstance,int nomville){
	int tab[RRInstance->nblignes];
	int nbvoisins=get_voisin(RRInstance,nomville,tab);
	printf("La ville %d a les voisins : ",nomville);
	for (int i = 0; i < nbvoisins ; ++i){
		printf("%d ",tab[i]);
	}
	printf("\n");
}

//Affiche les voisins de toutes les villes
void show_voisins(RailwayNetwork * RRInstance){
	for (int i = 0; i < RRInstance->nbvilles; ++i){
		show_voisin(RRInstance,i);
	}
}

//Affiche un Réseau de gare, lignesInVille ainsi que les voisins de toutes les villes
void show_all_RR(RailwayNetwork * RRInstance){
	int test=0;
	printf("afficher les valeurs lue ? (OUI:1/NON:0)\n");
	scanf("%d",&test);
	if (test==1){
		show_RR(RRInstance);
		show_lignesInVille(RRInstance);
		show_voisins(RRInstance);
	}
}

//Créer une ville avec des coordonnees uniques
void set_pos_distinct_from_others(RailwayNetwork * RRInstance, int nbPos){
	int faulty;
	do{
		faulty = 0;
		RRInstance->villes[nbPos].x = rand() % MAX_COORDONNEE;
		RRInstance->villes[nbPos].y = rand() % MAX_COORDONNEE;

		for (int i = 0; i < nbPos; i++){
			if ( (RRInstance->villes[nbPos].x == RRInstance->villes[i].x) && (RRInstance->villes[nbPos].y == RRInstance->villes[i].y)){
				faulty = 1;
				break;
			}
		}
	}while(faulty != 1);
}

//Créer les villes d'un Réseau
void generate_Villes(RailwayNetwork * RRInstance){
	RRInstance->villes = malloc(RRInstance->nbvilles * sizeof(ville));
	for(int i = 0; i < RRInstance->nbvilles;++i){
		set_pos_distinct_from_others(RRInstance,i);
	}
}

//Génère une ligne d'un réseau
ligne generate_Ligne(RailwayNetwork * RRInstance, int ** PlusCourtsCHemins,int maxArret){
	ligne Ligne;
	int a = rand() % (RRInstance->nbvilles);
	int b;
	do{
		b= rand() % (RRInstance->nbvilles);
	}while(a == b);
	int i = 0;
	Ligne.villesInLigne = malloc(maxArret * sizeof(int));
	Ligne.villesInLigne[i] = a;
	while( (i < maxArret) && (Ligne.villesInLigne[i] != b) ){
		int v;
		//Pas sur de ça :  choisir au hasard une ville v voisine de T[i] telle que D(v, b) < D(T[i], b);
		do{
			v=rand() % (RRInstance->nbvilles);
		}while(PlusCourtsCHemins[v][b] >= PlusCourtsCHemins[Ligne.villesInLigne[i]][b]);
		++i;
		Ligne.villesInLigne[i] = v;
	}
	Ligne.nbvillesInLigne = i;
	Ligne.nbhoraires = MIN_PASSAGE_JOURNA + rand() % ( MAX_PASSAGE_JOURNA - MIN_PASSAGE_JOURNA +1);
	Ligne.horaires=malloc(sizeof(int) * Ligne.nbvillesInLigne);
	for (int j = 0; j < Ligne.nbvillesInLigne ; ++j){
		Ligne.horaires[j]=malloc(sizeof(int) * Ligne.nbhoraires);
	}
	for(int i =0; i < Ligne.nbhoraires;i++){
		//génèration des horaires
		Ligne.horaires[0][i]= ( ((rand() % (JOUR_EN_HEURE - 1))*60) + ( rand() % (HEURE_EN_MINUTE-1)) );
		for (int j = 1; j < Ligne.nbvillesInLigne; ++j){
			Ligne.horaires[j][i]= ( ((rand() % (JOUR_EN_HEURE - 1))*60) + ( rand() % (HEURE_EN_MINUTE-1)) );
		}
	}
	return Ligne;
}

//Génère les lignes d'un réseau
void generate_lignes(RailwayNetwork * RRInstance, int ** PlusCourtsCHemins,int maxArret){
	RRInstance->lignes = malloc(RRInstance->nblignes * sizeof(ligne));
	for(int i = 1; i < RRInstance->nblignes;i++){
		RRInstance->lignes[i] = generate_Ligne(RRInstance,PlusCourtsCHemins,maxArret);
	}
}

//Génère un réseau
void generate_network(RailwayNetwork * RRInstance,int nbVilles,int densite,int nbLignes,int maxArret){
	srand(time(NULL));
	RRInstance->nbvilles = nbVilles;
	RRInstance->nblignes = nbLignes;
	generate_Villes(RRInstance);
	int nb_aretes = densite * nbVilles * (nbVilles-1)/200;
	for(int i = 1; i < nb_aretes; i++) {
        //u = rand()% nbVilles;
        /*
		choisir au hasard u ∈ V (non saturé),
		soit v ∈ V la plus proche de u tel que (u, v) 6∈ A,
		A := A ∪ {(u, v)},
		*/
    }
    int ** PlusCourtsCHemins;
	//ToDO calculer les longueurs D des plus courts chemins dans (V,A)
	generate_lignes(RRInstance,PlusCourtsCHemins,maxArret);
}
