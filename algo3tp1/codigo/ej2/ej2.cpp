#include "ej2.h"
using namespace std;

int main(){

	int nCursos, i;
	while(cin >> nCursos){
		
		// Vector de cursos disponibles (entrada)
		Cronograma cursos;

		// Inicializar: Agrego cada curso al cronograma
		for(i = 0; i < nCursos; ++i){
			Curso* ptr = new Curso;
			cin >> ptr->first.first;
			cin >> ptr->first.second;
			ptr->second = i+1;
			cursos.push_back(*ptr);
		}

		// Procesar: Selecciono los cursos
		Cronograma res = resolver(cursos);

		// Imprimir resultado
		mostrar_cursos(res);
	}

	return 0;

}
