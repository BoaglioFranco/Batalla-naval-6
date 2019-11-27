#pragma once
#include "Player.h"
#include <stdlib.h>
#include <time.h> 
#include <vector>

typedef struct _stCoordenadasHardB {
	int x;
	int y;
	Barco* provenienteDe;

	
};

class HardBOT :
	public Player
{
private:

	/*
	--------------------------------------------------------------------------------------------
	Bot complejo y eficientede los 3. Posee 2 modos, Busqueda y caza. 
	En modo Busqueda, usa una func. de probabilidad para determinar estadisticamente donde es mas probable que haya barcos. 
	Presenta un modo caza para cuando ya encontro un barco, que es similar pero levemente mas eficiente
	con respecto al que posee Medium Bot.
	--------------------------------------------------------------------------------------------
	*/
	bool isSearching;
	//busqueda
	int heatMap[10][10];
	bool isValidPosition(int x, int y, Barco& ship);
	void agregaEnHeatMap(int x, int y, Barco& ship);
	std::vector<Barco> barcosEnemigos; //almacena los barcos enemigos que siguen vivos
	void remueveDeBarcosEnemigos(Barco& b);
	void funcionProbabilidad();
	void eligePos(int& x, int& y);
	void resetearHeatMap();
	void setShot(int x, int y);
	//Caza
	std::vector<_stCoordenadasHardB> CoordenadasSospechosas;
	void eligeSospechoso(int& x, int& y);
	void agregaSospechosos(int x, int y, Barco& provenienteDe);
	void BorraHundidoDeSospechosas(Barco& pHundido);
	//
public:
	HardBOT();
	Barco* disparar(int& x, int& y, Mapa& Mapa_enemigo) override;
	bool placeShips(int& x, int& y) override;
};

