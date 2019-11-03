#pragma once
#include <iostream>
#include <string>

enum Dir
{
	D_UP, D_RIGHT, D_DOWN, D_LEFT
};

class Barco
{
private:
	int size;
	int hits;

public:
	std::string name;
	Dir orientacion;
	
	Barco(int size, std::string name);
	Barco();
	
	bool Hundido();
	
	void setSize(int size);
	int getSize();
	
	void registerShot();
};

