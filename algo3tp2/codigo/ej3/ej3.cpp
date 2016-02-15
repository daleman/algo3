#include "ej3.h"
using namespace std;

int main(){

	entrada_ej3 i;
	salida_ej3 s;
	while(true){
		i = inicializar_ej3();
		if (!i.valid) break;
		s = resolver_ej3(i);
		imprimir_ej3(s);
	}

	return 0;
}
