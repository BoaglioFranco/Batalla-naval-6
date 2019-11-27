#pragma once
#include "Barco.h"
#include<fstream>


///Unidad basica por la cual estan compuestas los mapas en este juego.
///Si la celda tiene un barco, tiene un puntero a este.
///De ser agua el puntero apunta a NULL


class Celda
{
public:
	int dato;
	bool isShot;
	Barco* miembroDe;
	
	Celda();
	void registrarDisparo();
	void setMiembroDe(Barco& miembro);
	
};

