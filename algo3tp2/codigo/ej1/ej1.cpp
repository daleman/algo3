#include "ej1.h"
using namespace std;

int main(){

	entrada_ej1 i;
	salida_ej1 s;
	while(true){
		i = inicializar_ej1();
		if (!i.valid) break;
		s = resolver_ej1(i);
		imprimir_ej1(s);
	}

	return 0;
}
