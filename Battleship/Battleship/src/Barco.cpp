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

bool Barco::hundido() {
	
	if (size == hits) {
		isSunk = true;
	}

	return isSunk;
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
	return isVertical;
}

void Barco::setOrientation()
{
	isVertical = !isVertical;
}


