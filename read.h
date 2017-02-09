#ifndef READ_H
#define READ_H



typedef struct ligne{
   int nbvilles;
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

typedef struct RR{
   int nblignes;
   int nbvilles;
   ville *villes;
   ligne *lignes;
}RR;

void read_file(char * filename,RR * RRInstance);

void show_RR(RR * RRInstance);

#endif
