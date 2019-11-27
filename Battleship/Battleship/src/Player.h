#pragma once
#include "Mapa.h"

class Player
{
public:

	Mapa board;
	std::string name;
	Barco piezas[5];
	int ite_Barcos;
	bool TieneFlota = true;
	virtual Barco * disparar(int& x, int& y,Mapa& Mapa_enemigo) = 0;
	virtual bool placeShips(int& x, int& y) = 0;
	bool revisarFlota(){
		int i = 0;
		int flag = 0;

		while (i < 5 && flag == 0)
		{
			if (piezas[i].hundido())
				i++;
			else
				flag = 1;
		}

		if (flag == 0)
			this->TieneFlota = false;

		return this->TieneFlota;
	}
};





