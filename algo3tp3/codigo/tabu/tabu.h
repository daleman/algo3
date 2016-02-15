#ifndef TABU_H
#define TABU_H
#include "../goloso/goloso.h"
#include "../tabu_list.h"

using namespace std;

// Parámetros:
// * cant_iter: máxima cantidad de iteraciones sin mejorar
	// (se reinicia cada vez que mejora)
// * tabu_size: tamaño de la lista tabú
	// (cantidad de soluciones que puede almacenar)
// * vecinos_size: tamaño de la vecindad
	// (cantidad de nodos distintos (como máximo) de cada vecino)
	// La cantidad de vecinos en una vecindad de tamaño V es
		// Sum{i=1..V} (n i)
Solucion tabu(grafo &g, Solucion &sol_inicial, int cant_iter, int tabu_size, int vecinos_size) {

	Solucion sol_optima = make_pair(sol_inicial.first, sol_inicial.second);
	Solucion sol_actual = make_pair(sol_inicial.first, sol_inicial.second);
	Tabu_list lista_tabu(tabu_size);
	int iter = 0;
	int vecindad = cant_vecinos(g.cantNodos, vecinos_size);
	while (iter < cant_iter) {
		Solucion sol_mejor = make_pair(vector<bool>(0), -pow(g.cantNodos,2));//solucion inválida
		Solucion sol_mejor_tabu = make_pair(vector<bool>(0), -pow(g.cantNodos,2));//solucion inválida
		//Recorrer vecindad
		Solucion temporal = make_pair(vector<bool>(0), -1);
		for (int i=0; i<vecindad; i++) {
			temporal = g.obtener_vecino(sol_actual, temporal, i);
			if (temporal.second > sol_optima.second) {
				sol_optima = temporal;
				if (sol_mejor.second > sol_actual.second) iter = -1;
			}
			if (temporal.second > sol_mejor_tabu.second) {
				sol_mejor_tabu = temporal;
			}
			if ((temporal.second > sol_mejor.second)
				&&(!lista_tabu.es_tabu(temporal.first))) {
					sol_mejor = temporal;
			}
		}
		iter++;
		lista_tabu.add_tabu(sol_actual.first);
		sol_actual = sol_mejor;
		// Si no pude tomar ningún vecino valido, tomo una solución tabú
		if (sol_actual.second==-pow(g.cantNodos,2)) {
			sol_actual = sol_mejor_tabu;
		}
		// Si tampoco tengo una solución tabú, me quedé estancado
		if (sol_actual.second==-pow(g.cantNodos,2)) {
			iter = cant_iter;
		}
	}

	return sol_optima;
}

#endif
