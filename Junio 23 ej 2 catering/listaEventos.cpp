#include "ListaEventos.h"


ostream& operator<<(ostream& out, const tEvento& evento) {
	out << "Evento: " << evento.nombreEvento << endl;
	out << "  Empleados necesarios -> ";
	for (tCategoriaProfesional k = 0; k < MAX_CATEGORIAS; k++)
		out << "  " << evento.personal[k] << " " << categoriaToString(k);
	return out;
}

ostream& operator<<(ostream& out, const tListaEventos& listaE) {
	for (int i = 0; i < listaE.cont; i++) {
		cout << *listaE.eventos[i] << endl;
		
	}
	return out;
}


int dameNumElems(const tListaEventos& listaE) {
	return listaE.cont;
}

int dameNumTrabajadores(const tEvento& evento, const tCategoriaProfesional& tt) {
	return evento.personal[tt];
}

tPtrEvento dameEvento(const tListaEventos& listaE, int pos) {
	return listaE.eventos[pos];
}

void decrementaPersonal(tEvento& evento, tCategoriaProfesional tt) {
	evento.personal[tt]--;
}

string dameTipoEvento(const tEvento& evento) {
	return evento.nombreEvento;
}


