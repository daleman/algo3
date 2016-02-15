#include "goloso.h"

int main(int argc, const char* argv[]) {
	grafo g = grafo();
	g.inicializar();
	//g.draw();

	Solucion result = goloso(g);
	//g.draw(result);
	salida(result);

	return 0;
}
