#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <string>
#include <iostream>
#include "Mapa.h"


const int _WordX = 10;
const int _WordY = 10;

/// La clase juego se encarga de usar todos los recursos graficos de OLC::PixelGameEngine
class Game : public olc::PixelGameEngine 
{
private:

	/// olc::vi2d Son Vectores de 2 dimensiones con su x , y.
	olc::vi2d vWorldSize = { _WordX , _WordY };/// MAPA principal ... jugador humano.
	olc::vi2d vWorldWarSize = { _WordX , _WordY };/// MAPA segundario ... para jugador maquina por ahora...

	olc::vi2d isoTileSize = { 40 , 20 }; /// Tamaño en pixeles de cada una de mis Tiles isometricos.

	olc::vi2d vWorldOrigen = { 5 , 1 };/// Donde quiero que comience mi mapa en pantalla.
	olc::vi2d vWarOrigen = { 30 , 30 };

	/// Puntero que va a contener mis sprite a dibujar en consola.
	olc::Sprite* isoPng = nullptr;
	/// Supongo que voy a tener uno para cada barco y un contador para ir diferenciandolos.

	/// Puntero para contener mi matriz para crear un mundo 2D en un arreglo.
	int* pWorld = nullptr;
	int* pWarWorld = nullptr;

	/// Un vector lista para contener eventos para dar informacion en pantalla.
	std::list<std::string> listEvents;

	MAPA map;
	Barco GeneralBelgrano;

public:

	Game()
	{
		sAppName = "Game";
	}
	
		
		
	bool OnUserCreate() override
	{
		/// Cargo la direecion de mis sprites.
		isoPng = new olc::Sprite("assets/isodemo.png");

		/// Doy el tamaño de mi mapa al arreglo.
		pWorld = new int[vWorldSize.x * vWorldSize.y]{ 0 };
		pWarWorld = new int[vWorldWarSize.x * vWorldWarSize.y]{ 0 };
		
		GeneralBelgrano.setSize(3);
		/// Un for para ir cambiando de eventos.
		for (int i = 0; i < 10; i++)
			listEvents.push_back("");

		
		return true;
	}
	

	bool OnUserUpdate(float FpsTime) override 
	{
		
		// Pantalla completa en blanco.
		olc::PixelGameEngine::Clear(olc::WHITE);
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

		if (GetMouse(0).bPressed)
		{
			if (map.valido(vSelected.x, vWorldSize.x, vSelected.y, vWorldSize.y,pWorld,GeneralBelgrano))//map.ValidPlacement(vWorldSize.x, vWorldSize.y, D_UP, GeneralBelgrano, pWorld)
			{                                                                 // map.valido(vSelected.x,vWorldSize.x,vSelected.y,vWorldSize.y)
				++pWorld[vSelected.y * vWorldSize.x + vSelected.x] %= 2;
				++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 1] %= 2;
			}
				
		}
		
		// Handle mouse click to toggle if a tile is visible or not
		//if (GetMouse(0).bPressed)
		//{
		//	// Guard array boundary
		//	if (vSelected.x >= 0 && vSelected.x < vWorldSize.x && vSelected.y >= 0 && vSelected.y < vWorldSize.y)
		//	{
		//		/// Sumandole 1 creo una pieza doble en vertical
		//		++pWorld[vSelected.y * vWorldSize.x + vSelected.x] %= 2;
		//		++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) - 1] %= 2;
		//		//++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) * 2] %= 6;
		//	}
		//}
		
		
		if (GetMouse(0).bPressed)
		{
			if (vSelected2.x >= 0 && vSelected2.x < vWorldWarSize.x && vSelected2.y >= 0 && vSelected2.y < vWorldWarSize.y)
			{
				++pWarWorld[vSelected2.y * vWorldWarSize.x + vSelected2.x] %= 2;
				++pWarWorld[(vSelected2.y * vWorldWarSize.x + vSelected2.x) + 1] %= 2;
			}
		}
		// Labmda function to convert "world" coordinate into screen space
		auto ToScreen = [&](int x, int y)
		{
			return olc::vi2d
			{
				(vWorldOrigen.x * isoTileSize.x) + (x - y) * (isoTileSize.x / 2),
				(vWorldOrigen.y * isoTileSize.y) + (x + y) * (isoTileSize.y / 2)
			};
		};

		auto ToScreen2 = [&](int x, int y)
		{
			return olc::vi2d
			{
				(vWarOrigen.x * isoTileSize.x) + (x - y) * (isoTileSize.x / 2),
				(vWarOrigen.y * isoTileSize.y) + (x + y) * (isoTileSize.y / 2)
			};
		};

		// Draw World - has binary transparancy so enable masking
		SetPixelMode(olc::Pixel::MASK);

		// (0,0) is at top, defined by vOrigin, so draw from top to bottom
		// to ensure tiles closest to camera are drawn last
		for (int y = 0; y < vWorldSize.y; y++)
		{
			for (int x = 0; x < vWorldSize.x; x++)
			{
				// Convert cell coordinate to world space
				olc::vi2d vWorld = ToScreen(x, y);

				switch (pWorld[y * vWorldSize.x + x])
				{
				case 0:
					// Invisble Tile                               1 - 0/3 BUG BUENARDO- 0     /// SACAR EL *2
					DrawPartialSprite(vWorld.x, vWorld.y, isoPng, 1 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
					break;
				case 1:
					// grass Visible Tile
					DrawPartialSprite(vWorld.x, vWorld.y, isoPng, 2 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				}
			}
		}

		for (int y = 0; y < vWorldWarSize.y; y++)
		{
			for (int x = 0; x < vWorldWarSize.x; x++)
			{
				olc::vi2d vWorld2 = ToScreen2(x, y);

				switch (pWarWorld[y * vWorldWarSize.x + x])
				{
				case 0:
					// Invisble Tile                               1 - 0/3 BUG BUENARDO- 0     /// SACAR EL *2
					DrawPartialSprite(vWorld2.x, vWorld2.y, isoPng, 1 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
					break;
				case 1:
					// grass Visible Tile
					DrawPartialSprite(vWorld2.x, vWorld2.y, isoPng, 2 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
					break;
				}

			}
		}
		//std::cout << vWorldSize.x << std::endl;
		//std::cout << vWorldSize.y << std::endl;


		//if (GetMouse(0).bPressed)
		//{
		//	std::cout <<"Vselected X = " <<vSelected.x << std::endl;
		//	std::cout <<"Vselected Y = " << vSelected.y << std::endl;
		//	//std::cout << "pWorld DATO EN MAPA = " << pWorld[vSelected.x + (vSelected.y*10)] << std::endl;
		//}

		if (GetKey(olc::Key::E).bHeld)
		{
			SetPixelMode(olc::Pixel::NORMAL);
			Clear(olc::WHITE);
			vWarOrigen = { 16, 1 };
		}


		if (GetKey(olc::Key::A).bPressed)
		{
			//vOrigin = { 5, 1 };      /// [vSelected.x + (vSelected.y * 10)]
			std::cout << "Vselected X = " << vSelected.x << std::endl;
			std::cout << "Vselected Y = " << vSelected.y << std::endl;
			std::cout << "pWorld DATO EN MAPA [A] = " << pWorld[vSelected.y * vWorldSize.x + vSelected.x] << std::endl;
		}

		if (GetKey(olc::Key::B).bPressed)
		{
			std::cout << "Vselected X = " << vSelected.x << std::endl;
			std::cout << "Vselected Y = " << vSelected.y << std::endl;
			std::cout << "WarWorld DATO EN MAPA [B] = " << pWarWorld[vSelected2.y * vWorldWarSize.x + vSelected2.x] << std::endl;
		}

		// Draw Selected Cell - Has varying alpha components
		SetPixelMode(olc::Pixel::ALPHA);

		// Convert selected cell coordinate to world space
		olc::vi2d vSelectedWorld = ToScreen(vSelected.x, vSelected.y);
		olc::vi2d vSelectedWorld2 = ToScreen2(vSelected2.x, vSelected2.y);

		// Draw "highlight" tile
		if (vMouse.x && vMouse.y != NULL) /// size del barquito y rotazion 
		{
			int tamaño = 2;
			switch (tamaño)
			{
			case 2: // horizontal
				DrawPartialSprite(vSelectedWorld.x, vSelectedWorld.y, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				DrawPartialSprite(vSelectedWorld.x + 20, vSelectedWorld.y + 10, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				break;
			default:
				break;
			}


			//X +20  ----- Y + 10 --- o --- X -20 Y -10 desde el centro   VERTICAL
			//DrawPartialSprite(vSelectedWorld.x + 20, vSelectedWorld.y + 10, sprIsom, 0 * vTileSize.x, 0, vTileSize.x, vTileSize.y);

			 // X - 20  ---- Y + 10 HORIZONTAL 
			//DrawPartialSprite(vSelectedWorld.x - 20, vSelectedWorld.y + 10, sprIsom, 0 * vTileSize.x, 0, vTileSize.x, vTileSize.y);

			//DrawPartialSprite(vSelectedWorld.x + 40, vSelectedWorld.y + 20, sprIsom, 0 * vTileSize.x, 0, vTileSize.x, vTileSize.y);
		}

		/*if (GetMouse(0).bPressed)
		{
			std::cout << "X = " << vSelectedWorld.x << std::endl;
			std::cout << "Y = " << vSelectedWorld.x << std::endl;
		}*/

		// Go back to normal drawing with no expected transparency
		SetPixelMode(olc::Pixel::NORMAL);

		// Draw Hovered Cell Boundary
		//DrawRect(vCell.x * vTileSize.x, vCell.y * vTileSize.y, vTileSize.x, vTileSize.y, olc::RED);

		// Draw Debug Info
		DrawString(4, 4, "Mouse   : " + std::to_string(vMouse.x) + ", " + std::to_string(vMouse.y), olc::BLACK);
		DrawString(4, 14, "Cell    : " + std::to_string(vCell.x) + ", " + std::to_string(vCell.y), olc::BLACK);

		if (vSelected.x >= 0 && vSelected.x < vWorldSize.x && vSelected.y >= 0 && vSelected.y < vWorldSize.y)
		{
			DrawString(4, 24, "Mapa[1] X: " + std::to_string(vSelected.x) + ",Y: " + std::to_string(vSelected.y), olc::BLACK);
			DrawString(10, 34, "FRANCO SE LA COME", olc::RED);

		}
		else if (vSelected2.x >= 0 && vSelected2.x < vWorldWarSize.x && vSelected2.y >= 0 && vSelected2.y < vWorldWarSize.y)
		{
			DrawString(4, 24, "Mapa[2] X: " + std::to_string(vSelected2.x) + ",Y: " + std::to_string(vSelected2.y), olc::BLACK);
			DrawString(10, 34, "MARTIN SE LA COME", olc::RED);
		}
		else {

			DrawString(4, 24, "Mapa [1]: Fuera del mapa ", olc::BLACK);
			DrawString(4, 34, "Mapa [2]: Fuera del mapa ", olc::BLACK);
		}
		/*
		DrawString(4, 24, "Selected  X: " + std::to_string(vSelected.x) + ",Y: " + std::to_string(vSelected.y), olc::BLACK);
		DrawString(4, 34, "Selected2 X: " + std::to_string(vSelected2.x) + ",Y: " + std::to_string(vSelected2.y), olc::BLACK);
		DrawString(10, 44, "FRANCO SE LA COME", olc::RED);*/

		auto AddEvent = [&](std::string s)
		{
			listEvents.push_back(s);
			listEvents.pop_front();
		};

		if (GetMouse(0).bPressed)	AddEvent("Hola");
		if (GetMouse(0).bReleased)	AddEvent("esto es un test");
		if (GetMouse(1).bPressed)	AddEvent("Q(-o-)__o___i_____Q(-o-)");
		if (GetMouse(1).bReleased)	AddEvent("dos chinos jugando ping pong");

		// Dibujo los textos por eventos
		int nLog = 0;
		for (auto& s : listEvents)
		{
			// 8 + 20  Separacion entre textos        /// los 3 * 16
			DrawString(400, nLog * 8 + 20, s, olc::Pixel(nLog * -16, nLog * -16, nLog * -16), 1);
			nLog++;
		}


		return true;
	}

	                                     
	
	void Exit(); /// Metodo para salir del juego pulsando una tecla.

};
