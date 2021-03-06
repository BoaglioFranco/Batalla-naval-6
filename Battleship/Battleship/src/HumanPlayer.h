#pragma once
#include "Player.h"
#include <fstream>
#include <iostream>
#include "Mapa.h"

class HumanPlayer :
	public Player
{
public:
	HumanPlayer(); ///const std::string& name
	HumanPlayer(const std::string& name);
	Barco * disparar(int& x, int& y,Mapa& Mapa_enemigo) override;
	bool placeShips(int& x, int& y) override;
	std::string name;
	//Mapa MAPA; // herencia, pelotudo
private:
	
	 /// Mapa del jugador
};
