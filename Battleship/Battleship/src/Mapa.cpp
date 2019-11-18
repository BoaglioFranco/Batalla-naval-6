#include "Mapa.h"

void Mapa::mostrarMapa()//es para ver si funciona bien la funcion insertar barco
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "\n\n\n";
		for (int j = 0; j < 10; j++)
		{

			//Sleep(75);
			std::cout << "\t";
			std::cout << grid[j][i].dato;//despues lo podemos modificar, pero asi el mapa nos queda acorde a como nos lo imaginamos
		}							//sino queda de costado y es medio confuso mirarlo
	}
}


bool Mapa::validPlacement(int x, int y, Barco& Ship)
{
	bool isvalidPlacement = false;
	bool isvalidX;
	bool isvalidY;
	bool vertical = Ship.getOrientation();

	int i = x, j = y;
	///Existen 2 orientaciones vertial (1) y horizontal(0)

	if (vertical) {
		isvalidX = (0 <= x && x < 10);//evalua que la coordenada X este dentro del rango.
		isvalidY = (0 <= y && (y - 1 + Ship.getSize()) < 10);//evalua que el largo del barco desde el punto de origen este en rango

		isvalidPlacement = isvalidX && isvalidY;

		for (j = y; j < (y + Ship.getSize()) && isvalidPlacement; j++) {//Evalua las casillas donde se encontraria el barco
			isvalidPlacement = (grid[i][j].dato == 0);//Y checkea que no haya otro barco.
		}
	}
	else {
		isvalidX = (0 <= x && x - 1 + Ship.getSize() < 10);
		isvalidY = (0 <= y && y < 10);

		isvalidPlacement = isvalidX && isvalidY;

		for (i = x; i < (x + Ship.getSize()) && isvalidPlacement; i++) {
			isvalidPlacement = (grid[i][j].dato == 0);
		}
	}

	return isvalidPlacement;
}

/// Esta funcion ahora es booleana
bool Mapa::insertShip(int x, int y, Barco& ship)
{
	int i = x, j = y;
	bool valid = validPlacement(x, y, ship);
	bool vertical = ship.getOrientation();

	if (valid) { //Inserta el barco en las casillas y guarda la direccion de memoria del barco en ellas
		if (vertical) {
			for (j; j < (y + ship.getSize()); j++)
			{
				grid[i][j].dato = 2;
				grid[i][j].setMiembroDe(ship);
			}
		}
		else {
			for (i; i < (x + ship.getSize()); i++) {
				grid[i][j].dato = 2;
				grid[i][j].setMiembroDe(ship);
			}
		}

	}

	return valid;
}

Barco& Mapa::sendReference(Barco& barquito) {
	if(barquito.Hundido)
		return barquito;
}