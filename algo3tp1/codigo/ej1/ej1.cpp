#include "ej1.h"
using namespace std;

int main(){

	int maxPeso, nPaquetes, i, p;
	while (cin >> maxPeso >> nPaquetes) {

		// Array de paquetes en orden de entrada
		int paquetes[nPaquetes];

		// Lista de camiones usados. El primero de la lista es
		// el que tiene más lugar, es decir el que tiene mayor
		// capacidad restante (Camion.first)
		priority_queue<Camion> camiones;

		// Inicializar: Recibo cada paquete de la entrada
		for (i = 0; i < nPaquetes; i++) {
			cin >> p;
			paquetes[i] = p;
		}

		// Procesar: tomo cada paquete y lo ubico en un camión
		// según el método Pascual
		resolver(camiones, maxPeso, paquetes, nPaquetes);

		// Imprimir resultado
		mostrar_camiones(maxPeso, camiones);
	}

	return 0;

}

