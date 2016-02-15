#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "ds.h"
#include <cmath>                //time
#include "time.h"
#include <stdio.h>



using namespace std;

#define PESO_MAX 100;

struct arista{
    int nodo1;
    int nodo2;
    int peso;

    bool operator<(const arista& a) const {
        return peso < a.peso;
    }

    arista(int n, int m, int p){
        this->nodo1 = n;
        this->nodo2 = m;
        this->peso = p;
    }

};

class grafo{
    public:
        int cantNodos;
        vector< vector<int> > lista_global;
        vector< vector <int> > pesos;
        vector<arista> aristas;




        vector<int> vecinos(int n){
            /* dado un nodo n, devuelve un vector de int con los vecinos de n */
            vector<int> vecinos;
            //cout << "vecino de " << n + 1 << ": ";
            for (int i = 0; i < (this->lista_global[n]).size(); ++i){
                //cout  << (*this->lista_global[n])[i] << " ";
                vecinos.push_back((this->lista_global[n])[i]);
            }
            //cout << endl;
            return vecinos;
        }

        grafo(){ grafo(0); }



        grafo(int n){


            //cargo la cantidad de nodos
            this->cantNodos = n;

            vector <int> vec;

            //inicializo todos los punteros en null
            for(int i = 0; i < n; i++){
                (this->lista_global).push_back(vector <int>()) ;//.push_back(vec);
            }

            //inicializo los pesos en -1
            vector<int> v;
            for(int i = 0; i < n; ++i)
                v.push_back(-1);
            for(int i = 0; i < n; ++i)
                this->pesos.push_back(v);
        }

        void generar_aristas_aleatorias() {

            int n = this->cantNodos;
            //cout << "Generando un grafo random:" << endl;
            //cout << "Cantidad de nodos: " << n << endl;

            srand(time(NULL));

            for(int i = 2; i <= n; ++i){
                int nodo = rand()%(i-1)+1;
                //cout << "Voy a asociar el nodo " << i << " con el nodo " << nodo << endl;
                int peso = rand() % PESO_MAX +1;
                asociar(i, nodo, peso);
            }

            //print();

        }

        void asociar(int nodo1, int nodo2, int peso){

            nodo1 = nodo1-1;
            nodo2 = nodo2-1;

            if(nodo1 != nodo2){
                //cout << "asociar(" << nodo1+1 << "," << nodo2+1 << ")" << endl;

                /* Agrego la arista faltante  */
                this->aristas.push_back(arista(nodo1,nodo2,peso));
                
                this->pesos[nodo1][nodo2] = peso;
                this->pesos[nodo2][nodo1] = peso;

                 //agrego cada nodo en la lista del otro nodo incidente
               
                    (this->lista_global[nodo1]).push_back(nodo2);
                    (this->lista_global[nodo2]).push_back(nodo1);
            }
        }

        void print(){
            cout << "cantidad de nodos: " << this->cantNodos << endl;
            for(int i = 0; i < this->cantNodos; ++i){
                cout << "[" << i+1 << "] ";
                if(this->lista_global[i].size() == 0){
                    cout << "-> null " << endl;
                }else{
                    cout << "-> ";
                    for(int j = 0; j < (this->lista_global[i]).size(); ++j){
                        cout << (lista_global[i])[j]+1 << "(" << this->pesos[i][(lista_global[i])[j]] << ") -> ";
                    }
                    cout << "null " << endl;
                }
            }
        }

        grafo kruskal(){
            disjointSet ds(this->cantNodos);
            vector<arista> res;

            sort(this->aristas.begin(), this->aristas.end());

            int i = 0;      //índice de arista que itero
            int j = 0;      //Cantidad de aristas que agregé
            while ( j < this->cantNodos-1 ) {
                if(!ds.sameSet(this->aristas[i].nodo1, this->aristas[i].nodo2)){
                    ds.simple_join(this->aristas[i].nodo1, this->aristas[i].nodo2);
                    res.push_back(this->aristas[i]);
                    j++;
                }
                i++;
            }

            /* Armo el grafo para devolver */
            grafo g_res(this->cantNodos);
            for(int i = 0; i < res.size(); ++i)
                g_res.asociar(res[i].nodo1+1, res[i].nodo2+1, res[i].peso);

            return g_res;
        }

        int bfs(int n, vector<bool> &visitadas) {
            /* Creo una cola y encolo a n */
            queue<int> q;
            q.push(n);
            int nodoActual;

            while(!q.empty()){
                /* Me guardo en una variable al nodo actual */
                nodoActual = q.front();
                q.pop();

                /* Encolo los vecinos de nodoActual */
                int tam = (this->lista_global[nodoActual]).size();
                for(int i = 0; i < tam; ++i){
                    int u = ((this->lista_global[nodoActual])[i]);
                    if(!visitadas[u]){
                        visitadas[u] = true;
                        q.push(u);
                    }
                }
            }
            return nodoActual;
        }

        int bfs(int n){
            /* Creo el vector de nodos visitados y marco el nodo como visitado */
            vector <bool> visitadas(this->cantNodos);
            for(int i = 0; i < this->cantNodos; i++)
                visitadas[i] = false;
            visitadas[n] = true;

            return bfs(n, visitadas);
        }

         bool es_conexo(){
        /* Creo el vector de nodos visitados y marco el nodo como visitado */
            vector<bool> visitadas(this->cantNodos);
              for(int i = 0; i < this->cantNodos; i++)
                visitadas[i] = false;
              visitadas[1] = true;

              bfs(1, visitadas);

			for(int i = 0; i < this->cantNodos; i++){
				if (!visitadas[i]){
					return false;
				}
			}
              return true;
        }

        int dfs(int n, int m){
            /* Valor del nodo master */ 
            int U = 0;

            /* Me creo un vector para irme guardando el camino que voy recorriendo */
            vector<int> p_max;
            p_max.push_back(n);

            /* Seteo lista de nodos visitados y flag de encontrado */
            bool encontrada = false;
            vector <bool> visitadas(this->cantNodos);
            for(int i = 0; i < this->cantNodos; i++)
                visitadas[i] = false;
            visitadas[n] = true;

            for(int j = 0; j < (this->lista_global[n]).size(); ++j){
                if(visitadas[(this->lista_global[n])[j]] == false){
                    return dfs_recur((this->lista_global[n])[j], m, visitadas, encontrada, p_max, U);
                }
                //if (encontrada) break;
            }
        }

        int dfs_recur(int n, int m, vector<bool> &visitadas, bool &encontrada, vector<int> p, int U){
            p.push_back(n);
            visitadas[n] = true;

            if (n == m){
                /* Encontre el nodo que buscaba */
                encontrada = true;
                /* Devuelvo el valor de la mitad del vector que tengo hasta ahora */
                U = p[p.size()/2]+1;
                return U;
            }

            for(int j = 0; j < (this->lista_global[n]).size(); ++j){
                if(visitadas[(this->lista_global[n])[j]] == false)
                    U = dfs_recur((this->lista_global[n])[j], m, visitadas, encontrada, p, U);
            }
            return U;
        }

};


#endif 
