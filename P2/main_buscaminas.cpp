// Versión jugable en internet: https://minesweeper.online/es/
// Alberto de la Encina 
// Puri Arenas

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "colors.h"
#include "inputOutput.h"
#include "juego.h"
#include "checkML.h"

using namespace std;

void juega(Juego& juego, int fila, int columna, ListaUndo& lista_undo) {


	if (fila == -3 && columna == -3) {  // Se realiza el undo
		cout << "UNDO: realizar undo.\n";
		ListaPosiciones ultima_jugada = lista_undo.ultimo_elemento();   // Pasamos la ultima jugada

		if (ultima_jugada.longitud() == 0) {
			//cout << "No se han realizado jugadas anteriores.\n";
			
		}
		else {
			for (int i = 0; i < ultima_jugada.longitud(); i++) {
				juego.ocultar(ultima_jugada.dame_posX(i), ultima_jugada.dame_posY(i));
			}
			lista_undo.eliminar_ultimo();
		}
	}
	else if (fila == -2 && columna == -2) {  // Marcar / desmarcar

		cout << "Introduce que ficha quieres Marcar/desmarcar: ";
		cin >> fila >> columna;
		juego.marcar_desmarcar(fila, columna);
	}
	else if (fila == -1 && columna == -1) {   
		cout << "Has abandonado el juego\n";
		juego.destruye();
	}
	else {  // Metemos las modificaciones en undo 
		ListaPosiciones posMod;
		juego.juega(fila, columna, posMod);

		if (posMod.longitud() > 0 && !juego.mina_explotada()) {
			lista_undo.insertar_final(posMod);
		}
	}
}




int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(NULL));
    Juego juego;
    ListaUndo lista_undo; 
    int f, c;
	mostrar_cabecera();

	if (!cargar_juego(juego)) {
		cout << "No se ha podido cargar el juego\n";
		
	}
	else {

		do {
			mostrar_juego_consola(juego);
			pedir_pos(f, c);
			juega(juego, f, c, lista_undo);
		} while ((f != -1 || c != -1) && !juego.esta_completo() && !juego.mina_explotada());

		mostrar_resultado(juego);
	}
    return 0;
}
