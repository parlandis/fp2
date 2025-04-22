// Versión jugable en internet: https://minesweeper.online/es/
// Alberto de la Encina 
// Puri Arenas

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "colors.h"
#include "checkML.h"
#include "gestor.h"
#include "inputOutput.h"

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




// No entiendo lo de gestor 
// ni lo de aletorio como tiene que ir 
// ni como se carga
//Como nos blindamos para que no pasen archivos solo de jeugo


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(NULL));
	GestorJuegos gj;
	int opcion = 0;
	Juego* actual = nullptr;
	ListaUndo listaundo;
	mostrar_cabecera();

	if (!gj.cargar_juegos()) {
		cout << "Error al cargar Juegos\n";
		cout << "Se genera un juego aleatorio...\n";

		int f = 3, c = 3, numM;                    // El numero de filas se pide ?? 
		cout << "Numero de filas (>3) y columnas (>3) del tablero: ";
		cin >> f >> c;
		numM = rand() % ((f * c) / 3) + 1;
		actual = new Juego(f, c, numM);
		gj.insertar(*actual);
	}
	else {
		if (gj.hay_juegos()) {
			cout << "Juego nuevo (opcion 1) o juego existente(opcion 2)\n";
			cin >> opcion;
			if (opcion == 2) {
				gj.mostrar_lista_juegos();
				cout << "Selecciona partida:\n";
				int partida;
				cin >> partida;

				if (partida >= 0 && partida < gj.numero_juegos()) {
					actual = new Juego(gj.dame_juego(partida));
				}
			}
		}
		else {
			cout << "El fichero cargado no tiene juegos... Se crea uno aleatorio\n";
			int f = 3, c = 3, numM;                    // El numero de filas se pide ?? 
			cout << "Numero de filas (>3) y columnas (>3) del tablero: ";
			cin >> f >> c;
			numM = rand() % ((f * c) / 3) + 1;
			actual = new Juego(f, c, numM);
			gj.insertar(*actual);
		}
	}
	bool jugando = true;
	while (jugando && actual != nullptr && !actual->mina_explotada() && !actual->esta_completo()) {
		mostrar_juego_consola(*actual);
		int fila, col;
		pedir_pos(fila, col);
		juega(*actual, fila, col, listaundo);
	}
	if (actual != nullptr) { // Check if 'actual' is not null before dereferencing
		mostrar_resultado(*actual);
		gj.eliminar(0);
		delete actual;
	}
	else {
		cout << "No se pudo inicializar el juego. Saliendo...\n";
	}
	gj.guardar_lista_juegos();

	return 0;
}
