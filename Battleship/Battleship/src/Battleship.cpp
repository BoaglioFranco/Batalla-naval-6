#include <iostream>
#include "Game.h"

int main()
{
	Game demo;

	if (demo.Construct(900, 300, 2, 2))
		demo.Start();

	return EXIT_SUCCESS;
}
