#include "Celda.h"

Celda::Celda()
{
	dato = 0;
	isShot = false;
	miembroDe = nullptr;
}

void Celda::registrarDisparo()
{
	dato -= 1;
	isShot = true;
	if (this->miembroDe) {
		miembroDe->registerShot();
	}
}

void Celda::setMiembroDe(Barco& miembro)
{
	this->miembroDe = &miembro;
}