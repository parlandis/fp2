#pragma once

#include <string>
#include <fstream>
#include "categoriasProf.h"

using namespace std;

const int TAM_INICIAL = 5;
const string CENTINELA_TRABAJADORES = "xxx";


typedef struct {
	string nif;
	tCategoriaProfesional categoria; 
	string nombreEvento;
} tTrabajador;

typedef struct {
	tTrabajador* lista;
	/* añade más campos si es necesario */
	int dim;
	int cont;
} tListaTrabajadores;



void inicialistaTrabajadores(tListaTrabajadores& lt);
ifstream& operator>>(ifstream& archivo, tListaTrabajadores& listaT);
tTrabajador buscarTrabajadorLibre(const tListaTrabajadores& lt, tCategoriaProfesional cp);
void destruirlistaTrabajadores(tListaTrabajadores& lt);


ostream& operator<<(ostream& out, const tListaTrabajadores& listaT);
int dameNumElems(const tListaTrabajadores& listaT);
tTrabajador dameTrabajador(const tListaTrabajadores& listaT, int i);
string dameEvento(const tTrabajador& trab);
void asignaEvento(tListaTrabajadores& listaT, int pos, string nombreEvento);
