#include "listaPosiciones.h"
#include "checkML.h"

ListaPosiciones::ListaPosiciones(){
	cont = 0;
	size = 10;
	lista = new Posicion[size];
}

ListaPosiciones::ListaPosiciones(const ListaPosiciones& lp) {
	cont = lp.cont;
	size = lp.size;
	lista = new Posicion[size];
	for (int i = 0; i < cont; ++i) {
		lista[i] = lp.lista[i];
	}
}

ListaPosiciones::~ListaPosiciones() {
	delete[] lista;
}
void ListaPosiciones::insertar_final(int x, int y) {
	if (cont >= size) {
		size *= 2;
		Posicion* nuevo = new Posicion[size];
		for (int i = 0; i < cont; ++i) {
			nuevo[i] = lista[i];
		}
		delete[] lista;
		lista = nuevo;
	}
	lista[cont].posx = x;
	lista[cont].posy = y;
	cont++;
}
int ListaPosiciones::longitud() const {
	return cont;
}
int ListaPosiciones::dame_posX(int i) const {
	return lista[i].posx;
}

int ListaPosiciones::dame_posY(int i) const {
	return lista[i].posy;
}


