#ifndef READ_H
#define READ_H

typedef struct ligne{
   int nbvilles;
   int *villes;

   int nbhoraires;
   int **horaires;
}ligne;

typedef struct ville{
   int x;
   int y;
}ville;

typedef struct RR{
   int nbligne;
   int nbville;
   ville *villes;
   ligne *lignes;
}RR;

struct RR read_file(char * filename);

void show_RR(struct RR RRInstance);

#endif
