
#pragma once
#include "tablero.h"
#include "listaUndo.h"
#include <iostream>
#include <cstdlib>
#include "checkML.h"

using namespace std;


const int NUM_DIRECCIONES = 8;
const int VECTOR_DIRECCION = 2;
const int DIRECCIONES[NUM_DIRECCIONES][VECTOR_DIRECCION] = { -1, -1, -1, 0, -1, 1, 0 ,1, 1, 1, 1, 0,  1, -1, 0, -1 };

class Juego {
private:
    Tablero tablero;
    int num_jugadas;
    bool mina_pisada;
    int num_minas;
    int num_descubiertas;
public:
    Juego();
    Juego(int fils, int cols);
    Juego(int fils, int cols, int numMinas);

    void destruye();

    int dame_num_jugadas() const;
    int dame_num_filas() const;
    int dame_num_columnas() const;
    int dame_num_minas() const;
    bool contiene_mina(int fila, int columna) const;
    bool esta_completo() const;
    bool mina_explotada() const;
    bool esta_descubierta(int fila, int columna) const;
	bool esta_marcada(int fila, int columna) const;
     bool esta_vacia(int fila, int columna) const;
    bool contiene_numero(int fila, int columna) const;
    int dame_numero(int fila, int columna) const;
    void poner_mina(int fila, int columna);
    void marcar_desmarcar(int fila, int columna);
    void ocultar(int fila, int columna);
    void juega(int fila, int columna, ListaPosiciones& lista_pos);
};

