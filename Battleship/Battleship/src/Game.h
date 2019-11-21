﻿#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <string>
#include <iostream>
#include "HumanPlayer.h"
#include "HardBOT.h"


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

	olc::vi2d vWorldOrigen = { 5 , 4 };/// Donde quiero que comience mi mapa en pantalla.
	olc::vi2d vWarOrigen = { 30 , 30 };

	/// Puntero que va a contener mis sprite a dibujar en consola.
	olc::Sprite* isoPng = nullptr;
	olc::Sprite* isoPng2 = nullptr;
	
	HumanPlayer * p1 = new HumanPlayer("Facundo");
	HardBOT * p2 = new HardBOT;
	Barco* Reg_shot = nullptr;
	Barco* Reg_shotIA = nullptr;
	std::string Ganador;
	/// Puntero para contener mi matriz para crear un mundo 2D en un arreglo.
	int* pWorld = nullptr;
	int* pWarWorld = nullptr;
	
	int cntBarco = 0; /// contador de barcos en mapa. graficos.
	int IA_shot = 0; /// Contador de disparos .
	bool status = false; /// Bool para iniciar el juego .

    /// Un vector lista para contener eventos para dar informacion en pantalla.
	std::list<std::string> listEvents;

public:


	Game()
	{
		sAppName = "Game";
	}

	void Winner(HumanPlayer* p1, HardBOT* p2)
	{
		if (p1->revisarFlota() == false)
		{
			Ganador = "Ganador: " + p2->name;
			
			SetPixelMode(olc::Pixel::NORMAL);
			Clear(olc::WHITE);
			DrawString(4, 34, Ganador, olc::BLACK, 5);
			if (GetKey(olc::Key::N).bPressed)
			{
				
			}
			DrawString(4, 84, "Presione [N] para Jugar de nuevo", olc::DARK_RED, 1);
			DrawString(4, 94, "Presione [ESC] para Salir del juego", olc::DARK_RED, 1);
		}
		else if (p2->revisarFlota() == false)
		{
			Ganador = "Ganador: " + p1->name;
			
			SetPixelMode(olc::Pixel::NORMAL);
			Clear(olc::WHITE);
			DrawString(4, 34, Ganador, olc::BLACK, 5);
			if (GetKey(olc::Key::N).bPressed)
			{
				
			}
			DrawString(4, 84, "Presione [N] para Jugar de nuevo", olc::DARK_RED, 1);
			DrawString(4, 94, "Presione [ESC] para Salir del juego", olc::DARK_RED, 1);
		}
		
	}

	bool OnUserCreate() override
	{
		/// Cargo la direecion de mis sprites.
		isoPng = new olc::Sprite("assets/iso1.png"); 
		isoPng2 = new olc::Sprite("assets/iso2.png");
		/// Doy el tamaño de mi mapa al arreglo.
		pWorld = new int[vWorldSize.x * vWorldSize.y]{ 0 };
		pWarWorld = new int[vWorldWarSize.x * vWorldWarSize.y]{ 0 };
		/// Un for para ir cambiando de eventos.
		for (int i = 0; i < 15; i++)
			listEvents.push_back("");

		return true;
	}


	bool OnUserUpdate(float FpsTime) override
	{

		// Pantalla completa en blanco.
		olc::PixelGameEngine::Clear(olc::WHITE);
		Clear(olc::VERY_DARK_CYAN);
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
					DrawPartialSprite(vWorld.x, vWorld.y, isoPng2, 2 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
					break;
				case 1: // Flota de 2
					DrawPartialSprite(vWorld.x, vWorld.y - isoTileSize.y, isoPng, 2 * isoTileSize.x, 1 * isoTileSize.y, isoTileSize.x, isoTileSize.y * 2);
					break;
				case 2: // celda cruz 
					DrawPartialSprite(vWorld.x, vWorld.y - isoTileSize.y, isoPng, 0 * isoTileSize.x, 1 * isoTileSize.y, isoTileSize.x, isoTileSize.y * 2);
					break;
				case 3: // Flota de 3
					DrawPartialSprite(vWorld.x, vWorld.y - isoTileSize.y, isoPng2, 0 * isoTileSize.x, 1 * isoTileSize.y, isoTileSize.x, isoTileSize.y * 2);
					break;
				case 4: // Segunda flota de 3
					DrawPartialSprite(vWorld.x, vWorld.y - isoTileSize.y, isoPng2, 0 * isoTileSize.x, 1 * isoTileSize.y, isoTileSize.x, isoTileSize.y * 2);
					break;
				case 5: // flota de 4
					DrawPartialSprite(vWorld.x, vWorld.y - isoTileSize.y, isoPng, 1 * isoTileSize.x, 1 * isoTileSize.y, isoTileSize.x, isoTileSize.y * 2);
					break;
				case 6: // flota de 5
					DrawPartialSprite(vWorld.x, vWorld.y - isoTileSize.y, isoPng, 3 * isoTileSize.x, 1 * isoTileSize.y, isoTileSize.x, isoTileSize.y * 2);
					break;
				case 7: /// Disparo agua
					DrawPartialSprite(vWorld.x, vWorld.y, isoPng, 2 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
					break;

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
					// Mapa sin descubrir.                              
					DrawPartialSprite(vWorld2.x, vWorld2.y, isoPng, 1 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
					break;
				case 1:
					// Hit Agua
					DrawPartialSprite(vWorld2.x, vWorld2.y, isoPng2, 2 * isoTileSize.x, 0, isoTileSize.x, isoTileSize.y);
					break;
				case 2:
					// Hit Barco RED                          
					DrawPartialSprite(vWorld2.x, vWorld2.y, isoPng, 0 * isoTileSize.x, 1, isoTileSize.x, isoTileSize.y);
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
			// 8 + 20  Separacion entre textos olc::Pixel(nLog * -17, nLog * -17, nLog * -17)        /// los 3 * 16 
			DrawString(320, nLog * 8 - 8, s, olc::Pixel(nLog * 18, nLog * 18, nLog * 18));
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
			p1->piezas[cntBarco].setOrientation();
		}

		if (GetKey(olc::Key::E).bPressed) /// Solo para debugiar
		{
			status = true;
			SetPixelMode(olc::Pixel::NORMAL);
			Clear(olc::VERY_DARK_CYAN);
			vWarOrigen = { 16, 4 };
			p2->placeShips(vSelected.x, vSelected.y);
			system("cls");
			p2->board.mostrarMapa();
		}

		if (GetKey(olc::Key::A).bPressed)
		{
			system("cls");
			p1->board.mostrarMapa();
		}

		
		// Dibuja el sombreado amaralli en cada tile que selecciono.
		SetPixelMode(olc::Pixel::ALPHA);

		/// Convierto las cordenadas a espacio "real" en el mundo.
		olc::vi2d vSelectedWorld = ToScreen(vSelected.x, vSelected.y);
		olc::vi2d vSelectedWorld2 = ToScreen2(vSelected2.x, vSelected2.y);
		

		if (GetMouse(0).bPressed && status)
		{
			if (p1->placeShips(vSelected.x, vSelected.y)) {

				if (p1->piezas[cntBarco].getOrientation())
					Hori = 10;

				switch (cntBarco)
				{
				case 0: /// Barco de 2
					++pWorld[vSelected.y * vWorldSize.x + vSelected.x] = 1;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 1 * Hori] = 1;
					cntBarco++;
					break;

				case 1: /// barco de 3
					++pWorld[vSelected.y * vWorldSize.x + vSelected.x] = 3;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 1 * Hori] = 3;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 2 * Hori] = 3;
					cntBarco++;
					break;

				case 2: ///Segundo barco de 3
					++pWorld[vSelected.y * vWorldSize.x + vSelected.x] = 4;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 1 * Hori] = 4;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 2 * Hori] = 4;
					cntBarco++;
					break;

				case 3: /// barco de 4
					++pWorld[vSelected.y * vWorldSize.x + vSelected.x] = 5;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 1 * Hori] = 5;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 2 * Hori] = 5;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 3 * Hori] = 5;
					cntBarco++;
					break;

				case 4: /// barco de 5
					++pWorld[vSelected.y * vWorldSize.x + vSelected.x] = 6;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 1 * Hori] = 6;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 2 * Hori] = 6;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 3 * Hori] = 6;
					++pWorld[(vSelected.y * vWorldSize.x + vSelected.x) + 4 * Hori] = 6;
					cntBarco++;
					break;

				default:
					break;
				}
			}
			else { /// Si estatus es 1 puedo jugar , sino preciona E
				
				/// Si se hace click fuera del mapa se printea el mensaje
				if (!Map_crtlvar && !Mapwar_crtlvar)
					AddEvent("Fuera de los Mapas");

				/// Si no todos los barcos estan en el mapa solo pueden existir 2 tipos de errores
				if (cntBarco != 5)
				{
					if (Map_crtlvar && pWorld[vSelected.y * vWorldSize.x + vSelected.x] != 0)
						AddEvent("Lugar Invalido"); /// Estas en un lugar invalido para colocar
				}
				else /// Todos tus barcos y los de la IA estan en mapa // Empiza el juego //.
				{
					if (Mapwar_crtlvar && p2->board.grid[vSelected2.x][vSelected2.y].isShot == false)
					{
						/// Disparo del jugador Humano
						Reg_shot = p1->disparar(vSelected2.x, vSelected2.y, p2->board);
						AddEvent(" ");
						if (Reg_shot == nullptr) /// Si el disparo devuelve Null Agua
						{
							AddEvent(">"+p1->name+": --[AGUA]--");
							pWarWorld[vSelected2.y * vWorldWarSize.x + vSelected2.x] = 1; // Cambio a una casilla disparada
						}
						else {
							
							AddEvent(">"+p1->name+": Le dio a un Barco"); /// Si le das a un Barco
							if (Reg_shot->hundido()) /// Se fija si fue hundido
							{
								AddEvent(">" + p1->name + ":");
								AddEvent("Flota enemiga-["+Reg_shot->name+"]-Hundida"); /// Te dice que barco fue hundido
							}
							pWarWorld[vSelected2.y * vWorldWarSize.x + vSelected2.x] = 2;
						}

						
						//// Disparo de la IA // si dispara 2 veces al mismo lugar causa un bug grafico, es solucionable pero si la IA funciona 
						//// Jamas volveria a disparar en el mismo lugar
						Reg_shotIA = p2->disparar(vSelected2.x, vSelected2.y, p1->board);
						IA_shot++;
						if (Reg_shotIA == nullptr)
						{
							AddEvent(">IA "+p2->name+": --[AGUA]--");
							pWorld[vSelected2.y * vWorldWarSize.x + vSelected2.x] = 7;
						}
						else
						{
							AddEvent(">IA "+p2->name+": le pego a tu Barco");
							if (Reg_shotIA->hundido())
							{
								AddEvent(">IA "+ p2->name +":");
								AddEvent("Hundio tu Flota [" + Reg_shotIA->name + "]");
							}
							pWorld[vSelected2.y * vWorldWarSize.x + vSelected2.x] = 2;
						}
						
					}
					else
						AddEvent("> --[Disparo invalido]--");
				}
			}
		}
		

		// Doy la textura de seleccion para cada barco y el mundo
		if (vMouse.x && vMouse.y != NULL) /// size del barquito y rotazion 
		{
			if (p1->piezas[cntBarco].getOrientation())
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
		DrawString(4, 24,"Jugador -> ["+p1->name+"]", olc::RED);
		DrawString(650, 2, "------------------",olc::WHITE);
		DrawString(650, 12," Enemigo IA ->["+p2->name+"]",olc::RED);
		DrawString(650, 22," La IA disparo ->["+ std::to_string(IA_shot) +"]");
		DrawString(650, 32,"-------------------",olc::WHITE);
		
		if (!status)
		{
			DrawString(250, 4, ".:Batalla Naval UTN:.", olc::WHITE, 1);
			DrawString(250, 14, "Made by :", olc::WHITE, 1);
			DrawString(250, 24, "[Facundo , Franco and Martin]", olc::RED, 1);
			DrawString(250, 55, "Presione la tecla [E] para Jugar", olc::VERY_DARK_RED, 2);
		}
		else if (status && cntBarco != 5)
		{
			DrawString(300, 50, "Coloque sus Flotas en el mapa con agua",olc::WHITE,1);
			DrawString(300, 60, "Flota ->["+p1->piezas[cntBarco].name +"]",olc::WHITE,1);
			DrawString(300, 70, "Presiona [R] para rotar el Barco", olc::WHITE, 1);
		}
		else if (cntBarco == 5 && IA_shot == 0)
		{
			DrawString(300, 50, "Dispara en el Mapa enemigo en blanco,", olc::WHITE, 1);
			DrawString(300, 60, "hasta hundir todos los Barcos enemigos.", olc::WHITE, 1);
		}
		else if (Map_crtlvar)
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

		Winner(p1, p2);

		return IsRunnig;
	}



};

void Newgame(Game * A)
{
	
}