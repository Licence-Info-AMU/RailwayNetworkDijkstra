#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int FilsG(int i) {
	return (2*i+1);
}

int FilsD(int i) {
	return (2*i+2);
}

void entasser(int i, int * tab, int n){
	int iMax = i;
	if((FilsG(i) < n) && (tab[FilsG(i)] > tab[iMax]))		
		iMax = FilsG(i);
	
	if((FilsD(i) < n) && (tab[FilsD(i)] > tab[iMax]))
		iMax = FilsD(i);
	
	if (iMax != i){
		swap_tab_int(tab,i,iMax);
		entasser(iMax,tab,n);	
	}
}

void construire_tas(int * T, int n){
	for(int i = 0; i < (n/2);i++){
		entasser(i,T,n);
	}
}
