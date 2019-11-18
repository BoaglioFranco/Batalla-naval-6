#include "Barco.h"

Barco::Barco(int size, std::string name) {
	this->size = size;
	hits = 0;
	this->name = name;
}

Barco::Barco() {
	size = 0;
	hits = 0;
}

Barco Barco::hundido(Barco& barquito) {
	if (barquito.getSize() == barquito.hits) {
		barquito.isSunk = true;
	}

	return barquito;
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

bool Barco::getOrientation()
{
	return this->isVertical;
}

void Barco::setOrientation()
{
	isVertical = !isVertical;
}
