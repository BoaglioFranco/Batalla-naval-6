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
	void disparar() override;
	bool placeShips(int& x, int& y) override;
	Mapa A;
private:
	 /// Mapa del jugador
};
