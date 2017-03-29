#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

//Récupére une chaine après un séparateur, plus utilisé
char * skip_separator(char * line,char separator){    //magic thing are magic rip 
	for (unsigned int i = 0; i < strlen(line); ++i){
		if (line[i]==separator){
			return line+i+1;
		}
	}
	return line;
}

//Echange les valeurs des cases données dans un tableau
void swap_tab_int(int * tab, int i, int j){
	int temp;
	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

//Quicksort pour trier un tableau d'entier
void quicksort(int T[],int debut, int fin) //O(n.ln(n))
{
    int p;
    int d=debut;
    int f=fin;
    if (debut<fin)
    {
        p=T[(debut+fin)/2];
        while (d<=f)
        {
            while (T[d]<p)
                d++;
            while (T[f]>p)
                f--;
            if (d<=f)
            {
                int tmp=T[d];
                T[d]=T[f];
                T[f]=tmp;
                d++;
                f--;
            }
        }
        quicksort(T,debut,f);
        quicksort(T,d,fin);
    }
}

//Affiche les valeurs d'une matrice d'entier
void showmatrice(int ** mat,int sizex,int sizey){           //mat[x][y]
    printf("\n");
    for (int i = 0; i < sizex; ++i){
        for (int j = 0; j < sizey; ++j){
            printf("%d\t",mat[i][j]);
        }
        printf("\n");
    }
}

//Converti un entier en char*, plus utilisé
char *itoa (int value, char *result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}
