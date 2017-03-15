#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "trace.h"

char * skip_separator(char * line,char separator){    //magic thing are magic rip 
	for (unsigned int i = 0; i < strlen(line); ++i){
		if (line[i]==separator){
			return line+i+1;
		}
	}
	return line;
}

int compare_int(const void *a,const void *b) {
	int *x = (int *) a;
	int *y = (int *) b;
	return *x - *y;
}

void sort_int(int * x){
	qsort (x, sizeof(x)/sizeof(*x), sizeof(*x), compare_int);
}

void swap_tab_int(int * tab, int i, int j){
	int temp;
	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

void create_Tab_Int(int * tab, int n){
	tab = malloc(n*sizeof(int));
    if(tab == NULL) {
		trace("Allocation impossible d'un tableau !",__FILE__,__LINE__);
		exit (1);
	}
}

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
