#include "listaJuegos.h"


ListaJuegos::ListaJuegos() {
	cont = 0;
	capacidad = 10;
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
int ListaJuegos::insertar(const Juego& juego) {
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
	int dif = juego.dame_num_filas() * juego.dame_num_columnas() / juego.dame_num_minas();
	pos = 0; 
	bool enc = false;
	while (pos < cont && !enc) {
		int actual = lista[pos]->dame_num_filas() * lista[pos]->dame_num_columnas() / lista[pos]->dame_num_minas();
		if (actual < dif) {

		}
		else if (actual > dif) {
			pos++;
		}
		else {
			enc = true;
		}
	}	
}