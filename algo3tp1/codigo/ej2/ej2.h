#include <algorithm>
#include <utility>
#include <iostream>
#include <vector>
using namespace std;

typedef pair <int,int> Fechas;
typedef pair <Fechas,int> Curso;
typedef vector <Curso> Cronograma;

inline bool termina_antes(Curso curso1, Curso curso2) {
	return curso1.first.second < curso2.first.second;
}

Cronograma resolver(Cronograma &entrada) {
	sort(entrada.begin(), entrada.end(), termina_antes);
	int ultimaFecha = -1;
	Cronograma cursosAceptados;
	for(int i = 0; i < entrada.size(); ++i){
		if(entrada[i].first.first > ultimaFecha){
			cursosAceptados.push_back(entrada[i]);
			ultimaFecha = entrada[i].first.second;
		}
	}
	
	return cursosAceptados;
}

void mostrar_cursos(Cronograma &cursos) {
	for(int i = 0; i < cursos.size(); ++i)
		cout << cursos[i].second << " ";
	cout << endl;
}
