#include "exacto.h"

int MAX_N_SIN_PODAS = 24;

void testear_exacto( int maxN, int step, int cantTests ) {
	
	ofstream tiempos;
	tiempos.open("exacto.data");
	
	for (int n=step; n<=maxN; n+=step) {
		cout << "n = " << n;
		double acum = 0;
		double acumSP = 0;
		double elmax = 0;
		double elmin = 1E+37;
		double elmaxSP = 0;
		double elminSP = 1E+37;
		double todos[cantTests];
		double todosSP[cantTests];
			
		for (int k=0; k<cantTests; k++) {
			cout << ".";
			grafo g = grafo(n);
			g.generar_aristas_aleatorias();

			double duracion;
			if (n<=MAX_N_SIN_PODAS) {
				iniciarTimer();
			//-> Resolver_exacto sin poda:
				exacto_sin_poda(g);
			//->
				duracion = finalizarTimer();
			
				acumSP += duracion;
				todosSP[k] = duracion;
				if (duracion > elmaxSP) elmaxSP = duracion;
				if (duracion < elminSP) elminSP = duracion;

			}

			iniciarTimer();
		//-> Resolver_exacto:
			exacto(g);
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

		double mediaSP = acumSP/cantTests;
		double desvioEstandarSP = 0;
		if (n<=MAX_N_SIN_PODAS) {
			for (int l =0; l<cantTests; ++l) {
				double d = todosSP[l]-mediaSP;
				desvioEstandarSP += (d*d);
			}
			desvioEstandarSP = sqrt(desvioEstandarSP/(cantTests-1));
		}
		tiempos << n << " " << fixed << media << " " << fixed << media-desvioEstandar
			<< " " << fixed << media + desvioEstandar <<
			" " << fixed << elmax << " " << fixed << elmin;
		if (n<=MAX_N_SIN_PODAS) {
			tiempos << " " << fixed << mediaSP << " " << fixed <<
			mediaSP-desvioEstandarSP << " " << fixed << mediaSP + desvioEstandarSP <<
			" " << fixed << elmaxSP << " " << fixed << elminSP;
		}
		tiempos << endl;
	}
	
	tiempos.close();
	system("gnuplot exacto.gnuplot");
}


int main(int argc, const char* argv[]) {
	int maxN = atoi(argv[1]);
	int step = atoi(argv[2]);
	int cantTests = atoi(argv[3]);
	
	testear_exacto(maxN, step, cantTests);
	
	return 0;
}
