#ifndef GOLOSO_H
#define GOLOSO_H
#include "../grafo.h"
#include "../timer.h"

using namespace std;

Solucion goloso(grafo g){
	Solucion s = make_pair(vector<bool>(g.cantNodos,false), 0);

	while (true){
		int candidato = -1;
		int maximo_aporte = 0;

		// veo cual es el nodo que mas aporta y si aporta algo
			// positivo, lo agrego
		for (int i = 0 ; i < g.cantNodos; ++i){				
			if (!s.first[i]){
				if ( g.se_conecta_con_clique(i, s.first) ){
					int aporta = g.cuanto_aporta(i,s);
					if (aporta > maximo_aporte){
						candidato = i;
						maximo_aporte = aporta;
					}
				}
			}
		}

		if (candidato == -1){
			break;
		} else {
			g.alternar(s, candidato);
		}
	}

	return s;
}

#endif
