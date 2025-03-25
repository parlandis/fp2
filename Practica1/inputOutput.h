#pragma once


#include "colors.h"
#include <fstream>
#include "juego.h"

const int N_HUECOS = 2; // huecos a dejar en el formato de las celdas.

using namespace std;


void mostrar_juego_consola( Juego& juego);
void mostrar_celda(Juego& juego, int f, int c);
bool cargar_juego(Juego& juego);
void mostrar_cabecera();
void pedir_pos(int& fila, int& columna);
void mostrar_resultado( Juego& juego);
bool guardar_partida(Juego& juego);
ostream& operator << (ostream& out, Juego& juego);