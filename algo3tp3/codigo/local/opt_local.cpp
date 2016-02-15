#include "local.h"
#include <stdio.h>
#include "../exacto/exacto.h"

void testear_local( int maxN, int step, int cantTests, int V ) {

	ofstream opt;
	char file[256];
	sprintf(file,"opt_local%d.data",V);
	opt.open(file);
	
	int init = 0;
	while (init < V) {init += step;}
    for (int n=init; n<=maxN; n+=step) {
		cout << "Test V = " << V << "; n = " << n;
		double acum = 0;
		int elmax = -pow(n,2);
		int elmin = 1;
		int todos[cantTests];
	
		for (int k=0; k<cantTests; k++) {
			cout << ".";
			Solucion inicial = make_pair(vector<bool>(n,false),0);

			grafo g = grafo(n);
			g.generar_aristas_aleatorias();

				float optimo = exacto(g).second;
		//-> Resolver_local:
				float result = local(g, inicial, V).second;
		//->
				result -= optimo;
				//Convertir a Porcentaje:
				result = 100*result/optimo;

			acum += result;
			todos[k] = result;
			if (result > elmax) elmax = result;
			if (result < elmin) elmin = result;
		}
		cout << endl;

		double media = acum/cantTests;
		double desvioEstandar = 0;
		for (int l =0; l<cantTests; ++l) {
			double d = todos[l]-media;
			desvioEstandar += (d*d);
		}
		desvioEstandar = sqrt(desvioEstandar/(cantTests-1));
		float index = n + (V/2.0) -1;
		opt << index << " " << fixed << media << " " << fixed <<
		media-desvioEstandar << " " << fixed << media + desvioEstandar <<
		" " << fixed << elmax << " " << fixed << elmin << endl;
	}

	opt.close();
}


int main(int argc, const char* argv[]) {
	int maxN = atoi(argv[1]);
	int step = atoi(argv[2]);
	int cantTests = atoi(argv[3]);

	testear_local(maxN, step, cantTests, 1);
	testear_local(maxN, step, cantTests, 2);
	testear_local(maxN, step, cantTests, 3);
	system("gnuplot opt_local.gnuplot");
    
	return 0;
}
