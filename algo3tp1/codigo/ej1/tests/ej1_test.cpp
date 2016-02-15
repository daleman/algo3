#include <cmath>
#include <cstdlib>
#include "../../timer.h"
#include "../ej1.h"
using namespace std;

int main(int argc, const char* argv[]){

	srand(time(NULL));

	int maxN = atoi(argv[1]);
	int step = atoi(argv[2]);
	int cantTests = atoi(argv[3]);

		// n es la cantidad de paquetes
		for(int n = step; n <= maxN; n+=step){

			//Variables para contar el tiempo
			double acum = 0;
			double elmax = 0;
			double elmin = 1E+37;
			double todos[cantTests];

			//Cantidad de tests que genera para ESE N
			for(int i = 0; i<cantTests; ++i){

				int maxPeso = n+12 + rand()%(6*n);
				// Array de paquetes
				int paquetes[n];
				// Lista de camiones
				priority_queue<Camion> camiones;
				// genero la i-esima instancia de n paquetes
				for(int j = 0; j < n; ++j){
					paquetes[j] = rand() % maxPeso + 1;
				}

				double duracion;
				iniciarTimer();
				resolver(camiones, maxPeso, paquetes, n);
				duracion = finalizarTimer(n);

				acum+= duracion;
				todos[i] = duracion;
				if (duracion > elmax) elmax = duracion;
				if (duracion < elmin) elmin = duracion;

			}
			
			double media = acum/cantTests;
		
			double desvioEstandar = 0;
			for (int l =0; l<cantTests; ++l) {
				double d = todos[l]-media;
				desvioEstandar += (d*d);
			}
			desvioEstandar = sqrt(desvioEstandar/(cantTests-1));
		
			cout << n << " " << fixed << media << " " << fixed << media-desvioEstandar;
			cout << " " << fixed << media + desvioEstandar << endl;
	
		}
	return 0;
}
