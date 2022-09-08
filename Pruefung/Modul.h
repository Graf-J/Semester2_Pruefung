#pragma once
#include "List.h"

class Modul
{
private:
	std::string ID;
	std::string bezeichnung;
	std::string art;
	int creditPoints;

public:
	Modul(std::string ID, std::string bezeichnung, std::string art, int creditPoints);

	void update(std::string bezeichnung, std::string art, int creditPoints);

	friend bool operator==(Modul& modul, std::string str);
	friend std::ostream& operator<<(std::ostream& os, Modul& obj);
};

