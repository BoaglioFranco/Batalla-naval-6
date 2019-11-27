#include "HumanPlayer.h"

HumanPlayer::HumanPlayer() {

	 std::cout << "Ingrese el nombre de jugador\n";
	 std::getline(std::cin >> std::ws, name); 
	 this->name = name;
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

HumanPlayer::HumanPlayer(const std::string& name) {

	 this->name = name;
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

 bool HumanPlayer::placeShips(int& x, int& y) {
	 bool ace;

	 if (board.insertShip(x, y, piezas[ite_Barcos]) && ite_Barcos < 5)
	 {
		   std::cout << "Player " + name + " inserto el barco -> " + piezas[ite_Barcos].name << std::endl;
		   std::cout << "Se coloco en mapa el Barco: " << piezas[ite_Barcos].name
			 << "\n tamaño: " << piezas[ite_Barcos].getSize() << "\n"
			 << "------------------------------------------\n" << 
			    "valor I "<< ite_Barcos <<std::endl;

		 ace = true;
		 ite_Barcos++;
	 }
	 else {
		 ace = false;
	 }

	 return ace;
 }


Barco * HumanPlayer::disparar(int& x, int& y,Mapa& Mapa_enemigo) {
	
	Barco * barquito = nullptr;

	if(Mapa_enemigo.RegistrarDisparo(x, y))
	{
		barquito = Mapa_enemigo.grid[x][y].miembroDe;
	}
	
	return barquito;
}


