#include <iostream>
#include "Game.h"

int main()
{

	Game * demo = nullptr;
	demo = new Game;

	if (demo->Construct(900, 300, 2, 2))
		demo->Start();
	
	std::cout << "\t\t----------------------------------" << std::endl;
	std::cout << "\t\t.-.-.Muchas gracias Por Jugar.-.-." << std::endl;
	std::cout << "\t\t----------------------------------\n\n\n" << std::endl;

	return EXIT_SUCCESS;
}
