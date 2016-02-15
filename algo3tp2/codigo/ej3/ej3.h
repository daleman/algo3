#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include "time.h"
#include "../grafo.h"
#include "../grafoEx.h"
using namespace std;

struct entrada_ej3 {
	entrada_ej3() {
		valid = false;
		g = grafoEx();
		F = 0;
	}
	bool valid;
	grafoEx g;
	int F;
};

struct salida_ej3 {
	salida_ej3() {
		L = 0;
		k = 0;
		e = vector<int>(0);
	}
	salida_ej3(int l,int K,vector<int> E) {
		L = l;
		k = K;
		e = E;
	}
	int L;
	int k;
	vector<int> e;
};

salida_ej3 resolver_ej3(entrada_ej3 i){
	vector<int> e;

    /* Grafo Trivial */
    if ( i.g.cantNodos == 1 ) {
            salida_ej3 trivial(0, 0, e);
            return trivial;
    }
	
	grafo res = i.g.kruskal();
	
	/* Calculo todos los resultados para mostrar */
	int L = 0;
	int k = res.aristas.size();
	for(int i = 0; i < res.aristas.size(); ++i){
		L += res.aristas[i].peso;
		e.push_back(res.aristas[i].nodo1+1);
		e.push_back(res.aristas[i].nodo2+1);
	}

	salida_ej3 salida(L,k,e);
	return salida;
}

entrada_ej3 generar_instancia_ej3(int n) {
	entrada_ej3 entrada;
	srand(time(NULL));
	if (n==1) {
		entrada.F = 1;
		entrada.g = grafoEx(1, 0);
	} else if (n==2) {
		entrada.F = 1 + rand() % 2;
		entrada.g = grafoEx(entrada.F, n-entrada.F);
		entrada.g.asociar(1,2,10);
	} else {
		entrada.F = 1 + rand() % (n-2);
		entrada.g = grafoEx(entrada.F, n - entrada.F);
		entrada.g.generar_aristas_aleatorias();
	}
	return entrada;
}

entrada_ej3 inicializar_ej3() {
	entrada_ej3 entrada;
	int F, C, R, a, b, c;
	cin >> F;
	if(F != 0) {
		entrada.valid = true;
		entrada.F = F;
		cin >> C >> R;
		grafoEx g(F,C);
		for(int i = 0; i < R; ++i){
			cin >> a;
			cin >> b;
			cin >> c;
			g.asociar(a,b,c);
		}
		entrada.g = g;
	}
	return entrada;
}

void imprimir_ej3(salida_ej3 salida) {
	int L = salida.L;
	int k = salida.k;
	vector<int> e = salida.e;
	cout << L << " " << k << " ";
	for(int i = 0; i < e.size(); ++i)
		cout << e[i] << " ";
	cout << endl;
}
