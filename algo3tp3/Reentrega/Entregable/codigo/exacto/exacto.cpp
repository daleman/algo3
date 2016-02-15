#include "exacto.h"

int main(){
	grafo g = grafo();
	g.inicializar();
	//g.draw();

	iniciarTimer();
	Solucion s = exacto_2p(g);
	double t = finalizarTimer();

	#ifdef TEST
		//muestro runtime
		cout << "tiempo transcurrido: " << t << endl;
		return 0;
	#endif

	//g.draw(s.first);	
	salida(s);

	return 0;
}

