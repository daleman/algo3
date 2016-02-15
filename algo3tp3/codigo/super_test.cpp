#include "goloso/goloso.h"
#include "tabu/tabu.h"
#include "local/local.h"
#include "exacto/exacto.h"

void testear( int maxN, int step, int cantTests ) {

	ofstream Oexacto;
	Oexacto.open("exacto.data");	
	ofstream Ogoloso;
	Ogoloso.open("goloso.data");
	ofstream Olocal;
	Olocal.open("local.data");
	ofstream Olocal2;
	Olocal2.open("local2.data");
	ofstream Otabu;
	Otabu.open("tabu.data");
	ofstream Otabu2;
	Otabu2.open("tabu2.data");
	
    for (int n=step; n<=maxN; n+=step) {
		cout << "n = " << n;
		double acum_e = 0;
		double acum_g = 0;
		double acum_l = 0;
		double acum_l2 = 0;
		double acum_t = 0;
		double acum_t2 = 0;
		double elmax_e = 0;
		double elmax_g = 0;
		double elmax_l = 0;
		double elmax_l2 = 0;
		double elmax_t = 0;
		double elmax_t2 = 0;
		double elmin_e = 1E+37;
		double elmin_g = 1E+37;
		double elmin_l = 1E+37;
		double elmin_l2 = 1E+37;
		double elmin_t = 1E+37;
		double elmin_t2 = 1E+37;
		double todos_e[cantTests];
		double todos_g[cantTests];
		double todos_l[cantTests];
		double todos_l2[cantTests];
		double todos_t[cantTests];
		double todos_t2[cantTests];
	
		for (int k=0; k<cantTests; k++) {
			grafo g = grafo(n);
			g.generar_aristas_aleatorias();
			Solucion si = make_pair(vector<bool>(n,false),0);
			double duracion;

			iniciarTimer();
				exacto(g);
			duracion = finalizarTimer();
				acum_e += duracion;
				todos_e[k] = duracion;
				if (duracion > elmax_e) elmax_e = duracion;
				if (duracion < elmin_e) elmin_e = duracion;

			iniciarTimer();
				goloso(g);
			duracion = finalizarTimer();
				acum_g += duracion;
				todos_g[k] = duracion;
				if (duracion > elmax_g) elmax_g = duracion;
				if (duracion < elmin_g) elmin_g = duracion;

			iniciarTimer();
				if (n>=2) local(g,si,2);
			duracion = finalizarTimer();
				acum_l += duracion;
				todos_l[k] = duracion;
				if (duracion > elmax_l) elmax_l = duracion;
				if (duracion < elmin_l) elmin_l = duracion;

			iniciarTimer();
				if (n>=3) local(g,si,3);
			duracion = finalizarTimer();
				acum_l2 += duracion;
				todos_l2[k] = duracion;
				if (duracion > elmax_l2) elmax_l2 = duracion;
				if (duracion < elmin_l2) elmin_l2 = duracion;

			iniciarTimer();
				tabu(g,si,n,n,1);
			duracion = finalizarTimer();
				acum_t += duracion;
				todos_t[k] = duracion;
				if (duracion > elmax_t) elmax_t = duracion;
				if (duracion < elmin_t) elmin_t = duracion;

			iniciarTimer();
				if (n>=2) tabu(g,si,n,n,2);
			duracion = finalizarTimer();
				acum_t2 += duracion;
				todos_t2[k] = duracion;
				if (duracion > elmax_t2) elmax_t2 = duracion;
				if (duracion < elmin_t2) elmin_t2 = duracion;
		}
		cout << endl;
		double media;
		double desvioEstandar;
		float index;

		media = acum_e/cantTests;
		desvioEstandar = 0;
		for (int l =0; l<cantTests; ++l) {
			double d = todos_e[l]-media;
			desvioEstandar += (d*d);
		}
		desvioEstandar = sqrt(desvioEstandar/(cantTests-1));
	index = n - 0.5*step;
		Oexacto << index << " " << fixed << media << " " << fixed <<
		media-desvioEstandar << " " << fixed << media + desvioEstandar <<
		" " << fixed << elmax_e << " " << fixed << elmin_e << endl;

		media = acum_g/cantTests;
		desvioEstandar = 0;
		for (int l =0; l<cantTests; ++l) {
			double d = todos_g[l]-media;
			desvioEstandar += (d*d);
		}
		desvioEstandar = sqrt(desvioEstandar/(cantTests-1));
	index = n - 0.25*step;
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
	index = n + 0.25*step;
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
	index = n + 0.5*step;
		Olocal2 << index << " " << fixed << media << " " << fixed <<
		media-desvioEstandar << " " << fixed << media + desvioEstandar <<
		" " << fixed << elmax_l2 << " " << fixed << elmin_l2 << endl;

		media = acum_t/cantTests;
		desvioEstandar = 0;
		for (int l =0; l<cantTests; ++l) {
			double d = todos_t[l]-media;
			desvioEstandar += (d*d);
		}
		desvioEstandar = sqrt(desvioEstandar/(cantTests-1));
	index = n - 0.15*step;
		Otabu << index << " " << fixed << media << " " << fixed <<
		media-desvioEstandar << " " << fixed << media + desvioEstandar <<
		" " << fixed << elmax_t << " " << fixed << elmin_t << endl;

		media = acum_t2/cantTests;
		desvioEstandar = 0;
		for (int l =0; l<cantTests; ++l) {
			double d = todos_t2[l]-media;
			desvioEstandar += (d*d);
		}
		desvioEstandar = sqrt(desvioEstandar/(cantTests-1));
	index = n + 0.15*step;
		Otabu2 << index << " " << fixed << media << " " << fixed <<
		media-desvioEstandar << " " << fixed << media + desvioEstandar <<
		" " << fixed << elmax_t2 << " " << fixed << elmin_t2 << endl;
	}
	Oexacto.close();	
	Ogoloso.close();
	Olocal.close();
	Olocal2.close();
	Otabu.close();
	Otabu2.close();
	system("gnuplot super_test.gnuplot");
}


int main(int argc, const char* argv[]) {
	cout << ":)" << endl;
	int maxN = atoi(argv[1]);
	int step = atoi(argv[2]);
	int cantTests = atoi(argv[3]);
	
	testear(maxN, step, cantTests);
    
	return 0;
}
