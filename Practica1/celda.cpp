#include "celda.h"

Celda::Celda() {
	descubierta = false;
	estado = VACIA;
	numero = 0;
	marcada = false;
}

void Celda::destruye() {
	descubierta = false;
	estado = VACIA;
	numero = 0;
	marcada = false;
}

int Celda::dame_numero() {
	return numero;
}


bool Celda::esta_descubierta() const {

	return descubierta;
}

bool Celda::contiene_mina() const {
	return estado == MINA;
}

bool Celda::contiene_numero() const {
	return estado == NUMERO;
}

bool Celda::esta_vacia() const {
	return estado == VACIA;
}

bool Celda::esta_marcada() const {
	return marcada;	
}

void Celda::descubrir_celda() {
	descubierta = true;
}

void Celda::ocultar_celda() {
	descubierta = false;
}

void Celda::poner_mina() {
	estado = MINA;
}

void Celda::poner_numero(int n) {
	numero = n;
	estado = NUMERO;
}

void Celda::marcar_celda() {
	marcada = true;
}

void Celda::desmarcar_celda() {
	marcada = false;
}