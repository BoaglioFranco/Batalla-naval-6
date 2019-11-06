#include "Mapa.h"

bool MAPA::valido(int SelecX, int WorldX, int SelecY, int WorldY, int* world, Barco& Ship, int orientacion)
{
	bool ValidOU = true;
	int contadOU = 0;

	if (SelecX >= 0 && SelecX < WorldX && SelecY >= 0 && SelecY < WorldY)
	{


		return true;
		/*for (int i = SelecX; i < SelecX + Ship.getSize(); i++)
		{
			
			if (world[SelecY * WorldX + SelecX] == 1 || i >= 9)
			{
				return false;
			}else{
				world[(SelecY * WorldX + SelecX) + 1];
				contadOU++;
			}
			if (contadOU == Ship.getSize())
			{
				return true;
			}
		}*/
	}
	else return false;
}

