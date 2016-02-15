#include "ej3.h"
using namespace std;

int main(){

	while(cin >> height >> width) {

		if (width>MAXSIZE || height>MAXSIZE) {
			cout << "Error: El piso es demasiado grande" << endl;
		} else {

			// Inicializar: creo los pisos a partir de la entrada
			inicializar_piso();

				//cout << "-Entrada-" << endl;
				//imprimir_piso(pisoMejor);

			// Procesar: selecciono los sensores
			obtener_mejor();

			// Imprimir resultado
			if (costoMejor > maxCosto) {
				//cout << "No se ha encontrado ninguna solución posible" << endl;
				cout << "-1";
			} else {
				//cout << "-Salida: $" << costoMejor << endl;
				//imprimir_piso(pisoMejor);
				obtener_sensores();
				cout << cantSensores << " " << costoMejor << endl;
				for (int i=0; i<cantSensores; i++) {
					int x = sensores[i].first;
					int y = sensores[i].second;
					int s = pisoMejor[x][y];
					int t = 0;
					if (s==SENSORH) t=2;
					if (s==SENSORV) t=3;
					if (s==SENSOR4) t=1;
					x++; y++;
					cout << t << " " << y << " " << x << endl;
				}
			}
		}

	}

	return 0;
}
