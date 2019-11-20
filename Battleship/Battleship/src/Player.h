#pragma once
#include "Mapa.h"

class Player
{
public:

	Mapa board;
	std::string name;
	Barco piezas[5];
	bool TieneFlota = true;
	virtual Barco * disparar(int& x, int& y,Mapa& Mapa_enemigo) = 0;
	virtual bool placeShips(int& x, int& y) = 0;

};





