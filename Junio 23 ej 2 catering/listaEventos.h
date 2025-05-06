#pragma once

# include <fstream>
# include <string>
# include <iostream>
#include "categoriasProf.h"

using namespace std;

const int MAX_EVENTOS = 10;
const string CENTINELA_EVENTOS = "xxx";


typedef struct  {
	string nombreEvento;
	int personal[MAX_CATEGORIAS];
} tEvento;

typedef tEvento* tPtrEvento;

typedef struct tListaEventos {
	tPtrEvento eventos[MAX_EVENTOS];
	int cont;
};




void decrementaPersonal(tEvento& evento, tCategoriaProfesional tt);
ostream& operator<<(ostream& out, const tListaEventos& eventos);
int dameNumElems(const tListaEventos& listaE);
tPtrEvento dameEvento(const tListaEventos& listaE, int pos);
int dameNumTrabajadores(const tEvento& evento, const tCategoriaProfesional& tt);
string dameTipoEvento(const tEvento& evento);
