#include "inputOutput.h"
#include <iomanip>

#include <iostream>

using namespace std;

const char CHAR_MINA = '*';  // Mina

void mostrar_separador(Juego& juego);
void color_numero(int numero);


istream& operator >>(istream& in, Juego& juego) {
	int nfils, ncols, nMinas;
	in >> nfils >> ncols >> nMinas;

    juego = Juego(nfils, ncols);
    
	int fila, columna;
	for (int i = 0; i < nMinas; i++) {
		in >> fila >> columna;
        juego.poner_mina(fila, columna);
	}
    return in;
}

void pedir_pos(int& fila, int& columna) {
    cout << "Introduce la fila y la columna: \n";
    cin >> fila >> columna;
}

void mostrar_resultado( Juego& juego) {
    if (juego.mina_explotada()) {
        cout << "HAS PERDIDO\n";
    }
    if (juego.esta_completo()) {
        cout << "HAS GANADO\n";
    }
}

void mostrar_cabecera() {
    cout << "Buscaminas\n";
    cout << "-----------\n";
}

bool cargar_juego(Juego& juego) {
    string nombreF;
    cout << "Introduce el nombre del fichero: ";
	cin >> nombreF;
    cout << "\n";
    
	ifstream archivo(nombreF);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo\n";
        return false;
    }
	archivo >> juego;
    archivo.close();
    return true;
}

void color_numero(int numero) {
    switch (numero) {
    case 1: cout << BLUE; break;
    case 2: cout << GREEN; break;
    case 3: cout << RED; break;
    case 4: cout << DBLUE; break;
    case 5: cout << DGREEN; break;
    case 6: cout << DRED; break;
    default:
        break;
    }
}


void mostrar_separador( Juego& juego) {
    cout << "\t -+";
    for (int col = 0; col < juego.dame_num_columnas(); ++col) {
        cout << setw(N_HUECOS + 1) << setfill('-') << '+' << setfill(' ');
    }
    cout << endl;
}

void mostrar_celda(Juego& juego, int fila, int columna) {

    
    if (!juego.esta_descubierta(fila, columna) && !juego.esta_marcada(fila, columna)) {
        cout << BG_GRAY << GRAY << N_HUECOS << setfill(' ') << ' ' << RESET;
    }
    else {
        cout << BG_BLACK << BLACK;
        if (!juego.esta_marcada(fila, columna)) {
            if (juego.contiene_mina(fila, columna)) {
                cout << RED << setw(N_HUECOS) << setfill(' ') << CHAR_MINA << RESET;
            }
            else {
                if (juego.esta_vacia(fila, columna)) {
                    cout << setw(N_HUECOS) << setfill(' ') << ' ' << RESET;
                }
                else {
                    if (juego.contiene_numero(fila, columna)) {
                        int numero = juego.dame_numero(fila, columna);
                        color_numero(numero);
                        cout << setw(N_HUECOS) << setfill(' ') << numero << RESET;
                    }
                    else {
                        cout << BG_RED << RED << setw(N_HUECOS) << setfill(' ') << ' ' << RESET;
                    }
                }
            }
        }
        else {
            cout << BG_ORANGE << ORANGE << setw(N_HUECOS) << setfill(' ') << ' ' << RESET;
        }
    }
}


void mostrar_juego_consola( Juego& juego){
    
    // mostrar el número de jugadas del juego
    cout << setw(N_HUECOS) << "Jugadas: " << juego.dame_num_jugadas() << "\n";

    cout << "\t  |";
    for (int col = 0; col < juego.dame_num_filas(); col++) {
        cout << LBLUE << setw(N_HUECOS) << col << RESET << '|';
    }
    cout << endl;

    mostrar_separador(juego);

    // mostrar tablero
    for (int f = 0; f < juego.dame_num_filas(); f++) {
        // mostrar numero de fila
        cout << "\t" << LBLUE << setw(2) << f << RESET << '|';
        // mostrar la fila
        for (int c = 0; c < juego.dame_num_columnas(); c++) {
            mostrar_celda(juego, f, c);
            cout << '|';
        }
        cout << endl;

        mostrar_separador(juego);
    }
    cout << endl;
}


