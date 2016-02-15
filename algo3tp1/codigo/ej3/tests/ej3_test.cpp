#include <cmath>
#include <cstdlib>
#include <list>
#include "../ej3.h"
#include "../../timer.h"
using namespace std;

#define MAX_N_SIN_PODAS	16
list<int> descomposicion_en_primos(int n);
void evaluar_en_funcion_de_casilleros_vacios(int maxN, int step, int cantTests);
void evaluar_en_funcion_de_casilleros_totales(int maxN, int step, int cantTests);

int main(int argc, const char* argv[]){
	srand(time(NULL));
	
	int maxN = atoi(argv[1]);
	int step = atoi(argv[2]); 
	int cantTests = atoi(argv[3]);

	if (maxN > MAXSIZE*MAXSIZE) maxN = MAXSIZE*MAXSIZE-5;

	evaluar_en_funcion_de_casilleros_vacios(maxN, step, cantTests);

	evaluar_en_funcion_de_casilleros_totales(maxN, step, cantTests);

	return 0;
}

void evaluar_en_funcion_de_casilleros_vacios(int maxN, int step, int cantTests) {
		// n es la cantidad de casilleros vacios (ni pared ni importante)
		// El ancho y el alto del piso se calculan en función de ese n
		for(int n = step; n <= maxN; n+=step){

			//Variables para contar el tiempo
			double acum = 0;
			double elmax = 0;
			double elmin = 1E+37;
			double todos[cantTests];
			double acum_sp = 0;
			double elmax_sp = 0;
			double elmin_sp = 1E+37;
			double todos_sp[cantTests];

			//Cantidad de tests que genera para ESE N
			for(int i = 0; i<cantTests; ++i){

				// Ancho y Alto
				height = sqrt(n) +1;
				width = n/sqrt(n) +1;
				int h = height;
				int w = width;

				// creo un piso de hxw espacios vacios
				int j, k, l;
				int s = h*w - n;
				for(j = 0; j < h; j++){
					for(k = 0; k < w; k++) {
						pisoMejor[j][k] = VACIO;
					}
				}

				// asigno s (hxw - s) espacios pared o importante
				for (l=0; l<s; l++) {

					int p = w*(rand()%w) + rand()%h;
					while (pisoMejor[p/w][p%w] !=VACIO) {
						p= (p+1)%(w*h);
					}
					int c = rand()%14;
					pisoMejor[p/w][p%w] = (c>=3 ? PARED : IMPORTANTE);
				}

				// creo el otro piso y las listas de vacios e importantes
				cantVacias = 0; cantImportantes = 0;
				for(j = 0; j < h; j++){
					for(k = 0; k < w; k++) {
						pisoActual[j][k] = pisoMejor[j][k];
						if (pisoMejor[j][k] == VACIO) { 
							vacias[cantVacias] = Posicion(j,k);
							cantVacias++;
						} else if (pisoMejor[j][k] == IMPORTANTE) {
							importantes[cantImportantes] = Posicion(j,k);
							cantImportantes++;
						}
					}
				}

				// otras variables
				maxCosto = cantVacias * PRECIO4;
				costoMejor = maxCosto+1;
				costoActual = 0;

				double duracion;
				iniciarTimer();
				obtener_mejor();
				duracion = finalizarTimer(cantVacias);

		//	Esto hace que solo mida tiempos de corridas en las que encontró la
		//	solución (cuando no encuentra solución termina en seguida), pero
		//	puede ser que nunca termine (nada asegura que termine). 
		//		if (costoMejor > maxCosto) {
		//			i--;
		//		} else {
					acum+= duracion;
					todos[i] = duracion;
					if (duracion > elmax) elmax = duracion;
					if (duracion < elmin) elmin = duracion;
		//		}

				if (n <= MAX_N_SIN_PODAS) {

					// reinicio para calcular otra vez
					reiniciar_piso();

					iniciarTimer();
					obtener_mejor_sin_podas();
					duracion = finalizarTimer(cantVacias);

					acum_sp+= duracion;
					todos_sp[i] = duracion;
					if (duracion > elmax_sp) elmax_sp = duracion;
					if (duracion < elmin_sp) elmin_sp = duracion;
				}

			}
			
			double media = acum/cantTests;
		
			double desvioEstandar = 0;
			for (int l=0; l<cantTests; ++l) {
				double d = todos[l]-media;
				desvioEstandar += (d*d);
			}
			desvioEstandar = sqrt(desvioEstandar/cantTests);
		
			cout << n << " " << fixed << media << " " << fixed << media-desvioEstandar;
			cout << " " << fixed << media + desvioEstandar << endl;
			cout << n << " " << fixed << elmin << " " << fixed << elmax << endl;

				if (n <= MAX_N_SIN_PODAS) {
					media = acum_sp/cantTests;
		
					desvioEstandar = 0;
					for (int l=0; l<cantTests; ++l) {
						double d = todos_sp[l]-media;
						desvioEstandar += (d*d);
					}
					desvioEstandar = sqrt(desvioEstandar/(cantTests-1));
		
					cout << n << " " << fixed << media << " " << fixed << media-desvioEstandar;
					cout << " " << fixed << media + desvioEstandar << endl;
					cout << n << " " << fixed << elmin_sp << " " << fixed << elmax_sp << endl;

				}
		}
}

void evaluar_en_funcion_de_casilleros_totales(int maxN, int step, int cantTests) {
		for(int n = step; n <= maxN; n+=step){
			//Variables para contar el tiempo
			double acum = 0;
			double elmax = 0;
			double elmin = 1E+37;
			double todos[cantTests];
			double acum_sp = 0;
			double elmax_sp = 0;
			double elmin_sp = 1E+37;
			double todos_sp[cantTests];

			//Cantidad de tests que genera para ESE N
			for(int i = 0; i<cantTests; ++i){

				// Ancho y Alto
				list<int> lp = descomposicion_en_primos(n);
				if (lp.size() == 1) {
					height = 1;
					width = n;
				} else if (lp.size() == 2) {
					height = lp.front();
					width = n/height;
				} else {
					int v = lp.size()-1;
					v = rand()%v;
					height = 1;
					for (list<int>::const_iterator it = lp.begin(); (v>=0) && (it!=lp.end()); ++it) {
						height *= *it;
						v--;
					}
					width = n/height;
				}
				int h = height;
				int w = width;

				// creo los pisos de hxw y las listas de vacios e importantes
				int j, k;
				cantVacias = 0; cantImportantes = 0;
				for(k = 0; k < h; k++){
					for(j = 0; j < w; j++) {
						int r = rand()%9;
						if (r>6) pisoMejor[j][k] = PARED;
						else if (r==6) {
							pisoMejor[j][k] = IMPORTANTE;
							importantes[cantImportantes] = Posicion(j,k);
							cantImportantes++;
						} else {
							pisoMejor[j][k] = VACIO;
							vacias[cantVacias] = Posicion(j,k);
							cantVacias++;
						}
						pisoActual[j][k] = pisoMejor[j][k];
					}
				}

				// otras variables
				maxCosto = cantVacias * PRECIO4;
				costoMejor = maxCosto+1;
				costoActual = 0;

				double duracion;
				iniciarTimer();
				obtener_mejor();
				duracion = finalizarTimer(n);

		//	Esto hace que solo mida tiempos de corridas en las que encontró la
		//	solución (cuando no encuentra solución termina en seguida), pero
		//	puede ser que nunca termine (nada asegura que termine). 
		//		if (costoMejor > maxCosto) {
		//			i--;
		//		} else {
					acum+= duracion;
					todos[i] = duracion;
					if (duracion > elmax) elmax = duracion;
					if (duracion < elmin) elmin = duracion;
		//		}

				if (n <= MAX_N_SIN_PODAS) {

					// reinicio para calcular otra vez
					reiniciar_piso();

					iniciarTimer();
					obtener_mejor_sin_podas();
					duracion = finalizarTimer(n);

					acum_sp+= duracion;
					todos_sp[i] = duracion;
					if (duracion > elmax_sp) elmax_sp = duracion;
					if (duracion < elmin_sp) elmin_sp = duracion;
				}

			}
			
			double media = acum/cantTests;
		
			double desvioEstandar = 0;
			for (int l=0; l<cantTests; ++l) {
				double d = todos[l]-media;
				desvioEstandar += (d*d);
			}
			desvioEstandar = sqrt(desvioEstandar/cantTests);
		
			cout << n << " " << fixed << media << " " << fixed << media-desvioEstandar;
			cout << " " << fixed << media + desvioEstandar << endl;
			cout << n << " " << fixed << elmin << " " << fixed << elmax << endl;

				if (n <= MAX_N_SIN_PODAS) {
					media = acum_sp/cantTests;
		
					desvioEstandar = 0;
					for (int l=0; l<cantTests; ++l) {
						double d = todos_sp[l]-media;
						desvioEstandar += (d*d);
					}
					desvioEstandar = sqrt(desvioEstandar/cantTests);
		
					cout << n << " " << fixed << media << " " << fixed << media-desvioEstandar;
					cout << " " << fixed << media + desvioEstandar << endl;
					cout << n << " " << fixed << elmin_sp << " " << fixed << elmax_sp << endl;

				}
		}
}

list<int> descomposicion_en_primos(int n) {
	list<int> result = list<int>();
	for (int i=2; i<=n/2; i++) {
		if (n%i==0) {
			result = descomposicion_en_primos(n/i);
			result.push_back(i);
			break;
		}
	}
	if (result.empty()) result.push_back(n);
	return result;
}
