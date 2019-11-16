#include "HumanPlayer.h"


HumanPlayer::HumanPlayer(const std::string& name) {
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

 void HumanPlayer::placeShips(int a int b) {
	//TODO: una version de este metodo que no sea pedorra.
	pleisyip(int pito, int culo)

}


void HumanPlayer::disparar() {};