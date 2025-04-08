#include "listaJuegos.h"


ListaJuegos::ListaJuegos() {
	cont = 0;
	capacidad = 10;
	lista = new Juego[capacidad];
}
ListaJuegos::~ListaJuegos() {

}
int ListaJuegos::insertar(const Juego& juego) {
	if (cont < capacidad) {
		Juego nuevo = new Juego();
	}
}
int ListaJuegos::dame_longitud() const {
	return cont;
}

bool ListaJuegos::es_vacia() const {
	if cont > 0 return  false;
	return true;
}
const Juego& ListaJuegos::dame_juego(int pos) const {
	return lista[pos];
}
void ListaJuegos::eliminar(int pos) {
	if (pos < cont - 1) {
		for (int i = pos; i < cont - 1; i++) {
			lista[i] = lista[i + 1];
		}
	}
}