#pragma once
#include "Barco.h"

class MAPA 
{
public:
	MAPA() {};
	~MAPA() {};
	int **grid;
	
	bool valido(int SelecX, int WorldX, int SelecY, int WorldY,int * world, Barco& Ship);
	bool validPlacement(int x, int y, Dir orientacion, Barco& Ship); /// int worldsizeX, int worlsizeY
	bool insertShip(int x, int y, Dir orientacion, Barco& ship);

};

