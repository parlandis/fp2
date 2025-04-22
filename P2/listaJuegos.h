#include "juego.h"
#include "checkML.h"


class ListaJuegos {
private:
	int cont;
	Juego** lista;
	int capacidad;
public:
	ListaJuegos();
	~ListaJuegos();
	int insertar(const Juego& juego);
	int dame_longitud() const;
	bool es_vacia() const;
	const Juego& dame_juego(int pos) const;
	void eliminar(int pos);
	void buscar(const Juego& juego, int& pos);
};