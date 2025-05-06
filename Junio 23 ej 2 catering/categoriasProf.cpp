#include "categoriasProf.h"


string categoriaToString(const tCategoriaProfesional& t) {
	string s = "sin definir";
	if (t == 0) s = "chef";
	else if (t == 1) s = "camarero";
	else if (t == 2) s = "limpieza";
	return s;
}
