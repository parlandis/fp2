#pragma once

#include "ListaPosiciones.h"

const int MAX_UNDO = 10;

class ListaUndo {
private:
    int cont;
    ListaPosiciones lista[MAX_UNDO];

public:
    ListaUndo();
    

    void destruye();

	void eliminar_ultimo();
    void insertar_final(const ListaPosiciones& lista_pos);
    ListaPosiciones ultimo_elemento() const;
};
