#include "gestor.h"

GestorJuegos::GestorJuegos() {

}
bool GestorJuegos::cargar_juegos() {
	string nombreF;
	cout << "Introduce el nombre del Fichero de Juegos: ";
	cin >> nombreF;
	cout << "\n";

	ifstream archivo(nombreF);
	if (!archivo.is_open()) {
		cout << "Error al abrir el archivo de Juegos o No existe\n";
		return false;
	}
	int nJ;
	archivo >> nJ;
	while (nJ > 0) {
		int fil, col, numM;
		archivo >> fil >>  col >> numM;


		Juego nuevo = Juego(fil, col);
		int fM, cM;
		for (int i = 0;i < numM; i++) {
			archivo >> fM >> cM;
			nuevo.poner_mina(fM, cM);
		}
		insertar(nuevo);
		nJ--;
	}
	return true;

}
void GestorJuegos::mostrar_lista_juegos() const {
	cout << "Mostrando lista de Juegos por Orden de dificultad\n";

	int nJ = numero_juegos();
	for (int i = 0; i < nJ; i++) {
		Juego j = dame_juego(i);
		cout << "Juego " << i << ":\n";
		cout << "\tDimension: " << j.dame_num_filas() << " x " << j.dame_num_columnas();
		
		cout << "\n \tMinas: " << j.dame_num_minas();
		cout << endl;
	}
}
int GestorJuegos::numero_juegos() const {
	return juegos.dame_longitud();
}
const Juego& GestorJuegos::dame_juego(int pos) const {
	return juegos.dame_juego(pos);
}
int GestorJuegos::insertar(const Juego& juego) {
	int pos = juegos.insertar(juego);
	
	return pos;
}
void GestorJuegos::eliminar(int pos) {
	juegos.eliminar(pos);
}
bool GestorJuegos::hay_juegos() const {
	return !juegos.es_vacia();
}
bool GestorJuegos::guardar_lista_juegos() const {
	string nombreF;
	cout << "Dame el nombre del archivo en el que quieres guardar la partida: ";
	cin >> nombreF;
	cout << endl;
	ofstream archivo(nombreF);
	if (!archivo.is_open()) {
		cout << "Error al guardar\n";
		return false;
	}
	int numJ = juegos.dame_longitud();
	archivo << numJ << endl;

	for (int i = 0; i < numJ; i++) {
		const Juego& juego = juegos.dame_juego(i);
		int f, c, nM;
		f = juego.dame_num_filas();
		c = juego.dame_num_columnas();
		
		nM = juego.dame_num_minas();

		archivo << f << " " << c << " \n" << nM << " \n";

		for (int fil = 0; fil < f; ++fil) {
			for (int col = 0; col < c; ++col) {
				if (juego.contiene_mina(fil, col)) {
					archivo << fil << " " << col << " \n";
				}
			}
		}
		archivo << endl;
	}
	archivo.close();
	return true;
}
