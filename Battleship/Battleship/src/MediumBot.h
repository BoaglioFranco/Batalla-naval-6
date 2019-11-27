#pragma once
#include "Player.h"
#include <stdlib.h>
#include <time.h>
#include "Lista.h"

typedef struct {
	int x;
	int y;
}_stCoordenadasMediumB;

class MediumBot :
	public Player
{
private:
	bool isSearching;

	Lista<_stCoordenadasMediumB> CoordenadasSospechosas;
	void agregaSospechoso(int x, int y, Mapa& Mapa_enemigo);
	void eligeSospechoso(int& x, int& y);
public:
	MediumBot();
	Barco* disparar(int& x, int& y, Mapa& Mapa_enemigo) override;
	bool placeShips(int& x, int& y) override;
};

