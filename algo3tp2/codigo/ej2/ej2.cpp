#include "ej2.h"
using namespace std;

int main(){

	//grafo g(8);

	//g.generar_aristas_aleatorias(0, 10);

	entrada_ej2 i;
	salida_ej2 s;
	while(true){
		i = inicializar_ej2();
		if (!i.valid) break;
		s = resolver_ej2(i);
		imprimir_ej2(s);
	}

	return 0;
}
