#include "listaTrabajadores.h"
#include <iomanip>







void inicialistaTrabajadores(tListaTrabajadores& lt) {
	lt.cont = 0; 
	lt.dim = TAM_INICIAL;
	lt.lista = new tTrabajador[lt.dim];

}
ifstream& operator>>(ifstream& archivo, tListaTrabajadores& listaT) {
	archivo.open("trabajadores.txt");
	if (archivo.is_open()) {
		string aux;
		tTrabajador trab;
		archivo >> aux;
		while (aux != "xxx") {
			trab.nif = aux;
			archivo >> trab.categoria >> trab.nombreEvento;
			if (listaT.cont == listaT.dim) {
				int nDim = listaT.dim * 2;
				tTrabajador* lista = new tTrabajador[nDim];
				for (int i = 0; i < listaT.cont; i++) {
					lista[i] = listaT.lista[i];
				}
				delete [] listaT.lista;
				listaT.lista = lista;
				listaT.dim = nDim;
			}
			listaT.lista[listaT.cont] = trab;
			listaT.cont++;
			archivo >> aux;
		}
	}

	return archivo;
	
}

tTrabajador buscarTrabajadorLibre(const tListaTrabajadores& lt, tCategoriaProfesional cp) {
	tTrabajador t;
	



}
void destruirlistaTrabajadores(tListaTrabajadores& lt) {



}







ostream& operator<<(ostream& out, const tTrabajador& t) {
	out << "NIF: " << t.nif << "    Puesto: " << left << setw(10) << categoriaToString(t.categoria) << "  Evento asignado: " << t.nombreEvento;
	return out;
	return out;
}

ostream& operator<<(ostream& out, const tListaTrabajadores& listaT) {
	for (int i = 0; i < listaT.cont; i++)
		out << listaT.lista[i] << endl;
	out << endl;
	return out;
}

void asignaEvento(tListaTrabajadores& listaT, int pos, string nombreEvento) {
	listaT.lista[pos].nombreEvento = nombreEvento;
}

int dameNumElems(const tListaTrabajadores& listaT) {
	return listaT.cont;
}
tTrabajador dameTrabajador(const tListaTrabajadores& listaT, int i) {
	return listaT.lista[i];
}

string dameEvento(const tTrabajador& trab) {
	return trab.nombreEvento;
}
