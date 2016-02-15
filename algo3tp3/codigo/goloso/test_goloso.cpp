#include "goloso.h"

void testear_goloso( int maxN, int step, int cantTests ) {
	
	ofstream tiempos;
	tiempos.open("goloso.data");
	
    for (int n=step; n<=maxN; n+=step) {
		cout << "n = " << n;
		double acum = 0;
		double elmax = 0;
		double elmin = 1E+37;
		double todos[cantTests];
			
		for (int k=0; k<cantTests; k++) {
			cout << ".";
			grafo g = grafo(n);
			g.generar_aristas_aleatorias();

			double duracion;
			iniciarTimer();
			//-> Resolver_goloso:
				goloso(g);
			//->
			duracion = finalizarTimer();
			
			acum += duracion;
			todos[k] = duracion;
			if (duracion > elmax) elmax = duracion;
			if (duracion < elmin) elmin = duracion;
		}
		cout << endl;

		double media = acum/cantTests;
		double desvioEstandar = 0;
		for (int l =0; l<cantTests; ++l) {
			double d = todos[l]-media;
			desvioEstandar += (d*d);
		}
		desvioEstandar = sqrt(desvioEstandar/(cantTests-1));
		tiempos << n << " " << fixed << media << " " << fixed <<
		media-desvioEstandar << " " << fixed << media + desvioEstandar <<
		" " << fixed << elmax << " " << fixed << elmin << endl;
	}
	
	tiempos.close();
	system("gnuplot goloso.gnuplot");
}


int main(int argc, const char* argv[]) {
	int maxN = atoi(argv[1]);
	int step = atoi(argv[2]);
	int cantTests = atoi(argv[3]);
	
	testear_goloso(maxN, step, cantTests);
    
	return 0;
}
