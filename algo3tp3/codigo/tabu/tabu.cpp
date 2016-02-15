#include "tabu.h"

using namespace std;

int main(int argc, const char* argv[]) {
	grafo g = grafo();
	g.inicializar();
	//g.draw();

	Solucion si = goloso(g);
	Solucion sf = tabu(g,si,/*I*/50,/*T*/40,/*V*/4);
	//g.draw(sf);

	cout << "Solucion inicial: ";
	salida(si);
	cout << "Solucion final: ";
	salida(sf);

	return 0;
}

