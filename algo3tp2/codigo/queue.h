#include <iostream>
#include <vector>
using namespace std;

template <class T> struct elem{
	T valor;
	elem* next;
};

template <class T> class queue{
	
	private:
		elem<T>* primero;
		elem<T>* ultimo;
		int numElem;
	
	public:
		queue(){
			this->primero = NULL;
			this->ultimo = NULL;
			this->numElem = 0;
		}
		
		void enqueue(T n){
			this->numElem++;
			elem<T>* new_ptr = new(elem<T>);
			new_ptr->valor = n;
			new_ptr->next = NULL;
			if(this->primero == NULL){
				this->primero = new_ptr;
				this->ultimo = new_ptr;
			}else
				enqueue_recur(new_ptr, this->primero);
		}
		
		void enqueue_recur(elem<T>* new_ptr, elem<T>* nodo){
			if(nodo->next == NULL){
				nodo->next = new_ptr;
				this->ultimo = new_ptr;
			}else
				enqueue_recur(new_ptr, nodo->next);
		}
		
		T first(){
			return this->primero->valor;
		}
		
		T last(){
			return this->ultimo->valor;
		}
		
		int size(){
			return this->numElem;
		}
		
		bool vacia(){
			if (this->numElem == 0)
				return true;
			else
				return false;
		}
		
		T dequeue(){
			if(this->primero == NULL)
				return -1;
			else{
				this->numElem--;
				T temp_val = this->primero->valor;
				elem<T>* temp_nodo = this->primero;
				this->primero = this->primero->next;
				delete(temp_nodo);
				return temp_val;
			}
		}
		
		void print(){
			if(this->primero == NULL)
				cout << "empty" << endl;
			else{
				cout << "[";
				print_recur(this->primero);
				cout << "]" << endl;
			}
		}
		
		void print_recur(elem<T>* nodo){
			if (nodo->next != NULL){
				cout << nodo->valor << ",";
				print_recur(nodo->next);
			}else{
				cout << nodo->valor;
				return;
			}
		}
	
};
