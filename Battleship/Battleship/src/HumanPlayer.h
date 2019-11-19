#pragma once
#include "Player.h"
#include <fstream>
#include "Mapa.h"

class HumanPlayer :
	public Player
{
public:
	HumanPlayer() {};
	void pHumanPlayer(const std::string& name);
	std::string disparar(int& x, int& y,Mapa& Mapa_enemigo) override;
	bool placeShips(int& x, int& y, int i) override;
	bool revisarFlota();
	//Mapa MAPA; // herencia, pelotudo
private:
	 /// Mapa del jugador
};
