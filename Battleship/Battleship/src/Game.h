#pragma once

#define OLC_PGE_APPLICATION
#include <string>
#include <iostream>
#include "olcPixelGameEngine.h"

/// La clase juego se encarga de usar todos los recursos graficos de OLC::PixelGameEngine
class Game : public olc::PixelGameEngine 
{
public:

	Game();

	bool OnUserCreate() override; /// Metodo para inicializar o crear variables que necesite en tiempo de ejecucion de mi juego
	
	bool OnUserUpdate(float FpsTime) override; /// Metodo para realizar todos mis acciones en pantalla recive los FPS. /// siempre actualizar en tiempo real los eventos en mi mapa.
	                                     
	
	void Exit(); /// Metodo para salir del juego pulsando una tecla.

private:
	
	/// olc::vi2d Son Vectores de 2 dimensiones con su x , y.
	olc::vi2d vWorldSize = { 10 ,10 }; /// MAPA principal ... jugador humano.
	olc::vi2d vWorldWarSize = { 10 ,10 }; /// MAPA segundario ... para jugador maquina por ahora...

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
};
