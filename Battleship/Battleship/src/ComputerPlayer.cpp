#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer() {
	this->name = "Higuain";
	ite_Barcos = 0;

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


bool ComputerPlayer::placeShips(int& x, int& y) {
	srand(time(0)); //setea seed para el random
	for (ite_Barcos = 0; ite_Barcos < 5; ite_Barcos++) {
		do {
			x = rand() % 10;
			y = rand() % 10; //pone coordenadas random hasta que encuentre una que funcione
			if (rand() % 2)
				piezas[ite_Barcos].setOrientation();

		} while (!board.insertShip(x, y, piezas[ite_Barcos]));
	}

	return 1;
}

Barco* ComputerPlayer::disparar(int& x, int& y, Mapa& Mapa_enemigo) {

	srand(time(0));
	do {
		x = rand() % 10;
		y = rand() % 10; //Dispara random
	} while (Mapa_enemigo.grid[x][y].isShot);

	Barco* barcoDisparado = nullptr;
	if (Mapa_enemigo.RegistrarDisparo(x, y))
	{
		barcoDisparado = Mapa_enemigo.grid[x][y].miembroDe;
	}


	return barcoDisparado;
}