#ifndef TAS_H
#define TAS_H

//Récupère le Fils gauche
int FilsG(int i);

//Récupère le Fils droit
int FilsD(int i);

//Récupère le père
int Pere(int i);

//Entasse le tas vers le bas
void entasserVersLeBas(int i, int * tab, int * position, int * distance, int n);

//Entasse le tas vers le haut
void entasserVersLeHaut(int i, int * tab, int * position, int * distance, int n);

//Construit un tas
void construire_tas(int * tab, int * position, int * distance, int n);

#endif
