#include "goloso.h"
#include "../exacto/exacto.h"

void testear_goloso( int maxN, int step, int cantTests ) {
	
	ofstream cota;
	cota.open("cota_goloso.data");
	
    for (int n=step; n<=maxN; n+=step) {
		cout << "n = " << n;
	
		for (int k=0; k<cantTests; k++) {
			cout << ".";
			grafo g = grafo(n);
			g.generar_aristas_aleatorias();

				float optimo = exacto(g).second;
			//-> Resolver_goloso:
				float result = goloso(g).second;
			//->
				result -= optimo;
				//Convertir a Porcentaje:
				result = 100*result/optimo;

				float gmax = g.gradoMax()-optimo;
				gmax = 100*gmax/optimo;

			float index = n + ((float)k/(float)cantTests);
			cota << index << " " << fixed << result << " " << fixed <<
			gmax << endl;
		}
		cout << endl;
	}
	
	cota.close();
	system("gnuplot cota_goloso.gnuplot");
}


int main(int argc, const char* argv[]) {
	int maxN = atoi(argv[1]);
	int step = atoi(argv[2]);
	int cantTests = atoi(argv[3]);
	
	testear_goloso(maxN, step, cantTests);
    
	return 0;
}
