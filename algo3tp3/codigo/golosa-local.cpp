#include "goloso/goloso.h"
#include "tabu/tabu.h"
#include "local/local.h"
#include "exacto/exacto.h"

void testear( int maxN, int step, int cantTests ) {
	
	ofstream Ogoloso;
	Ogoloso.open("comp_goloso.data");
	ofstream Olocal;
	Olocal.open("comp_local.data");
	ofstream Olocal2;
	Olocal2.open("comp_local2.data");
	
    for (int n=step; n<=maxN; n+=step) {
		cout << "n = " << n;
		double acum_g = 0;
		double acum_l = 0;
		double acum_l2 = 0;
		int elmax_g = -pow(n,2);
		int elmax_l = -pow(n,2);
		int elmax_l2 = -pow(n,2);
		int elmin_g = 1;
		int elmin_l = 1;
		int elmin_l2 = 1;
		int todos_g[cantTests];
		int todos_l[cantTests];
		int todos_l2[cantTests];
	
		for (int k=0; k<cantTests; k++) {
			grafo g = grafo(n);
			g.generar_aristas_aleatorias();
			Solucion si = make_pair(vector<bool>(n,false),0);

				float optimo = exacto(g).second;
			//-> Resolver:
				float result_l = local(g,si,1).second;
				si = goloso(g);
				float result_g = si.second;
				float result_l2 = local(g,si,1).second;
			//->
				result_g -= optimo;
				//Convertir a Porcentaje:
				result_g = 100*result_g/optimo;

				result_l -= optimo;
				//Convertir a Porcentaje:
				result_l = 100*result_l/optimo;

				result_l2 -= optimo;
				//Convertir a Porcentaje:
				result_l2 = 100*result_l2/optimo;

			acum_g += result_g;
			acum_l += result_l;
			acum_l2 += result_l2;
			todos_g[k] = result_g;
			todos_l[k] = result_l;
			todos_l2[k] = result_l2;
			if (result_g > elmax_g) elmax_g = result_g;
			if (result_l > elmax_l) elmax_l = result_l;
			if (result_l2 > elmax_l2) elmax_l2 = result_l2;
			if (result_g < elmin_g) elmin_g = result_g;
			if (result_l < elmin_l) elmin_l = result_l;
			if (result_l2 < elmin_l2) elmin_l2 = result_l2;
		}
		cout << endl;
		double media;
		double desvioEstandar;
		float index;

		media = acum_g/cantTests;
		desvioEstandar = 0;
		for (int l =0; l<cantTests; ++l) {
			double d = todos_g[l]-media;
			desvioEstandar += (d*d);
		}
		desvioEstandar = sqrt(desvioEstandar/(cantTests-1));
	index = n - 0.3*step;
		Ogoloso << index << " " << fixed << media << " " << fixed <<
		media-desvioEstandar << " " << fixed << media + desvioEstandar <<
		" " << fixed << elmax_g << " " << fixed << elmin_g << endl;

		media = acum_l/cantTests;
		desvioEstandar = 0;
		for (int l =0; l<cantTests; ++l) {
			double d = todos_l[l]-media;
			desvioEstandar += (d*d);
		}
		desvioEstandar = sqrt(desvioEstandar/(cantTests-1));
	index = n;
		Olocal << index << " " << fixed << media << " " << fixed <<
		media-desvioEstandar << " " << fixed << media + desvioEstandar <<
		" " << fixed << elmax_l << " " << fixed << elmin_l << endl;

		media = acum_l2/cantTests;
		desvioEstandar = 0;
		for (int l =0; l<cantTests; ++l) {
			double d = todos_l2[l]-media;
			desvioEstandar += (d*d);
		}
		desvioEstandar = sqrt(desvioEstandar/(cantTests-1));
	index = n + 0.3*step;
		Olocal2 << index << " " << fixed << media << " " << fixed <<
		media-desvioEstandar << " " << fixed << media + desvioEstandar <<
		" " << fixed << elmax_l2 << " " << fixed << elmin_l2 << endl;
	}
	
	Ogoloso.close();
	Olocal.close();
	Olocal2.close();
	system("gnuplot golosa-local.gnuplot");
}


int main(int argc, const char* argv[]) {
	cout << ":)" << endl;
	int maxN = atoi(argv[1]);
	int step = atoi(argv[2]);
	int cantTests = atoi(argv[3]);
	
	testear(maxN, step, cantTests);
    
	return 0;
}
