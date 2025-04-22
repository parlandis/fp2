#include "listaJuegos.h"


ListaJuegos::ListaJuegos() {
	cont = 0;
	capacidad = 3;
	lista = new Juego*[capacidad];
}
ListaJuegos::~ListaJuegos() {
	for (int i = 0; i < cont; i++) {
		delete lista[i];
		lista[i] = nullptr;
	}
	delete[] lista;
	lista = nullptr;
}
int ListaJuegos::insertar(const Juego& juego) {   // inserta mal los juegos 
	if (cont == capacidad) {
		capacidad *= 2;
		Juego** nuevo = new Juego * [capacidad];
		for (int i = 0; i < cont; i++) {
			nuevo[i] = lista[i];
		}
		delete[] lista;
		lista = nuevo;
	}

	int pos;
	buscar(juego, pos);
	
	
	for (int i = cont; i > pos; i--) {
		lista[i] = lista[i - 1];
	}
	lista[pos] = new Juego(juego);
	cont++;
	return pos;
}
int ListaJuegos::dame_longitud() const {
	return cont;
}

bool ListaJuegos::es_vacia() const {
	if (cont > 0) return  false;
	return true;
}
const Juego& ListaJuegos::dame_juego(int pos) const {
	return *lista[pos];
}
void ListaJuegos::eliminar(int pos) {
	if (pos < cont - 1) {
		for (int i = pos; i < cont - 1; i++) {
			lista[i] = lista[i + 1];
		}
		cont--;
		lista[cont] = nullptr;
	}
}


void  ListaJuegos::buscar(const Juego& juego, int& pos) {  // Por Busqueda binari????
	bool enc = false;
	double dif = (juego.dame_num_filas() * juego.dame_num_columnas()) / (double)juego.dame_num_minas();
	int ini = 0, fin = dame_longitud() -1;
	
	int m = (ini + fin) / 2;
	while (ini < fin) {
		double actual = lista[m]->dame_num_filas() * lista[m]->dame_num_columnas() / lista[m]->dame_num_minas();

		if (dif < actual) {
			ini = m + 1;
		}
		else if(dif > actual) {
			fin = m - 1;
		}
		else {
			pos = m;
			return;
		}
	}
	pos = ini;
}