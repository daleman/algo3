#include "local.h"

int main(int argc, const char* argv[]) {
	
	grafo g = grafo();
	g.inicializar();
	//g.draw();

	Solucion si = goloso(g);
	Solucion sf = local(g,si,/*V*/1);
	//g.draw(sf);

	cout << "Solucion inicial: ";
	salida(si);
	cout << "Solucion final: ";
	salida(sf);

	return 0;
}

