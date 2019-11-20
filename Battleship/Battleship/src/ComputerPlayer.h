#pragma once
#include "Player.h"
#include <stdlib.h>
#include <time.h> 


class ComputerPlayer :
	public Player
{
private:
	int heatMap[10][10];
	bool isHunting;

	bool isValidPosition(int x, int y, Barco& ship);

public:
	ComputerPlayer();
	bool placeShips(int& x, int& y) override; //los parametros no cumplen mucha funcion aca. Don't look at me i'm not the one who makes the design choices. 
	Barco * disparar(int& x, int& y, Mapa& Mapa_enemigo) override; // habiamos dicho q ibamos a usar un sistema de conversion de matriz a array pero bueno . Tampoco se por que poronga esto devuelve una string ni como se supone que eso nos de algun tipo de informacion relevante. No se si se dan cuenta que si cambian las cosas en la interfaz me obligan a cambiarlas a mi aca tambien pero bueno-
	bool revisarFlota();
		
};

