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
	/*
	--------------------------------------------------------------------------------------------
	Bot Intermedio. Presenta dos modos: Busqueda y Caza
	En el modo busqueda divide al mapa como si fuera un tablero de ajedrez, y solo dispara en las casillas "Blancas" o "Negras"
	Una vez que encuentra a un Barco, cambia a modo caza, en donde va a disparar a todas las casillas de alrededor de la
	que golpeo. Si consigue otro hit, repite el proceso.
	--------------------------------------------------------------------------------------------
	*/
private:
	bool isSearching;
	//Caza
	Lista<_stCoordenadasMediumB> CoordenadasSospechosas;
	void agregaSospechoso(int x, int y, Mapa& Mapa_enemigo);
	void eligeSospechoso(int& x, int& y);
	//
public:
	MediumBot();
	Barco* disparar(int& x, int& y, Mapa& Mapa_enemigo) override;
	bool placeShips(int& x, int& y) override;
};

