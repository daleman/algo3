#ifndef EXACTO_H
#define EXACTO_H
#include <cmath>
#include <cstdlib>
#include "../grafo.h"
#include "../timer.h"
#include <vector>


using namespace std;
void exacto_recur(grafo &g, int i, Solucion &optima, Solucion &actual);
void exacto_recur_sp(grafo &g, int i, Solucion &optima, Solucion &actual);

Solucion exacto(grafo &g) {
	Solucion optima = make_pair(vector<bool>(g.cantNodos,false), 0);
	Solucion actual = make_pair(vector<bool>(g.cantNodos,false), 0);
	exacto_recur(g, 0, optima, actual);
	return optima;
}

Solucion exacto_sin_poda(grafo &g) {
	Solucion optima = make_pair(vector<bool>(g.cantNodos,false), 0);
	Solucion actual = make_pair(vector<bool>(g.cantNodos,false), 0);
	exacto_recur_sp(g, 0, optima, actual);
	return optima;
}

void exacto_recur(grafo &g, int i, Solucion &optima, Solucion &actual) {
	if (actual.second > optima.second) {
		optima = actual;
	}
	if (i==g.cantNodos) {
		return;
	}

	// si se conecta_con_clique sigo la recursion con y sin ese nodo
	if ( g.se_conecta_con_clique(i, actual.first) ) {
		g.alternar(actual, i);
		//Si funciona bien, las siguientes 2 líneas deberían imprimir una línea por clique:
		//es decir una por cada nodo + una por cada arista + una por cada K3, etc
		//cout << "i=" << i << "\tActual: "; solucion(actual);
		//cout << "\tOptima: "; solucion(optima); cout << endl;
		exacto_recur(g, i+1, optima, actual);
		g.alternar(actual, i);
		exacto_recur(g, i+1, optima, actual);
	// si no se conecta con mas nodos tampoco va a ser una clique, luego hago la recursion sin ese nodo
	}else{
		exacto_recur(g, i+1, optima, actual);
	}
}

void exacto_recur_sp(grafo &g, int i, Solucion &optima, Solucion &actual) {
	if (actual.second > optima.second) {
		optima = actual;
	}
	if (i==g.cantNodos) {
		return;
	}
	g.alternar(actual, i);
	exacto_recur_sp(g, i+1, optima, actual);
	g.alternar(actual, i);
	exacto_recur_sp(g, i+1, optima, actual);
}

#endif
