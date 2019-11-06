#pragma once
#include <iostream>
#include <string>
#include "Barco.h"

class MAPA 
{
public:
	MAPA() {};
	~MAPA() {};
	
	
	bool valido(int SelecX, int WorldX, int SelecY, int WorldY, int* world, Barco& Ship, int orientacion);
	bool validPlacement(int x, int y, Dir orientacion, Barco& Ship); /// int worldsizeX, int worlsizeY
	bool insertShip(Barco& Ship);

};

