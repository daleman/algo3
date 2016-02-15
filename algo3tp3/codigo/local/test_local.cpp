#include "local.h"
#include <stdio.h>

int MAX_N_V_2 = 600;
int MAX_N_V_3 = 200;

void complejidad(int n);
void testear_local( int maxN, int step, int cantTests, int V ) {
	if ((V==2) && (maxN > MAX_N_V_2)) {
		maxN = MAX_N_V_2;
	}
	if ((V==3) && (maxN > MAX_N_V_3)) {
		maxN = MAX_N_V_3;
	}

	ofstream tiempos;
	char file[256];
	sprintf(file,"local%d.data",V);
	tiempos.open(file);
	
	int init = 0;
	while (init < V) {init += step;}
    for (int n=init; n<=maxN; n+=step) {
		cout << "Test V = " << V << "; n = " << n;
		double acum = 0;
		double elmax = 0;
		double elmin = 1E+37;
		double todos[cantTests];
	
		for (int k=0; k<cantTests; k++) {
			cout << ".";
			Solucion inicial = make_pair(vector<bool>(n,false),0);

			grafo g = grafo(n);
			g.generar_aristas_aleatorias();

			double duracion;
			iniciarTimer();
		//-> Resolver_local:
				local(g, inicial, V);
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
		float index = n + (V/4.0) -0.5;
		tiempos << index << " " << fixed << media << " " << fixed <<
		media-desvioEstandar << " " << fixed << media + desvioEstandar <<
		" " << fixed << elmax << " " << fixed << elmin << endl;
	}

	tiempos.close();
}


int main(int argc, const char* argv[]) {
	int maxN = atoi(argv[1]);
	int step = atoi(argv[2]);
	int cantTests = atoi(argv[3]);

	complejidad(maxN);
	testear_local(maxN, step, cantTests, 1);
	testear_local(maxN, step, cantTests, 2);
	testear_local(maxN, step, cantTests, 3);
	system("gnuplot local.gnuplot");
    
	return 0;
}

void complejidad(int n) {
	ofstream tiempos;
	tiempos.open("complex.data");
	for (int i=1; i<=n; i++) {
		double timea = 0.00000000005;
		double timeb = 0.00000001;
		double timec = 0.0005;
		double time1 = timea*i*i*i*i+timeb*i*i+timec*i;
		double time2 = timea*(i>=2 ? cant_vecinos(i,2)*2 : 0)*i*i*i+timeb*i*i+timec*i;
		double time3 = timea*(i>=3 ? cant_vecinos(i,3)*3 : 0)*i*i*i+timeb*i*i+timec*i;
		tiempos << i << " " << fixed << time1 << " " << fixed << time2 << " " << fixed << time3 << endl;
	}
	tiempos.close();
}
