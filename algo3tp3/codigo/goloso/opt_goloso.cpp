#include "goloso.h"
#include "../exacto/exacto.h"

void testear_goloso( int maxN, int step, int cantTests ) {
	
	ofstream opt;
	opt.open("opt_goloso.data");
	
    for (int n=step; n<=maxN; n+=step) {
		cout << "n = " << n;
		double acum = 0;
		int elmax = -pow(n,2);
		int elmin = 1;
		int todos[cantTests];
	
		for (int k=0; k<cantTests; k++) {
			cout << ".";
			grafo g = grafo(n);
			g.generar_aristas_aleatorias();

				float optimo = exacto(g).second;
			//-> Resolver_goloso:
				float result = goloso(g).second;
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
		opt << n << " " << fixed << media << " " << fixed <<
		media-desvioEstandar << " " << fixed << media + desvioEstandar <<
		" " << fixed << elmax << " " << fixed << elmin << endl;
	}
	
	opt.close();
	system("gnuplot opt_goloso.gnuplot");
}


int main(int argc, const char* argv[]) {
	int maxN = atoi(argv[1]);
	int step = atoi(argv[2]);
	int cantTests = atoi(argv[3]);
	
	testear_goloso(maxN, step, cantTests);
    
	return 0;
}
