#ifndef LOCAL_H
#define LOCAL_H
#include "../goloso/goloso.h"

using namespace std;

// Parámetros:
// * cant_iter: máxima cantidad de iteraciones sin mejorar
	// (se reinicia cada vez que mejora)
// * vecinos_size: tamaño de la vecindad
	// (cantidad de nodos distintos (como máximo) de cada vecino)
	// La cantidad de vecinos en una vecindad de tamaño V es
		// Sum{i=1..V} (n i)
Solucion local(grafo &g, Solucion &sol_inicial, int vecinos_size) {

	Solucion sol_actual = make_pair(sol_inicial.first, sol_inicial.second);
	bool maximo_local = false;
	int vecindad = cant_vecinos(g.cantNodos, vecinos_size);
	while (!maximo_local) {
		Solucion sol_mejor = make_pair(vector<bool>(0), -1);//solucion inválida
		//Recorrer vecindad
		Solucion temporal = make_pair(vector<bool>(0), -1);
		for (int i=0; i<vecindad; i++) {
			temporal = g.obtener_vecino(sol_actual, temporal, i);
			if (temporal.second > sol_mejor.second) {
					sol_mejor = temporal;
			}
		}
		if (sol_mejor.second > sol_actual.second) {
			sol_actual = sol_mejor;
		} else {
			maximo_local = true;
		}
	}
	return sol_actual;
}

#endif
