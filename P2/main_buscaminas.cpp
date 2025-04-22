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
#include "juego.h"

using namespace std;

// Como se implementa esta funcion nueva ???
bool juega(Juego& juego, int fila, int columna, ListaUndo& lista_undo) {


	if (fila == -3 && columna == -3) {  // Se realiza el undo
		cout << "UNDO: realizar undo.\n";
		ListaPosiciones ultima_jugada = lista_undo.ultimo_elemento();   // Pasamos la ultima jugada

		if (ultima_jugada.longitud() == 0) {
			//cout << "No se han realizado jugadas anteriores.\n";
			return true;
		}
		else {
			for (int i = 0; i < ultima_jugada.longitud(); i++) {
				juego.ocultar(ultima_jugada.dame_posX(i), ultima_jugada.dame_posY(i));
			}
			lista_undo.eliminar_ultimo();
			return true;
		}
	}
	else if (fila == -2 && columna == -2) {  // Marcar / desmarcar

		cout << "Introduce que ficha quieres Marcar/desmarcar: ";
		cin >> fila >> columna;
		juego.marcar_desmarcar(fila, columna);
		return true;
	}
	else if (fila == -1 && columna == -1) {   
		cout << "Has abandonado el juego\n";
		return false;
		//juego.destruye();
	}
	else if(fila > 0 || fila < juego.dame_num_filas() || columna > 0 || columna < juego.dame_num_columnas()){  // Metemos las modificaciones en undo 
		ListaPosiciones posMod;
		juego.juega(fila, columna, posMod);
		

		if (posMod.longitud() > 0 && !juego.mina_explotada()) {
			lista_undo.insertar_final(posMod);
		}
		return true;
	}
}


void crearJuegoAleatorio(int &f, int &c, int& numM) {
	cout << "Numero de filas (>3) y columnas (>3) del tablero: ";
	cin >> f >> c;
	int numMax = f * c / 3;
	cout << "Numero de Minas (<" << numMax << "): ";
	cin >> numM;
}




// ni lo de aletorio como tiene que ir 
// Como aumento numJugadas
// 
//Como nos blindamos para que no pasen archivos solo de jeugo
 // buscar Por Busqueda binari????

// Codigo repetido 


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(NULL));
	GestorJuegos gj;
	int opcion = 0;
	Juego* actual = nullptr;
	ListaUndo listaundo;
	mostrar_cabecera();
	int f, c, numM;

	if (!gj.cargar_juegos()) {
		cout << "Error al cargar Juegos\n";
		cout << "Se genera un juego aleatorio...\n";
		crearJuegoAleatorio(f,c, numM);
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
			else {
				cout << "Se genera un juego aleatorio...\n";
				crearJuegoAleatorio(f, c, numM);
				actual = new Juego(f, c, numM);
				gj.insertar(*actual);
			}
		}
		else {
			cout << "El fichero cargado no tiene juegos... Se crea uno aleatorio\n";
			crearJuegoAleatorio(f, c, numM);
			actual = new Juego(f, c, numM);
			gj.insertar(*actual);
		}
	}
	bool jugando = true;
	while (jugando && actual != nullptr && !actual->mina_explotada() && !actual->esta_completo()) {
		mostrar_juego_consola(*actual);
		int fila, col;
		pedir_pos(fila, col);
		jugando = juega(*actual, fila, col, listaundo);
	}
	if (actual != nullptr) {
		mostrar_resultado(*actual);
		if (jugando) {
			gj.eliminar(0);
			delete actual;
		}
	}
	gj.guardar_lista_juegos();

	return 0;
}
