#pragma once
#define MAX_LISTA 100
#include <iostream>
#include "checkML.h"

class ListaPosiciones {
private:
    typedef struct {
        int posx;
        int posy;
    } Posicion;
    int size;
    int cont;
    Posicion *lista;

public:
    ListaPosiciones();
    ListaPosiciones(const ListaPosiciones& lp);  // Construsctora de copia 
	~ListaPosiciones();
    void insertar_final(int x, int y);  
    int longitud() const;
    int dame_posX(int i) const;
    int dame_posY(int i) const;
};
