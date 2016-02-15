#include "../grafo.h"

struct entrada_ej2 {
        entrada_ej2() {
                g = grafo();
                valid = false;
        }
        grafo g;
        bool valid;
};

struct salida_ej2 {
        salida_ej2() {
                C = 0;
                U = 0;
                k = 0;
                e = vector<int>(0);
        }
        salida_ej2(int c,int u,int K,vector<int> &E) {
                C = c;
                U = u;
                k = K;
                e = E;
        }
        int C;
        int U;
        int k;
        vector<int> e;
};

salida_ej2 resolver_ej2(entrada_ej2 &i){
        vector<int> e;

        /* Grafo Trivial */
        if ( i.g.cantNodos == 1 ) {
                salida_ej2 trivial(0, 1, 0, e);
                return trivial;
        }
        
        /* Ej2.a */
        grafo res = i.g;//.kruskal();                      //O(Kruskal)
        
        /* Ej2.b */
        int nodo_a = res.bfs(rand()%(i.g.cantNodos));                                //O(n)
        int nodo_b = res.bfs(nodo_a);                   //O(n)
        int U = res.dfs(nodo_a, nodo_b);                //O(n)
        
        /* Calculo todos los resultados para mostrar */
        int C = 0;
        int k = res.aristas.size();
        for(int i = 0; i < res.aristas.size(); ++i){
                C += res.aristas[i].peso;
                e.push_back(res.aristas[i].nodo1+1);
                e.push_back(res.aristas[i].nodo2+1);
        }

        salida_ej2 salida(C, U, k, e);
        return salida;

}

void imprimir_ej2(salida_ej2 &salida) {
        int C = salida.C;
        int U = salida.U;
        int k = salida.k;
        vector<int> e = salida.e;
        cout << C << " " << U << " " << k << " ";
        for(int i = 0; i < e.size(); ++i)
                cout << e[i] << " ";
        cout << endl;
}

entrada_ej2 generar_instancia_ej2b(int n) {
        entrada_ej2 entrada;
        entrada.g = grafo(n);
        entrada.g.generar_aristas_aleatorias();      
        return entrada;
}

entrada_ej2 inicializar_ej2() {
        entrada_ej2 entrada;
        int n, m, a, b, c;
        cin >> n;
        if(n != 0) {
                entrada.valid = true;
                grafo g(n);
                cin >> m;
                for(int i = 0; i < m; ++i){
                        cin >> a;
                        cin >> b;
                        cin >> c;
                        g.asociar(a,b,c);
                }
                entrada.g = g;
        }
        return entrada;
}
