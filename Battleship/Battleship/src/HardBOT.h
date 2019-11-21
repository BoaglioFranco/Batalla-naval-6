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
	bool isHunting;
	std::vector<Barco> barcosEnemigos; //almacena los barcos enemigos que siguen vivos
	void funcionProbabilidad();
public:
	HardBOT();
	Barco* disparar(int& x, int& y, Mapa& Mapa_enemigo) override;
	bool placeShips(int& x, int& y) override;
};

