#include "juego.h"

Juego::Juego():tablero() {    
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

Juego::Juego(int fils, int cols, int numMinas) : Juego(fils, cols) {   
    num_jugadas = 0;
    mina_pisada = false;
    num_descubiertas = 0;

    int i = 0;
    while ( i < numMinas) {
        int f = 0 + rand() % (fils - 1);
        int c = 0 + rand() % (cols - 1);
        Celda cel = tablero.dame_celda(f, c);
        if (!cel.contiene_mina()) {
            cel.poner_mina();
            tablero.poner_celda(f, c, cel);
            num_minas++;
            i++;
        }
    }

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


            // Si ponemos una mina cambiamos los numeros de alrededor 
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
           // cout << "No se puede Marcar esta celda porque esta ya decubierta\n";
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
        num_descubiertas--;
    }
}



void Juego::juega(int fila, int columna, ListaPosiciones& lista_pos) {
    static int nRecursion = 0; // para poder sumar bien las jugadas 
    if (tablero.es_valida(fila, columna) && !mina_explotada() && !esta_completo()) {
      
        Celda c = tablero.dame_celda(fila, columna);
        if (!c.esta_descubierta() && !c.esta_marcada()) {
            nRecursion++;
            bool primRec = (nRecursion == 1);
            c.descubrir_celda();
            tablero.poner_celda(fila, columna, c);
            lista_pos.insertar_final(fila, columna);
            num_descubiertas++;

            if (c.contiene_mina()) {
                mina_pisada = true;
                num_jugadas++;
            }
            else {
                if (c.esta_vacia()) {
                    for (int j = 0; j < NUM_DIRECCIONES; ++j) {
                        int nF = fila + DIRECCIONES[j][0];
                        int nC = columna + DIRECCIONES[j][1];
                        if (tablero.es_valida(nF, nC)) {
                            juega(nF, nC, lista_pos);
                        }
                    }
                }
                if (primRec) {
                    num_jugadas++;
                }
            }
            nRecursion--;
           
        }
        
    }
   
}


// Como hago recursion con Lista Pos ??
/*
void Juego::juega(int fila, int columna, ListaPosiciones& lista_pos) {
    

    if (!tablero.es_valida(fila, columna)) {
       // cout << "Fila y columna no validas\n";
    }
    else if (mina_explotada() || esta_completo()) {
        
    }
    else {

        Celda c = tablero.dame_celda(fila, columna);

        if (!c.esta_descubierta() && !c.esta_marcada()) {
            c.descubrir_celda();
            tablero.poner_celda(fila, columna, c);
            lista_pos.insertar_final(fila, columna);
            num_descubiertas++;
            num_jugadas++;

            if (c.contiene_mina()) {
                mina_pisada = true;
  
            }
            else if (c.esta_vacia()) {
                 ListaPosiciones celdas_a_procesar;  // Celdas a procesar de la jugada actual
                 //celdas_a_procesar.insertar_final(fila, columna);

                     //int fil = celdas_a_procesar.dame_posX(0);
                     //int col = celdas_a_procesar.dame_posY(0);

                     // Miramos si las ocho celdas de alrededor estan vacias 
                for (int j = 0; j < NUM_DIRECCIONES; ++j) {
                    int nF = fila + DIRECCIONES[j][0];
                    int nC = columna + DIRECCIONES[j][1];

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
                if (celdas_a_procesar.longitud() > 0) {
                    juega(celdas_a_procesar.dame_posX(0), celdas_a_procesar.dame_posY(0), celdas_a_procesar);
                    
                }
                

                
            }
        }
    }
}
*/
