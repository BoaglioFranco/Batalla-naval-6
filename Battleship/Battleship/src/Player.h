#pragma once
#include "Mapa.h"

class Player
{
public:
	std::string name;
	Barco piezas[5];
	bool hasFleet;
	virtual void disparar() = 0;
	virtual void placeShips() = 0;
};




