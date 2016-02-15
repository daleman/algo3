#include "tabu.h"
#include <stdio.h>
#include "../exacto/exacto.h"

void testear_tabu( int maxN, int step, int cantTests, char test, float v) {
	int V; float logT;
	ofstream opt;
	char file[256];
	if (test=='V') {
		V = v;
		logT = 1;
		sprintf(file,"opt_tabu_V_%d.data",V);
	} else {
		V = 1;
		logT = v;
		sprintf(file,"opt_tabu_T_%f.data",logT);
	}

	opt.open(file);

	int init = 0;
	while (init < V) {init += step;}
    for (int n=init; n<=maxN; n+=step) {
		if (test=='V') cout << "Test V = " << V;
		else cout << "Test logT = " << logT;
		cout << "; n = " << n;
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
				float result = tabu(g, inicial, n, pow(n,logT), V).second;
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
		float index = n;
		if (test=='V') index += (V/2.0) -1;
		else index += log(logT);
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

	//V= 1/2/3
	testear_tabu(maxN, step, cantTests, 'V', 1);
	testear_tabu(maxN, step, cantTests, 'V', 2);
	testear_tabu(maxN, step, cantTests, 'V', 3);

	//T= logn/n/n²
	testear_tabu(maxN, step, cantTests, 'T', 0.5);
	testear_tabu(maxN, step, cantTests, 'T', 1);
	testear_tabu(maxN, step, cantTests, 'T', 2);

	system("gnuplot opt_tabu.gnuplot");
    
	return 0;
}
