#include "HardBOT.h"

HardBOT::HardBOT() {

	this->name = "Testing";
	

	///Pone los barcos en piezas
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

	for (int i = 0; i < 5; i++) {
		barcosEnemigos.push_back(piezas[i]);
	}


}


bool HardBOT::isValidPosition(int x, int y, Barco& ship) {
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
			isvalidPlacement = (heatMap[i][j] != -1);//Y checkea que no haya otro barco.
		}
	}
	else {
		isvalidX = (0 <= x && x - 1 + ship.getSize() < 10);
		isvalidY = (0 <= y && y < 10);

		isvalidPlacement = isvalidX && isvalidY;

		for (i = x; i < (x + ship.getSize()) && isvalidPlacement; i++) {
			isvalidPlacement = (heatMap[i][j] != -1);
		}
	}

	return isvalidPlacement;

}

bool HardBOT::placeShips(int& x, int& y) {
	srand(time(0)); //setea seed para el random
	for (static int i = 0; i < 5; i++) {
		do {
			x = rand() % 10;
			y = rand() % 10; //pone coordenadas random hasta que encuentre una que funcione
			if (rand() % 2)
				piezas[i].setOrientation();

		} while (!board.insertShip(x, y, piezas[i]));
	}

	return 1;
}


void HardBOT::funcionProbabilidad() {//Recorrido que hace todos los turnos la ia para determinar cual es el lugar mas optimo para disparar

	for (Barco b : barcosEnemigos) {//todos los barcos vivos que tiene el enemigo.
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (isValidPosition(i, j, b)) {
					agregaEnHeatMap(i, j, b);
				}
			}
		}
		b.setOrientation(); //cambia la orientacion del barco y repite el mismo proceso

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (isValidPosition(i, j, b)) {
					agregaEnHeatMap(i, j, b);
				}
			}
		}
	
	}

}

void HardBOT::agregaEnHeatMap(int x, int y, Barco& ship) {// "inserta" la iteracion en heatmap
	int i = x, j = y;
	bool vertical = ship.getOrientation();
	
	if (vertical) {
		for (j; j < (y + ship.getSize()); j++)
		{
			heatMap[i][j] += 1;
		}
	}
	else {
		for (i; i < (x + ship.getSize()); i++) {
			heatMap[i][j] += 1;
		}
	}

	
}


Barco* HardBOT::disparar(int& x, int& y, Mapa& Mapa_enemigo) {

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