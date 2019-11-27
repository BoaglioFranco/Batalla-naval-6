#include <iostream>
#include <string>
#include "Game.h"


int main(int argc, char * arg[])
{
	int difficulty = 1;
	std::cout << "Bienvenido a .:Battlleship:. UTN" << std::endl;
	do {
		std::cout << "Selecciona la dificultad !!! \n" <<
			"( 1 ) Bot Easy.\n" <<
		    "( 2 ) Bot Medium.\n" <<
			"( 3 ) Bot Hard.    " << std::endl;
		std::cin >> difficulty;

		if (difficulty > 3 || difficulty < 1)
		{
			system("cls");
			std::cout << "Opcion invalida...\n\n";
		}

	} while (difficulty < 1 || difficulty > 3);

	Game * demo = nullptr;
	demo = new Game(difficulty);
	
	if (demo->Construct(900, 300, 2, 2, true))
		demo->Start();
	std::cout << "\n\n" << std::endl;
	std::cout << "\t\t----------------------------------" << std::endl;
	std::cout << "\t\t.-.-.Muchas gracias Por Jugar.-.-." << std::endl;
	std::cout << "\t\t----------------------------------\n\n\n" << std::endl;

	return EXIT_SUCCESS;
}
