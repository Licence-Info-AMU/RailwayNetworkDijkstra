#ifndef UTIL_H
#define UTIL_H
#include "trace.h"

//Récupére une chaine après un séparateur, plus utilisé
char * skip_separator(char * line,char separator);

//Echange les valeurs des cases données dans un tableau
void swap_tab_int(int * tab, int i, int j);

//Quicksort pour trier un tableau d'entier
void quicksort(int T[],int debut, int fin);

//Affiche les valeurs d'une matrice d'entier
void showmatrice(int ** mat,int sizex,int sizey); //mat[x][y]

//Converti un entier en char*, plus utilisé
char *itoa (int value, char *result, int base);

#endif
