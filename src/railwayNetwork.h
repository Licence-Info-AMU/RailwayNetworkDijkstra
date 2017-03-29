#ifndef RAILWAYNETWORK_H
#define RAILWAYNETWORK_H

typedef struct{
   int nbvillesInLigne;
   int *villesInLigne;
   int nbhoraires;
   int **horaires;	//horaires[nbvillesInLigne][nbhoraires];
}ligne;

typedef struct{
   int x;
   int y;
   int nblignesInVille;
   int * lignesInVille;

}ville;

typedef struct{
   int nblignes;
   int nbvilles;
   ville *villes;
   ligne *lignes;
}RailwayNetwork;

static int const MAX_COORDONNEE = 999;
static int const MAX_PASSAGE_JOURNA = 10;
static int const MIN_PASSAGE_JOURNA = 2;
static int const JOUR_EN_HEURE = 24;
static int const HEURE_EN_MINUTE = 60;

//Construction d'un Réseau de gare à partir d'un fichier
void railwayNetwork(char * filename,RailwayNetwork * RRInstance);

//Lecture du fichier pour construire le Réseau de gare
void read_File(char * filename ,RailwayNetwork *RRInstance);

//Créer une ville avec des coordonnees uniques
void set_pos_distinct_from_others(RailwayNetwork * RRInstance, int nbPos);

//Créer les villes d'un Réseau
void generate_Villes(RailwayNetwork * RRInstance);

//Génère une ligne d'un réseau
ligne generate_Ligne(RailwayNetwork * RRInstance, int ** PlusCourtsCHemins,int maxArret);

//Génère les lignes d'un réseau
void generate_lignes(RailwayNetwork * RRInstance, int ** PlusCourtsCHemins,int maxArret);

//Génère un réseau
void generate_network(RailwayNetwork * RRInstance,int nGares,int densite,int mLignes,int maxGareParLigne);

//Définit lignesInVille
void define_lignesInVille(RailwayNetwork * RRInstance);

//Récupère les voisins, renvoi les nombre de voisins et stocke les voisins dans le tableau voisins passé en paramètre
int get_voisin(RailwayNetwork * RRInstance,int nomville,int * voisins);

//Affiche lignesInVille
void show_lignesInVille(RailwayNetwork * RRInstance);

//Affiche les voisins d'une ville
void show_voisin(RailwayNetwork * RRInstance,int nomville);

//Affiche les voisins de toutes les villes
void show_voisins(RailwayNetwork * RRInstance);

//Affiche un Réseau de gare
void show_RR(RailwayNetwork * RRInstance);

//Affiche un Réseau de gare, lignesInVille ainsi que les voisins de toutes les villes
void show_all_RR(RailwayNetwork * RRInstance);

#endif
