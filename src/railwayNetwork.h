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

void railwayNetwork(char * filename,RailwayNetwork * RRInstance);

void read_File(char * filename ,RailwayNetwork *RRInstance);

void generate_Villes(RailwayNetwork * RRInstance);

ligne generate_Ligne(RailwayNetwork * RRInstance, int ** PlusCourtsCHemins,int maxArret);

void generate_lignes(RailwayNetwork * RRInstance, int ** PlusCourtsCHemins,int maxArret);

void generate_network(RailwayNetwork * RRInstance,int nGares,int densite,int mLignes,int maxGareParLigne);

void define_lignesInVille(RailwayNetwork * RRInstance);

int get_voisin(RailwayNetwork * RRInstance,int nomville,int * voisins);

void show_lignesInVille(RailwayNetwork * RRInstance);

void show_voisin(RailwayNetwork * RRInstance,int nomville);

void show_voisins(RailwayNetwork * RRInstance);

void show_RR(RailwayNetwork * RRInstance);

void show_all_RR(RailwayNetwork * RRInstance);

#endif
