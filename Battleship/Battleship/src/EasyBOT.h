#pragma once
#include "Player.h"
#include <stdlib.h>
#include <time.h> 

class EasyBOT :
	public Player
{
public:
	/*
	--------------------------------------------------------------------------------------------
	Es el bot mas sencillo, simplemente dispara al azar, sin tener nocion alguna de lo que conforma un barco.
	--------------------------------------------------------------------------------------------
	*/
	EasyBOT();
	bool placeShips(int& x, int& y) override; 
	Barco * disparar(int& x, int& y, Mapa& Mapa_enemigo) override;	
};

