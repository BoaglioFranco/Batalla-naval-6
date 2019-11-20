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

 bool HumanPlayer::placeShips(int& x, int& y) {
	 static int i = 0;
	 bool ace;

	 if (board.insertShip(x, y, piezas[i]) && i < 5)
	 {
		   std::cout << "Player " + name + " inserto el barco -> " + piezas[i].name << std::endl;
		   std::cout << "Se coloco en mapa el Barco: " << piezas[i].name
			 << "\n tamaño: " << piezas[i].getSize() << "\n"
			 << "------------------------------------------" << std::endl;
		 ace = true;
		 i++;
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


bool HumanPlayer::revisarFlota()
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