#include "exacto.h"

int MAX_N_SIN_PODAS = 30;

void testear_exacto( int maxN, int step, int cantTests ) {
	
	ofstream tiempos2p;
	ofstream tiempos;
	ofstream tiempossp;
	tiempos2p.open("exacto2p.data");
	tiempos.open("exacto.data");
	tiempossp.open("exactosp.data");
	
	for (int n=step; n<=maxN; n+=step) {
		cout << "n = " << n;
		double acum2P = 0;
		double acum = 0;
		double acumSP = 0;
		double elmax2P = 0;
		double elmin2P = 1E+37;
		double elmax = 0;
		double elmin = 1E+37;
		double elmaxSP = 0;
		double elminSP = 1E+37;
		double todos2P[cantTests];
		double todos[cantTests];
		double todosSP[cantTests];
			
		for (int k=0; k<cantTests; k++) {
			cout << ".";
			grafo g = grafo(n);
			g.generar_aristas_aleatorias();

			double duracion;

			iniciarTimer();
		//-> Resolver_exacto 2 podas:
			exacto_2p(g);
		//->
			duracion = finalizarTimer();
		
			acum2P += duracion;
			todos2P[k] = duracion;
			if (duracion > elmax2P) elmax2P = duracion;
			if (duracion < elmin2P) elmin2P = duracion;

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

		double media2P = acum2P/cantTests;
		double desvioEstandar2P = 0;
		for (int l =0; l<cantTests; ++l) {
			double d = todos2P[l]-media2P;
			desvioEstandar2P += (d*d);
		}
		desvioEstandar2P = sqrt(desvioEstandar2P/(cantTests-1));

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

		tiempos2p << n << " " << fixed << media2P << " " << fixed <<
		media2P-desvioEstandar2P << " " << fixed << media2P + desvioEstandar2P <<
		" " << fixed << elmax2P << " " << fixed << elmin2P << endl;

		tiempos << n << " " << fixed << media << " " << fixed << media-desvioEstandar
			<< " " << fixed << media + desvioEstandar <<
			" " << fixed << elmax << " " << fixed << elmin << endl;
		if (n<=MAX_N_SIN_PODAS) {
			tiempossp << n << " " << fixed << mediaSP << " " << fixed <<
			mediaSP-desvioEstandarSP << " " << fixed << mediaSP + desvioEstandarSP <<
			" " << fixed << elmaxSP << " " << fixed << elminSP << endl;
		}
	}
	
	tiempos2p.close();
	tiempos.close();
	tiempossp.close();
	system("gnuplot exacto.gnuplot");
}


int main(int argc, const char* argv[]) {
	int maxN = atoi(argv[1]);
	int step = atoi(argv[2]);
	int cantTests = atoi(argv[3]);
	
	testear_exacto(maxN, step, cantTests);
	
	return 0;
}
