#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer() {
	this->name = "Baby Face";


	std::ifstream archivoBarcos; //lee los barcos desde el archivo y los escribe en el array.
	archivoBarcos.open("barcos.txt");
	if (archivoBarcos.fail()) {
		std::cerr << "Error en la lectura del archivo" << std::endl;
		exit(1);
	}
	else {
		int sizeBarco;
		for (int i = 0; i < 5; i++) {
			archivoBarcos >> piezas[i].name >> sizeBarco;
			piezas[i].setSize(sizeBarco);
		}
	}
	archivoBarcos.close();

}

bool ComputerPlayer::isValidPosition(int x, int y, Barco& ship) {
	bool isvalidPlacement = false;
	bool isvalidX;
	bool isvalidY;
	bool vertical = ship.getOrientation();

	int i = x, j = y;
	///Existen 2 orientaciones vertial (1) y horizontal(0)

	if (vertical) {
		isvalidX = (0 <= x && x < 10);//evalua que la coordenada X este dentro del rango.
		isvalidY = (0 <= y && (y - 1 + ship.getSize()) < 10);//evalua que el largo del barco desde el punto de origen este en rango

		isvalidPlacement = isvalidX && isvalidY;

		for (j = y; j < (y + ship.getSize()) && isvalidPlacement; j++) {//Evalua las casillas donde se encontraria el barco
			isvalidPlacement = (heatMap[i][j] == 0);//Y checkea que no haya otro barco.
		}
	}
	else {
		isvalidX = (0 <= x && x - 1 + ship.getSize() < 10);
		isvalidY = (0 <= y && y < 10);

		isvalidPlacement = isvalidX && isvalidY;

		for (i = x; i < (x + ship.getSize()) && isvalidPlacement; i++) {
			isvalidPlacement = (heatMap[i][j] == 0);
		}
	}

	return isvalidPlacement;

}

bool ComputerPlayer::placeShips(int& x, int& y) {
	srand(time(0)); //setea seed para el random
	for (static int i = 0; i < 5; i++) {
		do {
			x = rand() % 10;
			y = rand() % 10; //pone coordenadas random hasta que encuentre una que funcione
			if(rand() % 2)
				piezas[i].setOrientation();
			
		} while (!board.insertShip(x, y, piezas[i]));
	}

	return 1;
}

Barco * ComputerPlayer::disparar(int& x, int& y, Mapa& Mapa_enemigo) {

	srand(time(0));
	do {
		x = rand() % 10;
		y = rand() % 10; //Dispara random
	} while(Mapa_enemigo.grid[x][y].isShot);

	Barco* barcoDisparado = nullptr;
	if (Mapa_enemigo.RegistrarDisparo(x, y))
	{
		barcoDisparado = Mapa_enemigo.grid[x][y].miembroDe;
	}


	return barcoDisparado;
}

bool ComputerPlayer::revisarFlota()
{
	int i = 0;
	int flag = 0;

	while (i < 5 && flag == 0)
	{
		if (piezas[i].hundido())
			i++;
		else
			flag = 1;
	}

	if (flag == 0)
		this->TieneFlota = false;

	return this->TieneFlota;
}