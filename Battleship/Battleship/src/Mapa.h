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
	
	void mostrarMapa();// por consola, testing purposes only
	bool validPlacement(int x, int y, Barco& Ship);/// int worldsizeX, int worlsizeY
	bool insertShip(int x, int y, Barco& ship);// Pone un barco en el mapa
	bool RegistrarDisparo(int& x, int& y);//cambia el valor de la celda.

};

