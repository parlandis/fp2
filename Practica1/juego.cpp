#include "juego.h"

Juego::Juego() {    
    num_jugadas = 0;
    mina_pisada = false;
    num_minas = 0;
    num_descubiertas = 0;
}

Juego::Juego(int fils, int cols) : tablero(fils, cols) {
    num_jugadas = 0;
    mina_pisada = false;
    num_minas = 0;
    num_descubiertas = 0;
   
}

void Juego::destruye() {
    tablero.destruye();
    num_minas = 0;
    num_descubiertas = 0;
    mina_pisada = false;
}

int Juego::dame_num_jugadas() const {
    return num_jugadas;
}

int Juego::dame_num_filas()const {
    return tablero.num_filas();
}

int Juego::dame_num_columnas() const {
    return tablero.num_columnas();
}

int Juego::dame_num_minas() const {
    return num_minas;
}

bool Juego::contiene_mina(int fila, int columna)const {
    return tablero.dame_celda(fila, columna).contiene_mina();
}

bool Juego::esta_completo() const {  // devuelve si hemos quitados todas las celdas sin mina
    return (num_descubiertas == (dame_num_filas() * dame_num_columnas() - num_minas)) && !mina_explotada();
}

bool Juego::mina_explotada() const {
    return mina_pisada;
}

bool Juego::esta_descubierta(int fila, int columna) const {
    return tablero.dame_celda(fila, columna).esta_descubierta();
}

bool Juego::esta_marcada(int fila, int columna) const {
    return tablero.dame_celda(fila, columna).esta_marcada();
}

bool Juego::esta_vacia(int fila, int columna)const {
    return tablero.dame_celda(fila, columna).esta_vacia();
}

bool Juego::contiene_numero(int fila, int columna)const {
    return tablero.dame_celda(fila, columna).contiene_numero();
}

int Juego::dame_numero(int fila, int columna)const {
    return tablero.dame_celda(fila, columna).dame_numero();
}

void Juego::poner_mina(int fila, int columna) {

    if (tablero.es_valida(fila, columna) && !tablero.dame_celda(fila, columna).contiene_mina() && !tablero.dame_celda(fila, columna).esta_descubierta()) {
        Celda c;
        c.poner_mina();
		tablero.poner_celda(fila, columna, c);
		num_minas++;



        int If[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int Ic[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

        for (int i = 0; i < NUM_DIRECCIONES; i++) {
            int incF = fila + If[i];
            int incC = columna + Ic[i];

            if (tablero.es_valida(incF, incC) && !tablero.dame_celda(incF, incC).contiene_mina()) {
             
				Celda aux = tablero.dame_celda(incF, incC);   
                if (aux.contiene_numero()) {
                    
                    aux.poner_numero(aux.dame_numero() + 1);
                    tablero.poner_celda(incF, incC, aux);
                }
                else {
                    
                    aux.poner_numero(1);
                    tablero.poner_celda(incF, incC, aux); 
                }
                
            }
        }
    }
}

void Juego::marcar_desmarcar(int fila, int columna) {   
    if (tablero.es_valida(fila, columna)) {
        Celda a = tablero.dame_celda(fila, columna);
        if (a.esta_descubierta()) {
            cout << "No se puede Marcar esta celda porque esta ya decubierta\n";
        }
        else {
            if (!a.esta_marcada()) {
                a.marcar_celda();
                tablero.poner_celda(fila, columna, a);
            }
            else {
                a.desmarcar_celda();
                tablero.poner_celda(fila, columna, a);
            }
        }
    }
}

void Juego::ocultar(int fila, int columna) {
    if (tablero.es_valida(fila, columna) && tablero.dame_celda(fila,columna).esta_descubierta()){
        Celda c = tablero.dame_celda(fila, columna);
        c.ocultar_celda();
        tablero.poner_celda(fila, columna, c);
    }
}


void Juego::juega(int fila, int columna, ListaPosiciones& lista_pos) {
    if (!tablero.es_valida(fila, columna)) {
        cout << "Fila y columna no validas\n";
        return;
    }

    if (mina_explotada() || esta_completo()) {
        return;
    }

    Celda c = tablero.dame_celda(fila, columna);

    if (!c.esta_descubierta() && !c.esta_marcada()) {
        c.descubrir_celda();
        tablero.poner_celda(fila, columna, c);
        lista_pos.insertar_final(fila, columna);
        num_descubiertas++;
        num_jugadas++;

        if (c.contiene_mina()) {
            mina_pisada = true;
            return;
        }
        if (c.esta_vacia()) {
            ListaPosiciones celdas_a_procesar;
            celdas_a_procesar.insertar_final(fila, columna);

                
                int fil = celdas_a_procesar.dame_posX(0);
                int col = celdas_a_procesar.dame_posY(0);

                for (int j = 0; j < NUM_DIRECCIONES; ++j) {
                    int nF = fil + DIRECCIONES[j][0];
                    int nC = col + DIRECCIONES[j][1];

                    if (tablero.es_valida(nF, nC)) {
                        Celda vecina = tablero.dame_celda(nF, nC);
                        if (!vecina.esta_descubierta() && !vecina.esta_marcada()) {
                            vecina.descubrir_celda();
                            tablero.poner_celda(nF, nC, vecina);
                            lista_pos.insertar_final(nF, nC);
                            num_descubiertas++;

                            if (vecina.esta_vacia()) {
                                celdas_a_procesar.insertar_final(nF, nC);
                            }
                        }
                    }
                }
            

        }
    }
}
