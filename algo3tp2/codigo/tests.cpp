#include <cmath>
#include <cstdlib>
#include "grafo.h"
#include "ej1/ej1.h"
#include "ej2/ej2.h"
#include "ej3/ej3.h"
#include "timer.h"

using namespace std;

void testear_ej1( int maxN, int step, int cantTests ) {
    for (int n=step; n<=maxN; n+=step) {
		double acum = 0;
		double elmax = 0;
		double elmin = 1E+37;
		double todos[cantTests];
	
		for (int k=0; k<cantTests; k++) {
			
			entrada_ej1 entrada = generar_instancia_ej1(n);
			double duracion;
			iniciarTimer();
		//-> Resolver_ej1:
		int cantTrabajos = entrada.n;
		vector<vector<int> > costo = entrada.matriz;
		vector < vector<par> > distribucionOptima(cantTrabajos+1,vector<par> (cantTrabajos) );
		distribucionOptima[1][0] = make_pair(costo[0][1],0);

		for ( int j = 2; j <= cantTrabajos; ++j ) {
			distribucionOptima[j][0] = make_pair
				(distribucionOptima[j-1][0].first + costo[j-1][j],j-1);
			distribucionOptima[j][j-1] = make_pair
				(distribucionOptima[j-1][0].first + costo[0][j],0);
			for ( int i = 1; i < j-1 ; ++i ) {
				distribucionOptima[j][i] = make_pair
					(distribucionOptima[j-1][i].first + costo[j-1][j],j-1);
				int costoAlternativo = distribucionOptima[j-1][i].first + costo[i][j];
				if (costoAlternativo < distribucionOptima[j][j-1].first) {
					distribucionOptima[j][j-1] = make_pair(costoAlternativo,i);
				}
			}
		}
		//->
			duracion = finalizarTimer();
			acum += duracion;
			todos[k] = duracion;
			if (duracion > elmax) elmax = duracion;
			if (duracion < elmin) elmin = duracion;
		}
		double media = acum/cantTests;
		
		double desvioEstandar = 0;
		for (int l =0; l<cantTests; ++l) {
			double d = todos[l]-media;
			desvioEstandar += (d*d);
		}
		desvioEstandar = sqrt(desvioEstandar/(cantTests-1));
		cout << n << " " << fixed << media << " " << fixed << media-desvioEstandar;
		cout << " " << fixed << media + desvioEstandar << endl;
	}
}

void testear_ej2( int maxN, int step, int cantTests ) {
   	for (int n=step; n<=maxN; n+=step) {
		double acum = 0;
		double elmax = 0;
		double elmin = 1E+37;
		double todos[cantTests];
	
		for (int k=0; k<cantTests; k++) {
			
			entrada_ej2 entrada = generar_instancia_ej2b(n);
			double duracion;
			iniciarTimer();
		//-> Resolver_ej2:
        if ( entrada.g.cantNodos != 1 ) {
			int nodo_a = entrada.g.bfs(rand()%(entrada.g.cantNodos));
			int nodo_b = entrada.g.bfs(nodo_a);
			entrada.g.dfs(nodo_a, nodo_b);
		}
        //-->
			duracion = finalizarTimer();
			acum += duracion;
			todos[k] = duracion;
			if (duracion > elmax) elmax = duracion;
			if (duracion < elmin) elmin = duracion;
		}
		double media = acum/cantTests;
		
		double desvioEstandar = 0;
		for (int l =0; l<cantTests; ++l) {
			double d = todos[l]-media;
			desvioEstandar += (d*d);
		}
		desvioEstandar = sqrt(desvioEstandar/(cantTests-1));
		cout << n << " " << fixed << media << " " << fixed << media-desvioEstandar;
		cout << " " << fixed << media + desvioEstandar << endl;
	}
}

void testear_ej3( int maxN, int step, int cantTests ) {
	for (int n=step; n<=maxN; n+=step) {
		double acum = 0;
		double elmax = 0;
		double elmin = 1E+37;
		double todos[cantTests];
	
		for (int k=0; k<cantTests; k++) {
			
			entrada_ej3 entrada = generar_instancia_ej3(n);
			double duracion;
			iniciarTimer();
		//-> Resolver_ej3:
        if ( entrada.g.cantNodos != 1 ) {
			entrada.g.kruskal_no_res();
		}
		//->
			duracion = finalizarTimer();
			acum += duracion;
			todos[k] = duracion;
			if (duracion > elmax) elmax = duracion;
			if (duracion < elmin) elmin = duracion;
		}
		double media = acum/cantTests;
		
		double desvioEstandar = 0;
		for (int l =0; l<cantTests; ++l) {
			double d = todos[l]-media;
			desvioEstandar += (d*d);
		}
		desvioEstandar = sqrt(desvioEstandar/(cantTests-1));
		cout << n << " " << fixed << media << " " << fixed << media-desvioEstandar;
		cout << " " << fixed << media + desvioEstandar << endl;
	}
}

int main(int argc, const char* argv[]) {
	
	if (argc == 0){
		cout << "¿Qué ejercicio querés testear?" << endl;
		return 1;
	}if (argc < 5) {
		cout << "El programa se llama asi: " << argv[0] <<
			" NUM_EJERCICIO MAX_N STEP CANT_TESTS" << endl;
		return 1;
	}	

	int ej = atoi(argv[1]);
	int maxN = atoi(argv[2]);
	int step = atoi(argv[3]);
	int cantTests = atoi(argv[4]);
	
    if (ej == 1)
            testear_ej1(maxN, step, cantTests);
    if (ej == 2)
            testear_ej2(maxN, step, cantTests);
    if (ej == 3)
            testear_ej3(maxN, step, cantTests);

	return 0;
}
