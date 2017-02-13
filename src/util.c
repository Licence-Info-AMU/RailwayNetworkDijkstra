#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * skip_separator(char * line,char separator){    //magic thing are magic rip 
	for (int i = 0; i < strlen(line); ++i){
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
