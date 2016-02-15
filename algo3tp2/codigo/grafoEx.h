#ifndef GRAFOEX_H
#define GRAFOEX_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define PESO_MAX 100;

class grafoEx{
	public:
		int cantFabricas;
		int cantNodos;
		vector< vector<int>* > lista_global;
		vector< vector <int> > pesos;
		vector<arista> aristas;
		
	vector<int> vecinos(int n){
		/* dado un nodo n, devuelve un vector de int con los vecinos de n */
		vector<int> vecinos;
		for (int i = 0; i < (*this->lista_global[n]).size(); ++i){
			vecinos.push_back((*this->lista_global[n])[i]);
		}
		return vecinos;
	}
	
	grafoEx(){ grafo(0); }
	
	grafoEx(int F, int C){
		
		//cargo la cantidad de nodos
		this->cantFabricas = F;
		this->cantNodos = F+C;
		
		//inicializo todos los punteros en null
		for(int i = 0; i < F+C; i++){
			this->lista_global.push_back(NULL);
		}
		
		//inicializo los pesos en -1
		vector<int> v;
		for(int i = 0; i < F+C; ++i)
			v.push_back(-1);
		for(int i = 0; i < F+C; ++i)
			this->pesos.push_back(v);
		
	}
	
	void generar_aristas_aleatorias() {
		
		int n = this->cantNodos;
		int cf = this->cantFabricas;
		//cout << "Generando un grafo random:" << endl;
		//cout << "Cantidad de nodos: " << n << endl;
		
		srand(time(NULL));
		
		for(int i = cf+1; i <= n; ++i){
			int peso = rand() % PESO_MAX;
			asociar(i, 1+rand()%(i-1), peso);
		}
		
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j < i; ++j){
				if(rand()%2==0 && i!=j){
					//cout << "(" << i+1 << "," << j+1 << ")" << endl;
					int peso = rand() % PESO_MAX;
					asociar(i,j,peso+1);	// los pesos son positivos
				}
			}
		}
		//print();
	}
	
	void asociar(int nodo1, int nodo2, int peso){
		
		nodo1 = nodo1-1;
		nodo2 = nodo2-1;
		
		if(nodo1 != nodo2){
			
			
			/* Agrego la arista faltante y mantengo ordenada la lista para Kruskal */
			this->aristas.push_back(arista(nodo1,nodo2,peso));
			
			this->pesos[nodo1][nodo2] = peso;
			this->pesos[nodo2][nodo1] = peso;
			
			if (this->lista_global[nodo1] == NULL){
				this->lista_global[nodo1] = new vector<int>;
				(*this->lista_global[nodo1]).push_back(nodo2);
			}else{
				(*this->lista_global[nodo1]).push_back(nodo2);
			}
			
			//falta agregar el otro nodo
			if (this->lista_global[nodo2] == NULL){
				this->lista_global[nodo2] = new vector<int>;
				(*this->lista_global[nodo2]).push_back(nodo1);
			}else{
				(*this->lista_global[nodo2]).push_back(nodo1);
			}
			
		}
	}
	
	void print(){
		cout << "cantidad de nodos: " << this->cantNodos << "(";
		cout << this->cantFabricas << " fábricas y " << (this->cantNodos -
			this->cantFabricas) << " clientes)" << endl;
		for(int i = 0; i < this->cantNodos; ++i){
			cout << "[" << i+1 << "] ";
			if(this->lista_global[i] == NULL){
				cout << "-> null " << endl;
			}else{
				cout << "-> ";
				for(int j = 0; j < (*this->lista_global[i]).size(); ++j){
					cout << (*lista_global[i])[j]+1 << "(" << this->pesos[i][(*lista_global[i])[j]] << ") -> ";
				}
				cout << "null " << endl;
			}
		}
	}
	
	grafo kruskal(){
		disjointSet ds(this->cantNodos);
		vector<arista> res;
		/*Ordeno la lista de aristas para Kruskal */ // ----> O(n logn)
		sort(this->aristas.begin(), this->aristas.end()); 
		
		int i = 0;	//índice de arista que itero
		int j = 0;	//Cantidad de aristas que agregue
		int cantClientes = cantNodos - this->cantFabricas;
		
		while (j < cantClientes){
			int root1 = ds.root(this->aristas[i].nodo1);
			int root2 = ds.root(this->aristas[i].nodo2);
			// estan en distintas componente conexas y...
			if((root1 != root2) &&
			// no pasa que ambos tengan una fabrica
			!((root1 < this->cantFabricas) && (root2 < this->cantFabricas)) ){
				if (root1 < this->cantFabricas) {
					ds.simple_join(root2, root1);//Si el primero es una fábrica...
				} else {
					ds.simple_join(root1, root2);//Si el segundo es fábrica o si ninguno lo es.
				}
				j++;
				res.push_back(this->aristas[i]);
			}
			i++;
		}

		/* Armo el grafo para devolver */
		grafo g_res(this->cantNodos);
		for(int i = 0; i < res.size(); ++i)
			g_res.asociar(res[i].nodo1+1, res[i].nodo2+1, res[i].peso);
	
		return g_res;
	}

	void kruskal_no_res() {
		disjointSet ds(this->cantNodos);
		vector<arista> res;
		/*Ordeno la lista de aristas para Kruskal */ // ----> O(n logn)
		sort(this->aristas.begin(), this->aristas.end()); 
		
		int i = 0;	//índice de arista que itero
		int j = 0;	//Cantidad de aristas que agregue
		int cantClientes = cantNodos - this->cantFabricas;
		
		while (j < cantClientes){
			int root1 = ds.root(this->aristas[i].nodo1);
			int root2 = ds.root(this->aristas[i].nodo2);
			// estan en distintas componente conexas y...
			if((root1 != root2) &&
			// no pasa que ambos tengan una fabrica
			!((root1 < this->cantFabricas) && (root2 < this->cantFabricas)) ){
				if (root1 < this->cantFabricas) {
					ds.simple_join(root2, root1);//Si el primero es una fábrica...
				} else {
					ds.simple_join(root1, root2);//Si el segundo es fábrica o si ninguno lo es.
				}
				j++;
				res.push_back(this->aristas[i]);
			}
			i++;
		}
	}
	
};


#endif
