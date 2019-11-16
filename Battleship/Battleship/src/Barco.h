#pragma once
#include <iostream>
#include <string>



class Barco
{
private:
	int size;
	int hits;
	bool isVertical;
public:
	std::string name;
	
	Barco(int size, std::string name);
	Barco();

	bool getOrientation();
	void setOrientation(bool ori);
	
	bool Hundido();
	
	void setSize(int size);
	int getSize();
	
	void registerShot();
};

