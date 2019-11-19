#pragma once
#include "Mapa.h"

class Player
{
public:
	Mapa board;
	std::string name;
	Barco piezas[5];
	bool hasFleet;
	virtual void disparar() = 0;
	virtual bool placeShips(int& x, int& y) = 0;
};





