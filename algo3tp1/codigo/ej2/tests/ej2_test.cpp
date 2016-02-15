#include <cmath>
#include <cstdlib>
#include "../../timer.h"
#include "../ej2.h"
using namespace std;

int main(int argc, const char* argv[]){

	srand(time(NULL));
	
	int maxN = atoi(argv[1]);
	int step = atoi(argv[2]); 
	int cantTests = atoi(argv[3]);
		
		// n es la cantidad de cursos que tiene un cronograma
		for(int n = step; n <= maxN; n+=step){
		
			//Variables para contar el tiempo
			double acum = 0;
			double elmax = 0;
			double elmin = 1E+37;
			double todos[cantTests];
		
			//Cantidad de tests que genera para ESE N
			for(int i = 0; i<cantTests; ++i){

				// Vector de cursos disponibles
				Cronograma cursos;
				// genero la i-esima instancia de un cronograma con n cursos
				for(int j = 0; j < n; ++j){
					int fecha_a = rand()%30;
					int fecha_b = rand()%30;
					if(fecha_b < fecha_a) swap(fecha_a,fecha_b);
					Curso p(Fechas(fecha_a,fecha_b),i+1);					
					cursos.push_back(p);
				}
				
				Cronograma res;
				double duracion;
				iniciarTimer();
				res = resolver(cursos);
				duracion = finalizarTimer(n);
			
				acum+= duracion;
				todos[i] = duracion;
				if (duracion > elmax) elmax = duracion;
				if (duracion < elmin) elmin = duracion;

			}
			
			double media = acum/cantTests;
		
			double desvioEstandar = 0;
			for (int l=0; l<cantTests; ++l) {
				double d = todos[l]-media;
				desvioEstandar += (d*d);
			}
			desvioEstandar = sqrt(desvioEstandar/(cantTests-1));
		
			cout << n << " " << fixed << media << " " << fixed << media-desvioEstandar;
			cout << " " << fixed << media + desvioEstandar << endl;

		}
	return 0;
}
