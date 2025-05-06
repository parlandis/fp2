#include "listaTrabajadores.h"
#include <iostream>
#include "ListaEventos.h"


bool cargarlistaTrabajadores(tListaTrabajadores& listaT);
bool cargarListaEventos(tListaEventos& listaE);


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	tListaTrabajadores listaT;
	inicialistaTrabajadores(listaT);
	ifstream archivo;
	archivo >> listaT;
	archivo.close();

	// 1.- inicia y carga la lista de trabajadores
	
	// 2.- Si la carga tiene éxito:

	       cout << "LISTA DE TRABAJADORES INICIAL: " << endl << endl;
	       cout << listaT << endl;
		   tListaEventos listaEventos;

	
	//   2.1. - inicia y carga la lista de eventos
	//   2.2. - si la carga tiene éxito:

	        cout << "LISTA DE EVENTOS INICIAL: " << endl << endl;
		    cout << listaEventos << endl;

	//      2.2.1. - asigna los eventos a los trabajadores
	
			cout << "LISTA DE TRABAJADORES TRAS LA ASIGNACION: " << endl << endl;
			cout << listaT << endl;
			cout << "LISTA DE EVENTOS TRAS LA ASIGNACION: " << endl << endl;
			cout << listaEventos << endl;

	//      2.2.2.- elimina el evento CumpleAna
	      
			cout << "LISTA DE TRABAJADORES TRAS LA ELIMINACION: " << endl << endl;
			cout << listaT << endl;
			cout << "LISTA DE EVENTOS TRAS LA ELIMINACION: " << endl << endl;
			cout << listaEventos << endl;

	// 3.- destruye las listas donde creas conveniente
	// 4.- manda mensajes de error sobre la apertura de ficheros donde
	//     creas conveniente.

	return 0;

}

bool cargarlistaTrabajadores(tListaTrabajadores& listaT) {
	ifstream archivo;
	archivo.open("trabajadores.txt");
	bool apertura = false;
	if (archivo.is_open()) {

		/* lee la lista de trabajadores del archivo 
		   usando el operador correspondiente */

		apertura = true;
		archivo.close();

	}
	return apertura;
}

bool cargarListaEventos(tListaEventos& listaE) {
	ifstream archivo;
	archivo.open("eventos.txt");
	bool apertura = false;
	if (archivo.is_open()) {

		/* lee la lista de eventos del archivo
		   usando el operador*/

		archivo.close();
		apertura = true;
	}
	return apertura;
}

