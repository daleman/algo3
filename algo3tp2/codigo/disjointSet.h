#include <vector>
#include <list>
using namespace std;

class ds_node{
	public:
		int valor;
		ds_node* parent;
		int rank;
		ds_node(int n){
			this->valor = n;
			this->parent = NULL;
			this->rank = 0;
		}
};


class disjointSet{
	public:
		int cantElems;
		vector<ds_node> elems;
		
		disjointSet(int n){
			this->cantElems = n;
			for(int i = 0; i < n; ++i){
				this->elems.push_back(ds_node(i));
				this->elems[i].parent = NULL;
			}
			for(int i = 0; i < n; ++i){
				this->elems[i].parent = &this->elems[i];
			}
			
		}
		
		void print(){
			for(int i = 0; i < this->cantElems; ++i){
				//cout << "| " << &this->elems[i] << " | " << this->elems[i].valor << " | " << this->elems[i].parent << " |" << endl;
			}
		}
		
		void simple_join(int n, int m){
			/* quiero que el padre de m sea ahora el padre de root(n) */
			// No implementa union by rank!
			root(n)->parent = root(m);
		}

		void union_by_rank(int n, int m){
			int rankn = root(n)->rank;
			int rankm = root(m)->rank;
			// UNION BY RANK:
			if (rankn < rankm) {
				root(n)->parent = root(m);
			} else if (rankm < rankn) {
				root(m)->parent = root(n);
			} else {
				root(m)->parent = root(n);
				root(n)->rank++;
			}
		}
		
		bool sameSet(int n, int m){
			if (root(n) == root(m)) return true;
			else return false;
		}

		ds_node* root(int n){
			/* Para un elemento n en particular, busca su nodo raiz */
			ds_node *r = &this->elems[n];
			list<ds_node> path = list<ds_node>();
			while (r->parent != r) {
				path.push_back(*r);
				r = r->parent;
			}
			// PATH COMPRESSION:
		/*	while (!path.empty()) {
				ds_node *p = &path.front();
				p->parent = r;
				path.pop_front();
			}*/
			return r;
		}
		
};
