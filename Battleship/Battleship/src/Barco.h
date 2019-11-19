#pragma once
#include <iostream>
#include <string>

class Barco
{
private:
	int size;
	int hits;
	bool isSunk = false;
	bool isVertical = true;

public:
	std::string name;
	
	Barco(int size, std::string name);
	Barco();

	bool getOrientation();
	void setOrientation();
	
	bool hundido();
	

	void setSize(int size);
	int getSize();
	
	void registerShot();
};

