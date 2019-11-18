#pragma once
#include <iostream>
#include <string>
#include "Barco.h"
#include "Celda.h"

class Mapa 
{
public:
	Mapa() {};
	~Mapa() {};
	Celda grid[10][10];
	
	void mostrarMapa();
	bool validPlacement(int x, int y, Barco& Ship);/// int worldsizeX, int worlsizeY
	bool insertShip(int x, int y, Barco& ship);
	Barco& sendReference(Barco& barquito);

};

