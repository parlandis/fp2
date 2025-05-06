#pragma once

#include <string>
#include <fstream>

using namespace std;

// constante que indica el número de puestos
// de trabajo que existen.
const int MAX_CATEGORIAS = 3;

// chefs(0), camareros(1) y personal de limpieza(2),
typedef int tCategoriaProfesional;


// recibe un tipo de trabajo y lo transforma a string
string categoriaToString(const tCategoriaProfesional& t);



