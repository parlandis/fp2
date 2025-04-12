#include "listaUndo.h"


ListaUndo::ListaUndo() {
	cont = 0;
    for (int i = 0; i < MAX_UNDO; i++) {
		lista[i] = nullptr; 
    }
}

ListaUndo::~ListaUndo() {
    for (int i = 0; i < cont; i++) {
        delete lista[i];
        lista[i] = nullptr;
    }
}
void ListaUndo::insertar_final(const ListaPosiciones& lista_pos) {  // Eliminamos por alante o por atras usando elim ult???
    ListaPosiciones* ultima = new ListaPosiciones(lista_pos);

    if (cont < MAX_UNDO) {
        lista[cont] = ultima;
        cont++;
    }
    else {
        delete lista[0];
        for (int i = 0; i < MAX_UNDO - 1; i++) {
            lista[i] = lista[i + 1];
        }
        lista[MAX_UNDO - 1] = ultima;
    }
}

void ListaUndo::eliminar_ultimo() {
    delete lista[cont - 1];
    cont--;
}

ListaPosiciones ListaUndo::ultimo_elemento() const {
    if (cont > 0) {
        return *lista[cont - 1];
    }
}