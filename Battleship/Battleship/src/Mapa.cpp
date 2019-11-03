#include "Mapa.h"

bool MAPA::valido(int SelecX, int WorldX, int SelecY, int WorldY, int *world ,Barco& Ship)
{	

	if (SelecX >= 0 && SelecX < WorldX && SelecY >= 0 && SelecY < WorldY)
	{
		for (int i = (SelecY * WorldX + SelecX); i < (SelecY * WorldX + SelecX) + Ship.getSize(); i++)
		{
			std::cout << "[ "<< i <<"] = "<< world[i] <<std::endl;
			if (world[i] == 1)
				return false;
			else
				return true;
		}
	}
		
}
bool MAPA::validPlacement(int x, int y, Dir orientacion, Barco& Ship)
{
	bool isvalidPlacement = false;
	bool isvalidX;
	bool isvalidY;
	
	int i = x, j = y;
	///Existen 4 condiciones para checkear debido a que si la orientacion del barco es diferente el desplazamiento dentro de la matriz no sera el mismo

	if (orientacion == 0) {
		isvalidX = (0 <= x && x < 10);//evalua que la coordenada X este dentro del rango.
		isvalidY = (0 <= (y + 1 - Ship.getSize()) && y < 10);//evalua que el largo del barco desde el punto de origen este en rango

		isvalidPlacement = isvalidX && isvalidY;

		for (j = y; j > (y - Ship.getSize()) && isvalidPlacement; j--) {//Evalua las casillas donde se encontraria el barco
			isvalidPlacement = (grid[i][j] == 0);				//Y checkea que no haya otro barco.
		}
	}
	else if (orientacion == 1) {
		isvalidX = (0 <= x && x - 1 + Ship.getSize() < 10);
		isvalidY = (0 <= y && y < 10);

		isvalidPlacement = isvalidX && isvalidY;

		for (i = x; i < (x + Ship.getSize()) && isvalidPlacement; i++) {
			isvalidPlacement = (grid[i][j] == 0);
		}
	}
	else if (orientacion == 2) {
		isvalidX = (0 <= x && x < 10);
		isvalidY = (0 <= y && (y - 1 + Ship.getSize()) < 10);

		isvalidPlacement = isvalidX && isvalidY;

		for (j = y; j < (y + Ship.getSize()) && isvalidPlacement; j++) {
			isvalidPlacement = (grid[i][j] == 0);
		}
	}
	else if (orientacion == 3) {
		isvalidX = (0 <= (x + 1 - Ship.getSize()) && x < 10);
		isvalidY = (0 <= y && y < 10);

		isvalidPlacement = isvalidX && isvalidY;

		for (i = x; i > (x - Ship.getSize()) && isvalidPlacement; i--) {
			isvalidPlacement = (grid[i][j] == 0);
		}
	}

	return isvalidPlacement;
}

