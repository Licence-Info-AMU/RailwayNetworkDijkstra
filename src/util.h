#ifndef UTIL_H
#define UTIL_H
#include "trace.h"

char * skip_separator(char * line,char separator);

void swap_tab_int(int * tab, int i, int j);

void quicksort(int T[],int debut, int fin);

void showmatrice(int ** mat,int sizex,int sizey); //mat[x][y]

char *itoa (int value, char *result, int base);

#endif
