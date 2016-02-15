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
void exacto_recur_2p(grafo &g, int i, Solucion &optima, Solucion &actual, int size_solucion);
int puede_incremetar_frontera(int n, int C, int Opt);

Solucion exacto_2p(grafo &g) {
  Solucion optima = make_pair(vector<bool>(g.cantNodos,false), 0);
  Solucion actual = make_pair(vector<bool>(g.cantNodos,false), 0);
  exacto_recur_2p(g, 0, optima, actual, 0);
  return optima;
}

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

void exacto_recur_2p(grafo &g, int i, Solucion &optima, Solucion &actual, int size_solucion) {
  if (actual.second > optima.second) {
    optima = actual;
  }
  if (i==g.cantNodos) {
    return;
  }
  // Segunda Poda: si al agregar nodos, la clique es demasiado
  // grande, entonces ya no sirve seguir agregando
  if (size_solucion+1 > (g.cantNodos/2)) {
    return;
  }

  if ( g.se_conecta_con_clique(i, actual.first) ) {
    g.alternar(actual, i);
    exacto_recur_2p(g, i+1, optima, actual, size_solucion + 1);
    g.alternar(actual, i);
    exacto_recur_2p(g, i+1, optima, actual, size_solucion);
  } else {
    exacto_recur_2p(g, i+1, optima, actual, size_solucion);
  }
}

void exacto_recur(grafo &g, int i, Solucion &optima, Solucion &actual) {
  if (actual.second > optima.second) {
    optima = actual;
  }
  if (i==g.cantNodos) {
    return;
  }

  // si se_conecta_con_clique sigo la recursion con y sin ese nodo
  if ( g.se_conecta_con_clique(i, actual.first) ) {
    g.alternar(actual, i);
    exacto_recur(g, i+1, optima, actual);
    g.alternar(actual, i);
    exacto_recur(g, i+1, optima, actual);
  // si no se conecta con mas nodos tampoco va a ser una clique,
  // luego hago la recursion sin ese nodo
  } else {
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
