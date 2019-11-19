#include "HumanPlayer.h"


void HumanPlayer::pHumanPlayer(const std::string& name) {
	this->name = name;

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

 bool HumanPlayer::placeShips(int& x, int& y, int i) {

	 bool ace;

	 if (MAPA.insertShip(x, y, piezas[i]) && i < 5)
	 {
		   std::cout << "Player " + name + " inserto el barco -> " + piezas[i].name << std::endl;
		   std::cout << "Se coloco en mapa el Barco: " << piezas[i].name
			 << "\n tamaño: " << piezas[i].getSize() << "\n"
			 << "------------------------------------------" << std::endl;
		 ace = true;
	 }
	 else {
		 ace = false;
	 }

	 return ace;
 }


std::string HumanPlayer::disparar(int& x, int& y,Mapa& Mapa_enemigo) {
	
	std::string disparo;
	
	if(Mapa_enemigo.RegistrarDisparo(x, y))
	{
		disparo = "Disparo en X["+ std::to_string(x) +"]"+"Y["+std::to_string(y)+"]"; /// harcodeo duro e inesperado
	}
	

	return disparo;
}