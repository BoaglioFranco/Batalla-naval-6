#pragma once
#include "Player.h"
#include <stdlib.h>
#include <time.h> 


class EasyBOT :
	public Player
{
public:
	EasyBOT();
	bool placeShips(int& x, int& y) override; 
	Barco * disparar(int& x, int& y, Mapa& Mapa_enemigo) override;	
};

