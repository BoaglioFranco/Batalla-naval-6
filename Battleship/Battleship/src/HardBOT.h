#pragma once
#include "Player.h"
#include <stdlib.h>
#include <time.h> 
#include <vector>
class HardBOT :
	public Player
{
private:
	int heatMap[10][10];
	bool isValidPosition(int x, int y, Barco& ship);
	void agregaEnHeatMap(int x, int y, Barco& ship);
	bool isSearching;
	std::vector<Barco> barcosEnemigos; //almacena los barcos enemigos que siguen vivos
	void remueveDeBarcosEnemigos(Barco& b);
	void funcionProbabilidad();
	void eligePos(int& x, int& y);
	void resetearHeatMap();
	void setShot(int x, int y);

	std::vector<int> CoordenadasSospechosas;
	int matrixToInt(int x, int y);
	void intToMatrix(int& x, int& y, int num);
	void agregaSospechosos(int x, int y);
public:
	HardBOT();
	Barco* disparar(int& x, int& y, Mapa& Mapa_enemigo) override;
	bool placeShips(int& x, int& y) override;
	void printPedorro();
};

