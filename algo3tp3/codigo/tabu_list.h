using namespace std;

class Tabu_list {
	public:
		int size;
		vector< vector<bool> > soluciones;
		int current;

		Tabu_list(int s) {
			this->size = s;
			this->soluciones = vector< vector<bool> >(this->size);
			for (int i=0; i<this->size; i++) {
				soluciones[i] = vector<bool>();
			}
			this->current = 0;
		}

		void add_tabu(vector<bool> solucion) {
			soluciones[current] = solucion;
			current = (current+1)%size;
		}

		bool es_tabu(vector<bool> solucion) {
			for (int i=0; i<size; i++) {
				int j = (size+current-i)%size;
				if (coinciden(solucion, soluciones[j])) {
					soluciones[j] = soluciones[current];
					soluciones[current] = solucion;
					current = (current+1)%size;
					return true;
				}
			}
			return false;
		}

		bool coinciden(vector<bool> s1, vector<bool> s2) {
			if (s2.size() != s1.size()) {return false;}
			for (int i=0; i<s1.size(); i++) {
				if (s1[i]!=s2[i]) {return false;}
			}
			return true;
		}
};
