#pragma once
#include "Mapa.h"

class Player
{
public:
	std::string name;
	Barco piezas[5];
	bool TieneFlota = true;
	virtual std::string disparar(int& x, int& y,Mapa& Mapa_enemigo) = 0;
	virtual bool placeShips(int& x, int& y, int i) = 0;
};





