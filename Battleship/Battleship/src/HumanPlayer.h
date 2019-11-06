#pragma once
#include "Player.h"
#include <fstream>
class HumanPlayer :
	public Player
{
public:
	HumanPlayer(const std::string& name);
	void disparar() override;
	void placeShips() override;

};
