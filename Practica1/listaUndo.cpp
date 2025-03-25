#include "listaUndo.h"

ListaUndo::ListaUndo() {
	cont = 0;
}

void ListaUndo::destruye() {
    lista->destruye();
	cont = 0;
}

void ListaUndo::insertar_final(const ListaPosiciones& lista_pos) {
    if (cont < MAX_UNDO) {
        lista[cont] = lista_pos; // Copiar toda la lista de posiciones
        cont++;
    }
    else {
        // Desplazar todas las listas hacia la izquierda
        for (int i = 0; i < MAX_UNDO - 1; i++) {
            lista[i] = lista[i + 1];
        }
        lista[MAX_UNDO - 1] = lista_pos; // Insertar la nueva lista al final
    }
}

void ListaUndo::eliminar_ultimo() {
	if (cont > 0) {
		cont--;
	}
}

ListaPosiciones ListaUndo::ultimo_elemento() const {
	if (cont > 0) {
		return lista[cont - 1];
	}
}