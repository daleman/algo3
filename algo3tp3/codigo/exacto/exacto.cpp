#include "exacto.h"

int main(){
	grafo g = grafo();
	g.inicializar();
	//g.draw();

	/*vector<int> vec2(g.cantNodos);
	vector<int> vec;
	vector<int> solucion;
	for (int i = 0; i < vec2.size(); ++i){
		vec2[i] = i+1;
	}

	int fronteraMax = -1;*/

	iniciarTimer();
	//exacto(vec,0,g.cantNodos,vec2,g,0,solucion,fronteraMax);
	Solucion s = exacto(g);
	double t = finalizarTimer();

	#ifdef TEST
		//muestro runtime
		cout << "tiempo transcurrido: " << t << endl;
		return 0;
	#endif

	//g.draw(s);	
	salida(s);

	return 0;
}

