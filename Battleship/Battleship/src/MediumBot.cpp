#include "MediumBot.h"

MediumBot::MediumBot() {
	this->name = "MediumBot";
	this->isSearching = true;
	ite_Barcos = 0;

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
}


bool MediumBot::placeShips(int& x, int& y) {//coloca todos los barcos de la ia al comenzar la partida.
	srand(time(0)); //setea seed para el random
	for (ite_Barcos = 0; ite_Barcos < 5; ite_Barcos++) {//la int estatica previene que el metodo sea llamado multiples veces
		do {
			x = rand() % 10;
			y = rand() % 10; //pone coordenadas random hasta que encuentre una que funcione
			if (rand() % 2)
				piezas[ite_Barcos].setOrientation();

		} while (!board.insertShip(x, y, piezas[ite_Barcos]));
	}

	return 1;
}

Barco* MediumBot::disparar(int& x, int& y, Mapa& Mapa_enemigo) {
	srand(time(0));
	if (isSearching) {
		do {
			x = rand() % 10;
			y = rand() % 10; //Elige un x e y random.
		} while ( (x % 2 != 0) == (y % 2 !=0) || Mapa_enemigo.grid[x][y].isShot);//repite esto hasta que la casilla seleccionada no este disparada y sea un numero par.
	}
	else {
		eligeSospechoso(x, y);//elige un item de la lista casillas sospechosas
	}


	Barco* barcoDisparado = nullptr;
	if (Mapa_enemigo.RegistrarDisparo(x, y))//efectua el disparo
	{
		barcoDisparado = Mapa_enemigo.grid[x][y].miembroDe;
		if (barcoDisparado && !barcoDisparado->hundido()) {
				agregaSospechoso(x - 1, y, Mapa_enemigo);
				agregaSospechoso(x + 1, y, Mapa_enemigo); //Agrega todas las casillas lindantes al hit
				agregaSospechoso(x, y - 1, Mapa_enemigo); //a la lista de casillas para disparar
				agregaSospechoso(x, y + 1, Mapa_enemigo);
		}
	}

	this->isSearching = CoordenadasSospechosas.listaVacia();//si las coordenadas estan vacias se pone en modo busqueda, y visceversa
	return barcoDisparado;
}


void MediumBot::eligeSospechoso(int& x, int& y) {// baja el ultimo elemento de casillas sospechosas para disparar alli.
	_stCoordenadasMediumB aux = CoordenadasSospechosas.extraerUltimo();
	x = aux.x;
	y = aux.y;
}


void MediumBot::agregaSospechoso(int x, int y, Mapa& Mapa_enemigo) {//agrega una casilla a la lista de sospechosos
	bool posValida = (-1 < y && y < 10) && (-1 < x && x < 10);// se fija que este dentro de la matriz
	if (posValida && !Mapa_enemigo.grid[x][y].isShot) {//si la pos es valida y la casilla no fue disparada
		bool found = false;

		_stCoordenadasMediumB aux;
		CoordenadasSospechosas.inicIterator();
		while(CoordenadasSospechosas.iterator){ // Perdon gustavo, no tuvimos tiempo para hacer un operator overload para las listas :(
			aux = CoordenadasSospechosas.iterator->Get_dato();
			if (aux.x == x && aux.y == y)
				found = true;
			CoordenadasSospechosas.iterator = CoordenadasSospechosas.iterator->Get_siguiente();

		}
		if (!found) {
			_stCoordenadasMediumB agregado;
			agregado.x = x;
			agregado.y = y;
			CoordenadasSospechosas.Agregar_Final(agregado);//Si la casilla no se encuentra ya en la lista de espera la agrega.
		}
	}


}