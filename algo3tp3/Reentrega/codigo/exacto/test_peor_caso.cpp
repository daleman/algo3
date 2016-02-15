#include "exacto.h"

int MAX_N_SIN_PODAS = 30;

void testear_exacto( int maxN, int step, int cantTests ) {
	
	ofstream tiempos2p;
	ofstream tiempos;
	ofstream tiempossp;
	tiempos2p.open("peor2p.data");
	tiempos.open("peor.data");
	tiempossp.open("peorsp.data");
	
	for (int n=step; n<=maxN; n+=step) {
		cout << "n = " << n;
			
		cout << ".";
		grafo g = grafo(n);
		g.generar_completo();

		double duracion;

			iniciarTimer();
		//-> Resolver_exacto 2 podas:
			exacto_2p(g);
		//->
			duracion = finalizarTimer();
			tiempos2p << n << " " << fixed << duracion << endl;

		if (n<=MAX_N_SIN_PODAS) {
			iniciarTimer();
		//-> Resolver_exacto sin poda:
			exacto_sin_poda(g);
		//->
			duracion = finalizarTimer();
			tiempossp << n << " " << fixed << duracion << endl;
		}

		iniciarTimer();
	//-> Resolver_exacto:
		exacto(g);
	//->
		duracion = finalizarTimer();
		tiempos << n << " " << fixed << duracion << endl;
		
		cout << endl;
	}
	
	tiempos2p.close();
	tiempos.close();
	tiempossp.close();
	system("gnuplot peor.gnuplot");
}


int main(int argc, const char* argv[]) {
	int maxN = atoi(argv[1]);
	int step = atoi(argv[2]);
	int cantTests = atoi(argv[3]);
	
	testear_exacto(maxN, step, cantTests);
	
	return 0;
}
