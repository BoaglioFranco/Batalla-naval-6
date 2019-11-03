#include "Barco.h"

Barco::Barco(int size, std::string name) {
	this->size = size;
	hits = 0;
	this->name = name;
	orientacion = D_UP;
}

Barco::Barco() {
	size = 0;
	hits = 0;
	orientacion = D_UP;
}

bool Barco::Hundido() {
	return size == hits;
}

void Barco::setSize(int size)
{
	this->size = size;
}

int Barco::getSize()
{
	return size;
}

void Barco::registerShot() {
	hits++;
}

