#ifndef RAILWAYNETWORK_H
#define RAILWAYNETWORK_H

typedef struct ligne{
   int nbvillesInLigne;
   int *villesInLigne;

   int nbhoraires;
   int **horaires;
}ligne;

typedef struct lignesInVille{
   int numeroligne;
   int rankville;
}lignesInVille;

typedef struct ville{
   int x;
   int y;
   int nblignesInVille;
   lignesInVille * lignesInVille;
}ville;

typedef struct RailwayNetwork{
   int nblignes;
   int nbvilles;
   ville *villes;
   ligne *lignes;
}RailwayNetwork;

void define_lignesInVille(RailwayNetwork * RRInstance);

void show_lignesInVille(RailwayNetwork * RRInstance);

int get_voisin(RailwayNetwork * RRInstance,int nomville,int * voisins);

void show_voisin(RailwayNetwork * RRInstance,int nomville);

void show_voisins(RailwayNetwork * RRInstance);

void read_File(char * filename ,RailwayNetwork *RRInstance);

void railwayNetwork(char * filename,RailwayNetwork * RRInstance);

void show_RR(RailwayNetwork * RRInstance);

#endif
