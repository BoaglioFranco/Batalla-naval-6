#pragma once
#include "Player.h"
#include <stdlib.h>
#include <time.h> 


class ComputerPlayer :
	public Player
{
public:
	ComputerPlayer();
	bool placeShips(int& x, int& y) override; 
	Barco * disparar(int& x, int& y, Mapa& Mapa_enemigo) override;
	bool revisarFlota();
		
};

