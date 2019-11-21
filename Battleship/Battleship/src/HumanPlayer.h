#pragma once
#include "Player.h"
#include <fstream>
#include "Mapa.h"

class HumanPlayer :
	public Player
{
public:
	HumanPlayer(const std::string& name);
	Barco * disparar(int& x, int& y,Mapa& Mapa_enemigo) override;
	bool placeShips(int& x, int& y) override;
	//Mapa MAPA; // herencia, pelotudo
private:
	 /// Mapa del jugador
};
