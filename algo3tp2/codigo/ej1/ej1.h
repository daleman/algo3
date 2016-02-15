#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include "time.h"
using namespace std;

typedef pair <int,int> par;

struct entrada_ej1 {
	entrada_ej1() {
		n = 0;
		valid = false;
	}
	int n;
	vector<vector<int> > matriz;
	bool valid;
};

struct salida_ej1 {
	salida_ej1() {
		C = 0;
		k = 0;
		e = vector<int>(0);
	}
	salida_ej1(int c,int K,vector<int> E) {
		C = c;
		k = K;
		e = E;
	}
	int C;
	int k;
	vector<int> e;
};

entrada_ej1 inicializar_ej1 ();
vector<vector<int> > inicializarMatrizCostos (int cantTrabajos);
int mostrarMatriz ( vector < vector <par> > matriz, int filas, int columnas );
int mostrarVec ( vector <int> vec);

salida_ej1 resolver_ej1(entrada_ej1 entrada) {
	int cantTrabajos = entrada.n;
	vector<vector<int> > costo = entrada.matriz;

	//En la posicion i j está el costo de la configuración óptima para
	//los primeros i trabajos con el trabajo j como último de la otra máquina.
	vector < vector<par> > distribucionOptima(cantTrabajos+1,vector<par> (cantTrabajos) );
	distribucionOptima[1][0] = make_pair(costo[0][1],0);
	
	for ( int j = 2; j <= cantTrabajos; ++j ) {
		distribucionOptima[j][0] = make_pair (distribucionOptima[j-1][0].first + costo[j-1][j],j-1);
		distribucionOptima[j][j-1] = make_pair (distribucionOptima[j-1][0].first + costo[0][j],0);
		for ( int i = 1; i < j-1 ; ++i ) {
			distribucionOptima[j][i] = make_pair(distribucionOptima[j-1][i].first + costo[j-1][j],j-1);
			int costoAlternativo = distribucionOptima[j-1][i].first + costo[i][j];
			if (costoAlternativo < distribucionOptima[j][j-1].first) {
				distribucionOptima[j][j-1] = make_pair(costoAlternativo,i);
			}
		}
	}

	vector<int> tEnMaq1(0);
	int k = 0;
	int C = distribucionOptima[cantTrabajos][0].first;

	int elAnterior = cantTrabajos-1;
	int ultimoOtraMaquina = 0;
	for (int i=1; i<cantTrabajos; i++) {
		if (distribucionOptima[cantTrabajos][i].first < C) {
			C = distribucionOptima[cantTrabajos][i].first;
			elAnterior = distribucionOptima[cantTrabajos][i].second;
			ultimoOtraMaquina = i;
		}
	}
	
	//cout << "el anterior es " << elAnterior << endl;

	int trabajoEnMaquina = cantTrabajos;	
	tEnMaq1.push_back(trabajoEnMaquina);
	k++;

	while (elAnterior != 0){
		tEnMaq1.push_back(elAnterior);
		k++;
		trabajoEnMaquina = elAnterior;
		while (ultimoOtraMaquina > elAnterior) {
			ultimoOtraMaquina = distribucionOptima[ultimoOtraMaquina][elAnterior].second;
		}
		elAnterior = distribucionOptima[trabajoEnMaquina][ultimoOtraMaquina].second;
	}

	vector<int> e = vector<int>(k);
	for (int i=0; i<k; i++) {
		e[i] = tEnMaq1[k-i-1];
	}

	//cout << "vector de trabajos" << endl;
	//mostrarVec(e);
	
	//cout << "matriz de cofiguracion Optima" << endl;
	//mostrarMatriz(distribucionOptima,cantTrabajos+1,cantTrabajos);
	//cout << endl;

	salida_ej1 salida(C, k, e);
	return salida;
}

entrada_ej1 inicializar_ej1 () {
	entrada_ej1 entrada;
	int cantTrabajos;
	cin >> cantTrabajos;
	if(cantTrabajos > 0) {
		entrada.n = cantTrabajos;
		entrada.valid = true;
		entrada.matriz = inicializarMatrizCostos(cantTrabajos);
	}
	return entrada;
}

void imprimir_ej1(salida_ej1 salida) {
	int C = salida.C;
	int k = salida.k;
	vector<int> e = salida.e;
	cout << C << " " << k << " ";
	for(int i = 0; i < e.size(); ++i)
		cout << e[i] << " ";
	cout << endl;
}

entrada_ej1 generar_instancia_ej1(int n) {
	entrada_ej1 entrada;
	entrada.matriz = vector<vector<int> >(n);
	entrada.n = n;
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
	  entrada.matriz[i] = vector<int>(n+1);
	  for (int j = 0; j <= n; j++) {
	    if (i < j)
	      entrada.matriz[i][j] = 0;
	    else
	      entrada.matriz[i][j] = rand() % n;
	  }
	}
	
	return entrada;
}

vector<vector<int> > inicializarMatrizCostos (int cantTrabajos) {
	vector<vector<int> > matrizCostos;
	for ( int i = 0 ; i < cantTrabajos; ++i ) {
		matrizCostos.push_back(vector<int>());
		for (int j = 0; j <= cantTrabajos; j++) {
		  matrizCostos[i].push_back(0);
		}
	}

	for ( int j = 0; j <= cantTrabajos; ++j ) {
		for ( int i = 0 ; i < cantTrabajos; ++i ) {
			if ( i < j )
				cin >> matrizCostos[i][j];
			else
				matrizCostos[i][j] = 0;
		}
	}
	return matrizCostos;
}

int mostrarVec ( vector <int> vec)
{
	cout << "[" ;
	for (int i = 0; i < vec.size();i++ )
	{
		cout << " " << vec[i]; 
	}
	cout << " ]" << endl;
return 0;
}

int mostrarMatriz ( vector < vector<par> > matriz, int filas, int columnas )
{
	for (int i = 0 ; i < filas ; ++i)
	{
		cout << "|" ;
		for (int j = 0; j < columnas; ++j)
		{
			cout << "\t" << matriz[i][j].first << ", " << matriz[i][j].second; 
		}
		cout << "\t|" << endl;
	}
	cout << "°" << endl;
	return 0;
}
