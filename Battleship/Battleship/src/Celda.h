#pragma once
#include "Barco.h"
#include<fstream>

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

