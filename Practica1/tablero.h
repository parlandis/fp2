#pragma once
#include "celda.h"
#include <iostream>

using namespace std;

const int MAX_FILS = 10;
const int MAX_COLS = 10;

class Tablero {
private:
    int filas, columnas;
    Celda celdas[MAX_FILS][MAX_COLS];

public:

    Tablero();
    Tablero(int fils, int cols);

    void destruye();

    int num_filas() const;
    int num_columnas() const;
    bool es_valida(int fila, int columna) const ;
    Celda dame_celda(int fila, int columna) const;
    void poner_celda(int fila, int columna, const Celda& celda);
};

