#include <queue>
#include <iostream>
#include <vector>
using namespace std;

// El primer entero es la capacidad restante
// El segundo entero es un identificador
typedef pair<int, int> Camion;

/**	ubicar_paquete : O(log(nPaquetes))
	Toma un paquete y lo ubica en un camión. El peso del paquete está
	dado por el parámetro 'int p'. Si el paquete entra en el camión
	con menor carga, es ubicado en él. Si no, se lo ubica en un
	nuevo camión vacío. La lista 'camiones' pasada como parámetro
	contiene todos los camiones usados.							**/
void ubicar_paquete(int maxPeso, priority_queue<Camion>& camiones, int p) {
        // Si entra el paquete en el primer camion...
        if (camiones.size() > 0 && camiones.top().first >= p) {
                Camion old = camiones.top();
                camiones.pop(); // O(2*log(nPaquetes)) + constant
                camiones.push(Camion(old.first - p, old.second)); // O(log(nPaquetes))
        }
        else {
                Camion nuevo(maxPeso - p, camiones.size());
                camiones.push(nuevo); // O(log(nPaquetes))
        }
}

void resolver(priority_queue<Camion>& camiones, int maxPeso, int paquetes[], int nPaquetes) {
	for (int i = 0; i < nPaquetes; i++) {
		ubicar_paquete(maxPeso, camiones, paquetes[i]);
	}
}

/**	mostrar_camiones : O(nPaquetes)
	Imprime en una línea la cantidad de camiones necesarios seguida del
	peso utilizado por cada camión. La lista 'camiones' pasada como
	parámetro contiene todos los camiones usados.						**/
void mostrar_camiones(int maxPeso, priority_queue<Camion>& camiones) {
        int k = camiones.size();
        // Construyo un array con el peso utilizado por cada camión
        int pesoUsado[k];
        while (camiones.size()) {
                Camion camion = camiones.top();
                camiones.pop();
                // El peso de cada camión es la capacidad total (maxPeso)
                // menos la capacidad restante (Camion.first)
                pesoUsado[camion.second] = maxPeso-camion.first;
        }

        // Imprimo el peso de cada camión
        cout << k;
        for (int i = 0; i < k; i++)
                cout << ' ' << pesoUsado[i];
        cout << endl;
}
