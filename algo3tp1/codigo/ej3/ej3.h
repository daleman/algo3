#include <iostream>
using namespace std;

#define MAXSIZE		50
#define PRECIO2		4000
#define PRECIO4		6000

//Valor de Casilla:
#define VACIO	 	45
#define SENSORH		61
#define SENSORV		73
#define SENSOR4		43
#define IMPORTANTE	111
#define PARED		35

typedef pair<int,int> Posicion;
typedef int Costo;
typedef char Casilla;
typedef Casilla Piso[MAXSIZE][MAXSIZE];

int width, height;
Piso pisoActual, pisoMejor;
Costo costoActual, costoMejor;
Posicion vacias[MAXSIZE*MAXSIZE], importantes[MAXSIZE*MAXSIZE], sensores[MAXSIZE*MAXSIZE];
int cantVacias, cantImportantes, cantSensores;
Costo maxCosto;

void inicializar_piso();
void obtener_mejor();
void obtener_mejor_sin_podas();
bool cambiar_valor(Posicion p, Casilla* c);
bool cambiar_valor_sin_podas(Posicion p, Casilla* c);
void evaluar_piso();
void evaluar_piso_sin_podas();
bool ultima_casilla(Posicion c);
Casilla* obtener_casilla(Posicion p);
bool vigilada(Posicion p);
bool vigila(Posicion p);
bool doble_vigilada(Posicion p);
void imprimir_piso(Piso p);
void imprimir_piso_largo(Piso p);
void reiniciar_piso();

void inicializar_piso() {
	cantVacias = 0;
	cantImportantes = 0;

	int i,j,c;
	for (j=0; j<height; j++) {
		for (i=0; i<width; i++) {
			cin >> c;
			if (c==1) {
				pisoMejor[i][j] = VACIO;
				vacias[cantVacias] = Posicion(i,j);
				cantVacias++;
			} else if (c==2) {
				pisoMejor[i][j] = IMPORTANTE;
				importantes[cantImportantes] = Posicion(i,j);
				cantImportantes++;
			} else pisoMejor[i][j] = PARED;
			pisoActual[i][j] = pisoMejor[i][j];
		}
	}

	maxCosto = cantVacias * PRECIO4;
	costoMejor = maxCosto+1;
	costoActual = 0;
}

void obtener_mejor() {
	Posicion p;
	Casilla* c;
	int iCasilla;
	bool loop = true;
	bool overflow;

	int i,j,k;
	bool h,v;
	bool imposible = false;
	if (cantVacias == 0) {
		if (cantImportantes==0){
			costoMejor = 0;
		}
	} else {
		/** Poda 1: si algún punto importante no puede ser vigilado
		por 2 sensores simultáneamente, no hay solución.			**/
		if ((width==1 || height==1) && (cantImportantes > 0)) imposible = true;
		else {
			for (k=0; k<cantImportantes; k++) {
				h = false;		v = false;
				p = importantes[k];
				i = p.first+1;	j = p.second;
				for (; i<width; i++) {
					if (pisoMejor[i][j]==VACIO) {	h = true;	break;	}
					if (pisoMejor[i][j]==PARED)		break;
				}
				if (!h) {
					for (i=p.first-1; i>=0; i--) {
						if (pisoMejor[i][j]==VACIO) {	h = true;	break;	}
						if (pisoMejor[i][j]==PARED)		break;
					}
				}
				if (h) {
					i = p.first;	j++;
					for (; j<height; j++) {
						if (pisoMejor[i][j]==VACIO) {	v = true;	break;	}
						if (pisoMejor[i][j]==PARED)		break;
					}
					if (!v) {
						for (j=p.second-1; j>=0; j--) {
							if (pisoMejor[i][j]==VACIO) {	v = true;	break;	}
							if (pisoMejor[i][j]==PARED)		break;
						}
					}
				} else {			imposible = true;	break;	}
				if (!(h && v)) {	imposible = true;	break;	}
			}
		}
		if (!imposible) {
		/** FinPoda **/

			while(loop) {

				evaluar_piso();

				iCasilla = 0;
				p = vacias[iCasilla];
				c = obtener_casilla(p);
				overflow = cambiar_valor(p,c);

				while(overflow) {
					if (ultima_casilla(p)) {
						loop = false;
						break;
					} else {
						iCasilla++;
						p = vacias[iCasilla];
						c = obtener_casilla(p);
						overflow = cambiar_valor(p,c);
					}
				}
			}
		}
	}
}

void obtener_mejor_sin_podas() {
	Posicion p;
	Casilla* c;
	int iCasilla;
	bool loop = true;
	bool overflow;

	if (cantVacias == 0) {
		if (cantImportantes==0){
			costoMejor = 0;
		}
	} else {
		while(loop) {

			evaluar_piso_sin_podas();

			iCasilla = 0;
			p = vacias[iCasilla];
			c = obtener_casilla(p);
			overflow = cambiar_valor_sin_podas(p,c);

			while(overflow) {
				if (ultima_casilla(p)) {
					loop = false;
					break;
				} else {
					iCasilla++;
					p = vacias[iCasilla];
					c = obtener_casilla(p);
					overflow = cambiar_valor_sin_podas(p,c);
				}
			}
		}
	}
}

bool cambiar_valor(Posicion p, Casilla* c) {
	// Asumo que la casilla no es una pared ni un lugar importante
	/** Poda 2: si hay un sensor apuntando a la casilla, no
		puede haber un sensor allí **/
	if (vigilada(p)) {
		*c = VACIO;
		return true;
	}
	/** FinPoda **/
	if (*c == VACIO) {
		/** Poda 3: si ya superé el mejor costo, no vale la pena seguir **/
		if (costoActual > costoMejor) {
			return true;
		}
		/** FinPoda **/
		*c = SENSORH;
		costoActual += PRECIO2;
		/*a)*/if (!vigila(p)) return false;
	}
	if (*c == SENSORH) {
		*c = SENSORV;
		/*a)*/if (!vigila(p)) return false;
	}
	if (*c == SENSORV) {
		*c = SENSOR4;
		costoActual -= PRECIO2;
		costoActual += PRECIO4;
		/*a)*/if (!vigila(p)) return false;
	}
	if (*c == SENSOR4) {
		*c = VACIO;
		costoActual -= PRECIO4;
		return true;
	}
	/** a) Poda 4: si al ubicar un sensor de ese tipo en esa posición
	vigila a otro sensor, paso al siguiente valor (si no es así, retorno)**/
}

bool cambiar_valor_sin_podas(Posicion p, Casilla* c) {
	if (*c == VACIO) {
		*c = SENSORH;
		costoActual += PRECIO2;
	} else if (*c == SENSORH) {
		*c = SENSORV;
	} else if (*c == SENSORV) {
		*c = SENSOR4;
		costoActual -= PRECIO2;
		costoActual += PRECIO4;
	} else if (*c == SENSOR4) {
		*c = VACIO;
		costoActual -= PRECIO4;
		return true;
	}
	return false;
}

void evaluar_piso() {
	// Calcula el costo del piso actual y si está completo lo compara con
	// el del mejor. Si es menor, el actual pasa a ser el nuevo mejor.
	// Asumo q el piso es válido (no hay sensores q se apuntan entre sí)
	// Pero podría estar incompleto (zonas no vigiladas todavía)
	Posicion p;
	Casilla* c;
	int i,j;
	for (i=0; i<cantVacias; i++) {
		p = vacias[i];
		c = obtener_casilla(p);
		if (*c == VACIO && !vigilada(p)) return;
	}
	for (i=0; i<cantImportantes; i++) {
		p = importantes[i];
		if (!doble_vigilada(p)) return;
	}
	if (costoActual < costoMejor) {
		for (i=0; i<width; i++) {
			for (j=0; j<height; j++) {
				pisoMejor[i][j] = pisoActual[i][j];
			}
		}
		costoMejor = costoActual;
	}
}

void evaluar_piso_sin_podas() {
	Posicion p;
	Casilla* c;
	int i,j;
	for (i=0; i<width; i++) {
		for (j=0; j<height; j++) {
			p = Posicion(i,j);
			if (pisoActual[i][j] == VACIO && !vigilada(p)) return;
			if (pisoActual[i][j] == IMPORTANTE && !doble_vigilada(p)) return;
			if (pisoActual[i][j] == SENSORH && (vigilada(p) || vigila(p) )) return;
			if (pisoActual[i][j] == SENSORV && (vigilada(p) || vigila(p) )) return;
			if (pisoActual[i][j] == SENSOR4 && (vigilada(p) || vigila(p) )) return;
		}
	}
	if (costoActual < costoMejor) {
		for (i=0; i<width; i++) {
			for (j=0; j<height; j++) {
				pisoMejor[i][j] = pisoActual[i][j];
			}
		}
		costoMejor = costoActual;
	}
}

bool vigilada(Posicion p) {
	// Retorna si algún sensor de otra casilla vigila la posicion p
	int i=p.first+1;
	int j=p.second;
	for (; i<width; i++) {
		if (pisoActual[i][j] == PARED) break;
		if (pisoActual[i][j] == SENSORH || pisoActual[i][j] == SENSOR4) {
			return true;
		}
	}
	i=p.first-1;
	for (; i>=0; i--) {
		if (pisoActual[i][j] == PARED) break;
		if (pisoActual[i][j] == SENSORH || pisoActual[i][j] == SENSOR4) {
			return true;
		}
	}
	i=p.first;
	j++;
	for (; j<height; j++) {
		if (pisoActual[i][j] == PARED) break;
		if (pisoActual[i][j] == SENSORV || pisoActual[i][j] == SENSOR4) {
			return true;
		}
	}
	j=p.second-1;
	for (; j>=0; j--) {
		if (pisoActual[i][j] == PARED) break;
		if (pisoActual[i][j] == SENSORV || pisoActual[i][j] == SENSOR4) {
			return true;
		}
	}
	return false;

}
bool vigila(Posicion p) {
	// Retorna si el sensor en la posicion p vigila a otro sensor
	int i,j;
	Casilla c = pisoActual[p.first][p.second];
	if (c == SENSORH || c == SENSOR4) {
		i=p.first+1; j=p.second;
		for (; i<width; i++) {
			if (pisoActual[i][j] == PARED) break;
			if (pisoActual[i][j] != VACIO && pisoActual[i][j] != IMPORTANTE) {
				return true;
			}
		}
		i=p.first-1;
		for (; i>=0; i--) {
			if (pisoActual[i][j] == PARED) break;
			if (pisoActual[i][j] != VACIO && pisoActual[i][j] != IMPORTANTE) {
				return true;
			}
		}
	}
	if (c == SENSORV || c == SENSOR4) {
		i=p.first; j=p.second+1;
		for (; j<height; j++) {
			if (pisoActual[i][j] == PARED) break;
			if (pisoActual[i][j] != VACIO && pisoActual[i][j] != IMPORTANTE) {
				return true;
			}
		}
		j=p.second-1;
		for (; j>=0; j--) {
			if (pisoActual[i][j] == PARED) break;
			if (pisoActual[i][j] != VACIO && pisoActual[i][j] != IMPORTANTE) {
				return true;
			}
		}
	}
	return false;
}

bool doble_vigilada(Posicion p) {
	// Retorna si dos o más sensores en otras casillas vigilan la posicion p
	int i=p.first+1;
	int j=p.second;
	bool sensorH = false;
	// Recorro los casilleros a la derecha de p hasta llegar a una pared
	for (; i<width; i++) {
		if (pisoActual[i][j] == PARED) break;
		if (pisoActual[i][j] == SENSORH || pisoActual[i][j] == SENSOR4) {
			// encontré un sensor horizontal (o de 4) que vigila a p
			sensorH = true;
			break;
		}
	}
	// Si no encontré ningún sensor horizontal, recorro los de la izquierda
	if (!sensorH) {
		i=p.first-1;
		for (; i>=0; i--) {
			if (pisoActual[i][j] == PARED) break;
			if (pisoActual[i][j] == SENSORH || pisoActual[i][j] == SENSOR4) {
				// encontré un sensor horizontal (o de 4) que vigila a p
				sensorH = true;
				break;
			}
		}
	}
	if (sensorH) {
		// Recorro los casilleros debajo de p
		i=p.first;
		j++;
		for (; j<height; j++) {
			if (pisoActual[i][j] == PARED) break;
			if (pisoActual[i][j] == SENSORV || pisoActual[i][j] == SENSOR4) {
				// encontré un sensor vertical (o de 4) que vigila a p
				return true;
			}
		}
		j=p.second-1;
		for (; j>=0; j--) {
			if (pisoActual[i][j] == PARED) break;
			if (pisoActual[i][j] == SENSORV || pisoActual[i][j] == SENSOR4) {
				// encontré un sensor vertical (o de 4) que vigila a p
				return true;
			}
		}
	}
	return false;
}

bool ultima_casilla(Posicion c) {
	Posicion ultima = vacias[cantVacias-1];
	return (c.first==ultima.first) && (c.second==ultima.second);
}

Casilla* obtener_casilla(Posicion p) {
	int i = p.first;
	int j = p.second;
	return &pisoActual[i][j];
}

void obtener_sensores() {
	cantSensores = 0;
	for (int j=0; j<height; j++) {
		for (int i=0; i<width; i++) {
			if (	pisoMejor[i][j]==SENSORH ||
					pisoMejor[i][j]==SENSORV ||
					pisoMejor[i][j]==SENSOR4	) {
				sensores[cantSensores] = Posicion(i,j);
				cantSensores++;
			}
		}
	}	
}

void imprimir_piso(Piso p) {
	for (int j=0; j<height; j++) {
		cout << "|";
		for (int i=0; i<width; i++) {
			cout << p[i][j];
		}
		cout << "|" << endl;
	}	
}

void imprimir_piso_largo(Piso p) {
	for (int j=0; j<height; j++) {
		cout << "|";
		for (int i=0; i<width; i++) {
			cout << p[i][j];
		}
	}
	cout << endl;
}

void reiniciar_piso() {
	costoMejor = maxCosto+1;
	costoActual = 0;
	for (int j=0; j<height; j++) {
		for (int i=0; i<width; i++) {
			if (	(pisoActual[i][j] == SENSORH) ||
					(pisoActual[i][j] == SENSORV) ||
					(pisoActual[i][j] == SENSOR4) ||
					(pisoActual[i][j] == VACIO)) {
				pisoActual[i][j] = VACIO;
				pisoMejor[i][j] = VACIO;
			}
		}
	}
}
