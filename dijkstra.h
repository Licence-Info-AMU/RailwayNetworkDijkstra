#ifndef DIJKSTRA_H
#define DIJKSTRA_H

typedef struct trajet{
    
	int horaireDep;
	int horaireArr;
	int numeroLigne;
}trajet;

void init_d(int tabTaille);
void init_Dijkstra(RR * RRInstance,int sdeb);

#endif
