#include "HardBOT.h"

HardBOT::HardBOT() {

	this->name = "HardBot";
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

	for (int i = 0; i < 5; i++) {
		barcosEnemigos.push_back(piezas[i]);
	}


}

bool HardBOT::placeShips(int& x, int& y) {//coloca todos los barcos de la ia al comenzar la partida.
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

Barco* HardBOT::disparar(int& x, int& y, Mapa& Mapa_enemigo) {//Accion de disparar
	srand(time(0));

	if (isSearching) {//La IA realiza dos algoritmos distintos dependiendo de si encontro al barco o no

		funcionProbabilidad();//Determina donde es mas probable que haya un barco y elige esa casilla
		eligePos(x, y);
	}
	else {
		eligeSospechoso(x, y); //elige una casilla del vector de coordenadas sospechosas
	}


	Barco* barcoDisparado = nullptr;
	if (Mapa_enemigo.RegistrarDisparo(x, y))//efectua el disparo
	{
		std::cout << x << " " << y << std::endl;
		resetearHeatMap(); //modifica los valores necesarios
		setShot(x, y);     //en heatmap.
		barcoDisparado = Mapa_enemigo.grid[x][y].miembroDe;
		if (barcoDisparado) {
			if (barcoDisparado->hundido()) {
				remueveDeBarcosEnemigos(*barcoDisparado);//si se hundio el barco lo saca del vector de barcos buscados
				BorraHundidoDeSospechosas(*barcoDisparado);
			}
			else {
				agregaSospechosos(x - 1, y, *barcoDisparado);
				agregaSospechosos(x + 1, y, *barcoDisparado); //Inserta las casillas de alrededor
				agregaSospechosos(x, y - 1, *barcoDisparado); //de la disparada al vector de 
				agregaSospechosos(x, y + 1, *barcoDisparado); //casillas sospechosas
			}
		}
	}

	this->isSearching = (CoordenadasSospechosas.size() < 1);//si las coordenadas estan vacias se pone en modo busqueda, y visceversa
	return barcoDisparado;
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



void HardBOT::funcionProbabilidad() {//Recorrido que hace todos los turnos la ia para determinar cual es el lugar mas optimo para disparar

	for (Barco& b : barcosEnemigos) {//todos los barcos vivos que tiene el enemigo.
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


void HardBOT::resetearHeatMap() {//resetea el mapa cada turno.
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (heatMap[i][j] != -1) //-1 indica si ya fue disparada la casilla
				heatMap[i][j] = 0;
		}
	}


}

//Hola gustavo si estas leyendo esto gracias por acompañarnos todo el año 
//Y tenes que decirnos cual fue la parte del codigo que mas te gusto.

void HardBOT::setShot(int x, int y) {//indica que la casilla del heatmap fue disparada para que no se modifique nuevamente
	heatMap[x][y] = -1;

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

void HardBOT::eligePos(int& x, int& y) {//Elige la posicion donde conviene disparar en modo busqueda
	int highest = 0;
	int hiY, hiX;
	srand(time(0)); 
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (heatMap[i][j] > highest || (heatMap[i][j]== highest && (rand() % 2))  ){ //si los valores son iguales es random si lo toma o no, para hacer la ia menos predecible
				highest = heatMap[i][j];
				hiX = i;
				hiY = j;
			}
		}
	}
	x = hiX;
	y = hiY;
}




/*
 int HardBOT::matrixToInt(int x, int y) {
	 return (x + (y * 10));
 }

 void HardBOT::intToMatrix(int& x, int& y, int num) {//Pasa de int a coordenada para disparar
	 x = num % 10;
	 y = num / 10;
 }
 */
 void HardBOT::remueveDeBarcosEnemigos(Barco& hundido) {//Borra el barco que fue hundido de los barcos buscados
	 int elementos = barcosEnemigos.size();
	 for (int i = 0; i< elementos; i++) {
		 if (hundido.name == barcosEnemigos[i].name)
			 barcosEnemigos.erase(barcosEnemigos.begin() + i); //hola
	 }
 }

 void HardBOT::agregaSospechosos(int x, int y, Barco& provieneDe) {//agrega una casilla al vector de sospechosos
	 bool posValida = (-1 < y && y < 10) && (-1 < x && x < 10);// se fija que este dentro de la matriz
	 if (posValida && heatMap[x][y] != -1) {//si la pos es valida y la casilla no fue disparada
		 bool found = false;

		 int elementos = CoordenadasSospechosas.size();
		 for (int i = 0; i < elementos; i++) {
			 if (CoordenadasSospechosas[i].x == x && CoordenadasSospechosas[i].y == y)
				 found = true;
		 }
		 if (!found) {
			 _stCoordenadasHardB aux;
			 aux.x = x;
			 aux.y = y;
			 aux.provenienteDe = &provieneDe;
			 CoordenadasSospechosas.push_back(aux);//Si la casilla no se encuentra ya en la lista de espera la agrega.
		 }
	 }


 }

 void HardBOT::eligeSospechoso(int& x, int& y) {
	 _stCoordenadasHardB aux = CoordenadasSospechosas.back();
	 CoordenadasSospechosas.pop_back();
	 x = aux.x;
	 y = aux.y;
 }

 void HardBOT::BorraHundidoDeSospechosas(Barco& pHundido) {
	 int elementos = CoordenadasSospechosas.size();
	 int i = 0;
	 while(i < elementos) {
		 if (pHundido.name == CoordenadasSospechosas[i].provenienteDe->name) {
			 CoordenadasSospechosas.erase(CoordenadasSospechosas.begin() + i);
		 }
		 else{
			 i++;
		 }
		 elementos = CoordenadasSospechosas.size();
	 }
 }