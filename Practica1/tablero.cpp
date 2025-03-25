#include "tablero.h"
#include <iostream>







Tablero::Tablero() {
    filas = 0;
    columnas = 0;
}

Tablero::Tablero(int fils, int cols) {
    
    filas = fils;
    columnas = cols;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            celdas[i][j] = Celda();
        }
    }
}

void Tablero::destruye() {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            celdas[i][j].destruye();
        }
    }
}

int Tablero::num_filas()const {
    return filas;
}

int Tablero::num_columnas()  const {
    return columnas;
}

bool Tablero::es_valida(int fila, int columna) const {
    return (fila >= 0 && fila < filas && columna >= 0 && columna < columnas);
}

Celda Tablero::dame_celda(int fila, int columna) const{

    return celdas[fila][columna];
}

void Tablero::poner_celda(int fila, int columna, const Celda& celda) {

	if (es_valida(fila, columna)) {
		celdas[fila][columna] = celda;
	}
	else {
		std::cout << "Celda no válida" << std::endl;
	}
}