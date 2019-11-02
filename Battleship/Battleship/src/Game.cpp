#include "Game.h"

Game::Game()
{
	sAppName = ".::-Battleship-::."; /// Doy un nombre para mi app :).
}

bool Game::OnUserCreate() 
{
	/// Cargo la direecion de mis sprites.
	isoPng = new olc::Sprite("assets/ejem.png");

	/// Doy el tamaño de mi mapa al arreglo.
	pWorld = new int[vWorldSize.x * vWorldSize.y]{ 0 }; 
	pWarWorld = new int[vWorldWarSize.x * vWorldWarSize.y]{ 0 };
   
	/// Un for para ir cambiando de eventos.
	for (int i = 0; i < 10; i++)
		listEvents.push_back("");


	return true;
}

bool Game::OnUserUpdate(float FpsTime)
{
	// Pantalla completa en blanco.
	Clear(olc::WHITE);
	// Creo unas "Cordenadas" de mouse.
	olc::vi2d vMouse = { GetMouseX(), GetMouseY() };
	// Creo un array 2D que va referenciar a una "celda" en mi mapa.
	olc::vi2d vCell = { vMouse.x / isoTileSize.x, vMouse.y / isoTileSize.y };
	
	// Creo un offset de las celdas para que mi mouse pueda seleccionar correctamente cada celda
	// porque las casillas con 4 celdas no son reconocidas por el mouse ya que es un mapa isometrico.
	olc::vi2d vOffset = { vMouse.x % isoTileSize.x, vMouse.y % isoTileSize.y };
	
	// Para solucionar este problema hago que todas las cuadriculas en mi mapa tengan una textura default con 4 colores
	// esto va a hacer que cada ves que mi mouse reconozca uno de esos colores pueda definir un limite a mi cuadraro celecionado y asi
	// poder seleccionar cualquier cuadrado en el mapa
	olc::Pixel col = isoPng->GetPixel(3 * isoTileSize.x + vOffset.x, vOffset.y);

	/// Magia ╰( ͡° ͜ʖ ͡° )つ──☆*:・ﾟ
	/// Mentira fran despues comento bien lo que hace
	/// Basicamente Crea crea un array 2d de donde estas "seleccionadndo" en el mapa
	olc::vi2d vSelected =
	{
		(vCell.y - vWorldOrigen.y) + (vCell.x - vWorldOrigen.x),
		(vCell.y - vWorldOrigen.y) - (vCell.x - vWorldOrigen.x)
	};
	
	/// ╰( ͡° ͜ʖ ͡° )つ──☆*:・ﾟ X 2
	olc::vi2d vSelected2 =
	{
		(vCell.y - vWarOrigen.y) + (vCell.x - vWarOrigen.x),
		(vCell.y - vWarOrigen.y) - (vCell.x - vWarOrigen.x)
	};

	/// Donde coloques el cursor dibuja el sprite adyasente ( ͡° ͜ʖ ͡° )
	if (col == olc::RED) vSelected += {-1, +0};
	if (col == olc::BLUE) vSelected += {+0, -1};
	if (col == olc::GREEN) vSelected += {+0, +1};
	if (col == olc::YELLOW) vSelected += {+1, +0};

	/// Lo mismo pero para el mapa 2 ( ͡° ͜ʖ ͡° )
	if (col == olc::RED) vSelected2 += {-1, +0};
	if (col == olc::BLUE) vSelected2 += {+0, -1};
	if (col == olc::GREEN) vSelected2 += {+0, +1};
	if (col == olc::YELLOW) vSelected2 += {+1, +0};
	
	
	return true;
}

