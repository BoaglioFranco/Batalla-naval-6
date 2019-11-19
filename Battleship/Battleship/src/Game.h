#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <string>
#include <iostream>
#include "HumanPlayer.h"


/// La clase juego se encarga de usar todos los recursos graficos de OLC::PixelGameEngine
class Game : public olc::PixelGameEngine
{
private:

	static const int _WordX = 10; /// Tamño de mi mapa eje x 
	static const int _WordY = 10; /// Tamño de mi mapa eje y

	/// olc::vi2d Son Vectores de 2 dimensiones con su x , y.
	olc::vi2d vWorldSize = { 10,10 };/// MAPA principal ... jugador humano.
	olc::vi2d vWorldWarSize = { _WordX , _WordY };/// MAPA segundario ... para jugador maquina por ahora...

	olc::vi2d isoTileSize = { 40 , 20 }; /// Tamaño en pixeles de cada una de mis Tiles isometricos.

	olc::vi2d vWorldOrigen = { 5 , 1 };/// Donde quiero que comience mi mapa en pantalla.
	olc::vi2d vWarOrigen = { 30 , 30 };

	/// Puntero que va a contener mis sprite a dibujar en consola.
	olc::Sprite* isoPng = nullptr;
	/// Supongo que voy a tener uno para cada barco y un contador para ir diferenciandolos.


	HumanPlayer  p1;
	HumanPlayer  p2;
	std::string name = "Facu";
	std::string name2 = "Martin";
	std::string Ganador;
	
	/// Puntero para contener mi matriz para crear un mundo 2D en un arreglo.
	int* pWorld = nullptr;
	int* pWarWorld = nullptr;
	
	int cntBarco = 0; /// contador de barcos en mapa. graficos
	int cntBarco2 = 0;

	/// Un vector lista para contener eventos para dar informacion en pantalla.
	std::list<std::string> listEvents;

public:


	Game()
	{
		sAppName = "Game";
	}

	bool Winner(HumanPlayer& p1, HumanPlayer& p2)
	{
		bool Winner;

		if (!p1.TieneFlota)
		{
			Ganador = "Ganador: " + p2.name;
		}
		else
		{
			Ganador = "Ganador: " + p1.name;
		}
			

		return Winner;
	}


	bool OnUserCreate() override
	{
		/// Cargo la direecion de mis sprites.
		isoPng = new olc::Sprite("assets/isodemo.png");
		p1.pHumanPlayer(name);
		p2.pHumanPlayer(name2);
		/// Doy el tamaño de mi mapa al arreglo.
		pWorld = new int[vWorldSize.x * vWorldSize.y]{ 0 };
		pWarWorld = new int[vWorldWarSize.x * vWorldWarSize.y]{ 0 };

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

		int nLog = 0; /// Variable de control textos flotantes.
		int Hori = 1; /// Variable de control poss.
		int vert = 1; /// Variable de control poss.
		bool IsRunnig = true; /// Variable de juego en funcionamiento.
		
		/// Donde coloques el cursor dibuja el sprite adyasente ( ͡° ͜ʖ ͡° )
		if (col == olc::RED) vSelected += {-1, +0};
		else if (col == olc::BLUE) vSelected += {+0, -1};
		else if (col == olc::GREEN) vSelected += {+0, +1};
		else if (col == olc::YELLOW) vSelected += {+1, +0};

		/// Lo mismo pero para el mapa 2 ( ͡° ͜ʖ ͡° )
	    if (col == olc::RED) vSelected2 += {-1, +0};
		else if (col == olc::BLUE) vSelected2 += {+0, -1};
		else if (col == olc::GREEN) vSelected2 += {+0, +1};
		else if (col == olc::YELLOW) vSelected2 += {+1, +0};
		
		// Funcion Lambda para convertir "world" en cordenadas para la pantalla.
		auto ToScreen = [&](int x, int y)
		{
			return olc::vi2d
			{
				(vWorldOrigen.x * isoTileSize.x) + (x - y) * (isoTileSize.x / 2),
				(vWorldOrigen.y * isoTileSize.y) + (x + y) * (isoTileSize.y / 2)
			};
		};

		// Lo mismo para mi segundo mapa
		auto ToScreen2 = [&](int x, int y)
		{
			return olc::vi2d
			{
				(vWarOrigen.x * isoTileSize.x) + (x - y) * (isoTileSize.x / 2),
				(vWarOrigen.y * isoTileSize.y) + (x + y) * (isoTileSize.y / 2)
			};
		};

		
		// Da trasparencia al mundo.
		SetPixelMode(olc::Pixel::MASK);

	    

		/// Mundo [1]
		/// (0,0) es mi tope , dibujo desde el tope hasta el final para
		/// haer que mis tiles mas cercanas se dibujen al final.
		for (int y = 0; y < vWorldSize.y; y++)
		{
			for (int x = 0; x < vWorldSize.x; x++)
			{
				
				/// Convierte las celdas a cordenadas del mundo.
				olc::vi2d vWorld = ToScreen(x, y);

				switch (pWorld[y * vWorldSize.x + x])
				{
				case 0:
					// Ocean Tile
					DrawPartialSprite(vWorld.x, vWorld.y - isoTileSize.y, isoPng, 3 * isoTileSize.x, 1 * isoTileSize.y, isoTileSize.x * 2, isoTileSize.y * 2);
					break;
				case 1:
					// Grass visible Tile
					DrawPartialSprite(vWorld.x, vWorld.y, isoPng, 2 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				}
			}
		}


		/// Mundo [2]
		/// Es todo lo mismo para dibujar mi segundo mapa con unas cordenadas propias.
		for (int y = 0; y < vWorldWarSize.y; y++)
		{
			for (int x = 0; x < vWorldWarSize.x; x++)
			{
				olc::vi2d vWorld2 = ToScreen2(x, y); 

				switch (pWarWorld[y * vWorldWarSize.x + x])
				{
				case 0:
					// Invisble Tile                               
					DrawPartialSprite(vWorld2.x, vWorld2.y, isoPng, 1 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
					break;
				case 1:
					// Grass visible Tile
					DrawPartialSprite(vWorld2.x, vWorld2.y, isoPng, 2 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
					break;
				}

			}
		}


		auto AddEvent = [&](std::string s)
		{
			listEvents.push_back(s);
			listEvents.pop_front();
		};
		
		for (auto& s : listEvents)
		{
			// 8 + 20  Separacion entre textos        /// los 3 * 16
			DrawString(350, nLog * 8 - 8, s, olc::Pixel(nLog * -17, nLog * -17, nLog * -17));
			nLog++;
		}
		
		bool Map_crtlvar = vSelected.x >= 0 && vSelected.x < vWorldSize.x && vSelected.y >= 0 && vSelected.y < vWorldSize.y;
		bool Mapwar_crtlvar = vSelected2.x >= 0 && vSelected2.x < vWorldWarSize.x && vSelected2.y >= 0 && vSelected2.y < vWorldWarSize.y;
		
		//////////////////////////////// FIN PRIMITIVAS DEL JUEGO ///////////////////////////////////////////////

		/*Luego de dibujar las primitivas del mapa entra el jugador y bot con sus methodos*/
		/*El jugador coloca sus baracos al terminar se colocan barcos al bot*/
		/*El jugar dispara y recibe la informacion del bot*/
		/*Bot dispara y recibo la informacion*/
		/**/

		/// Rotacion de los barcos.
		if (GetKey(olc::Key::R).bPressed)
		{
			p1.piezas[cntBarco].setOrientation();
		}

		if (GetKey(olc::Key::E).bPressed) /// Solo para debugiar
		{
			SetPixelMode(olc::Pixel::NORMAL);
			Clear(olc::WHITE);
			vWarOrigen = { 16, 1 };
			system("cls");
			p2.MAPA.mostrarMapa();
		}
		if (GetKey(olc::Key::A).bPressed)
		{
			if (p2.MAPA.grid[vSelected2.x][vSelected2.y].isShot)
				std::cout << "Me gusta la macoña" << std::endl;
			else
				std::cout << "No me gusta la macoña" << std::endl;
		}
		

		// Dibuja el sombreado amaralli en cada tile que selecciono.
		SetPixelMode(olc::Pixel::ALPHA);

		/// Convierto las cordenadas a espacio "real" en el mundo.
		olc::vi2d vSelectedWorld = ToScreen(vSelected.x, vSelected.y);
		olc::vi2d vSelectedWorld2 = ToScreen2(vSelected2.x, vSelected2.y); 

		
		if (GetMouse(0).bPressed)
		{
			if (p1.placeShips(vSelected.x, vSelected.y,cntBarco) && p2.placeShips(vSelected.x, vSelected.y,cntBarco2)) {
				if (p1.piezas[cntBarco].getOrientation())
					Hori = 10;
				
				switch (cntBarco)
				{
				case 0:
					++pWorld[vSelected.y * vWorldSize.x + vSelected.x] %= 2;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 1 * Hori] %= 2;
					cntBarco++;
					cntBarco2++;
					break;

				case 1:
					++pWorld[vSelected.y * vWorldSize.x + vSelected.x] %= 2;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 1 * Hori] %= 2;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 2 * Hori] %= 2;
					cntBarco++;
					cntBarco2++;
					break;

				case 2:
					++pWorld[vSelected.y * vWorldSize.x + vSelected.x] %= 2;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 1 * Hori] %= 2;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 2 * Hori] %= 2;
					cntBarco++;
					cntBarco2++;
					break;

				case 3:
					++pWorld[vSelected.y * vWorldSize.x + vSelected.x] %= 2;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 1 * Hori] %= 2;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 2 * Hori] %= 2;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 3 * Hori] %= 2;
					cntBarco++;
					cntBarco2++;
					break;
				
				case 4:
					++pWorld[vSelected.y * vWorldSize.x + vSelected.x] %= 2;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 1 * Hori] %= 2;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 2 * Hori] %= 2;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 3 * Hori] %= 2;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 4 * Hori] %= 2;
					cntBarco++;
					cntBarco2++;
					break;

				default:
					break;
				}

			}
			else {

				if (!Map_crtlvar && !Mapwar_crtlvar)
					AddEvent("Fuera de los Mapas");
				
			    else if (cntBarco != 5)
				{
					if (Map_crtlvar && pWorld[vSelected.y * vWorldSize.x + vSelected.x] == 1)
						AddEvent("Estas sobre otro barco :c");
					else if (Map_crtlvar && pWorld[vSelected.y * vWorldSize.x + vSelected.x] == 1)
						AddEvent("Lugar Invalido");

				}
				else
				{ 
					if (Mapwar_crtlvar && p2.MAPA.grid[vSelected2.x][vSelected2.y].isShot == false)
					{
						AddEvent(p1.disparar(vSelected2.x, vSelected2.y, p2.MAPA));
						++pWarWorld[vSelected2.y * vWorldWarSize.x + vSelected2.x];

					}
					else
						AddEvent("Disparo invalido");
					
				}

				
			}
			
		}
		/// Datos para el mapa 2
		

		// Doy la textura de seleccion para cada barco y el mundo
		if (vMouse.x && vMouse.y != NULL) /// size del barquito y rotazion 
		{
			if (p1.piezas[cntBarco].getOrientation())
				vert = -1; /// Convierto cada posicion en negativo para seguir la rotacion 

			switch (cntBarco)
			{
			case 0: 
				DrawPartialSprite(vSelectedWorld.x, vSelectedWorld.y, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				DrawPartialSprite(vSelectedWorld.x + 20 * vert, vSelectedWorld.y + 10, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				break;
			case 1:
				DrawPartialSprite(vSelectedWorld.x, vSelectedWorld.y, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				DrawPartialSprite(vSelectedWorld.x + 20 * vert, vSelectedWorld.y + 10, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				DrawPartialSprite(vSelectedWorld.x + 40 * vert, vSelectedWorld.y + 20, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				break;
			case 2:
				DrawPartialSprite(vSelectedWorld.x, vSelectedWorld.y, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				DrawPartialSprite(vSelectedWorld.x + 20 * vert, vSelectedWorld.y + 10, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				DrawPartialSprite(vSelectedWorld.x + 40 * vert, vSelectedWorld.y + 20, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				break;
			case 3:
				DrawPartialSprite(vSelectedWorld.x, vSelectedWorld.y, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				DrawPartialSprite(vSelectedWorld.x + 20 * vert, vSelectedWorld.y + 10, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				DrawPartialSprite(vSelectedWorld.x + 40 * vert, vSelectedWorld.y + 20, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				DrawPartialSprite(vSelectedWorld.x + 60 * vert, vSelectedWorld.y + 30, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				break;
			case 4:
				DrawPartialSprite(vSelectedWorld.x, vSelectedWorld.y, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				DrawPartialSprite(vSelectedWorld.x + 20 * vert, vSelectedWorld.y + 10, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				DrawPartialSprite(vSelectedWorld.x + 40 * vert, vSelectedWorld.y + 20, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				DrawPartialSprite(vSelectedWorld.x + 60 * vert, vSelectedWorld.y + 30, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				DrawPartialSprite(vSelectedWorld.x + 80 * vert, vSelectedWorld.y + 40, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				break;
			default:
				DrawPartialSprite(vSelectedWorld.x, vSelectedWorld.y, isoPng, 0 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
				break;
			}
		}

		
		if (GetKey(olc::Key::ESCAPE).bPressed)
		{
		  IsRunnig = false;
		}

		///////////////// DIBUJO DATOS AL MAPA /////////////////////////////////////////////////////////////////



		// Go back to normal drawing with no expected transparency
		SetPixelMode(olc::Pixel::NORMAL);
		
		// Draw Debug Info
		DrawString(4, 4, "Mouse   : " + std::to_string(vMouse.x) + ", " + std::to_string(vMouse.y), olc::BLACK);
		DrawString(4, 14, "Cell    : " + std::to_string(vCell.x) + ", " + std::to_string(vCell.y), olc::BLACK);
		DrawString(4, 24,"Jugador -> ["+p1.name+"]", olc::RED);
		
		if (Map_crtlvar)
		{
			DrawString(4, 34, "Mapa[1] X: " + std::to_string(vSelected.x) + ",Y: " + std::to_string(vSelected.y), olc::BLACK);
		}
		else if (Mapwar_crtlvar)
		{
			DrawString(4, 34, "Mapa[2] X: " + std::to_string(vSelected2.x) + ",Y: " + std::to_string(vSelected2.y), olc::BLACK);
		}
		else{
			DrawString(4, 34, "Mapa [1]: Fuera del mapa ", olc::BLACK);
			DrawString(4, 44, "Mapa [2]: Fuera del mapa ", olc::BLACK);
		}
		/////

		/// mejorar este metodo 
		/*if (Winner(p1, p2))
		{
			SetPixelMode(olc::Pixel::NORMAL);
			Clear(olc::WHITE);
			DrawString(4, 34, Ganador , olc::BLACK,5);
		}else{
			SetPixelMode(olc::Pixel::NORMAL);
			Clear(olc::WHITE);
			DrawString(4, 34, Ganador , olc::BLACK,10);
		}*/

		return IsRunnig;
	}
};
