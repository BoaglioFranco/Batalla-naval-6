#pragma once
#include "Player.h"
#include <fstream>
#include "Mapa.h"
class HumanPlayer :
	public Player
{
public:
	HumanPlayer(const std::string& name);
	void disparar() override;
	static void placeShips() override;

};
