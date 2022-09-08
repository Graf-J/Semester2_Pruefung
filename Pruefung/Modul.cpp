#include <iostream>
#include "Modul.h"
#include "Lehrveranstaltung.h"

Modul::Modul(std::string ID, std::string bezeichnung, std::string art, int creditPoints)
{
	this->ID = ID;
	this->bezeichnung = bezeichnung;
	this->art = art;
	this->creditPoints = creditPoints;
}

void Modul::update(std::string bezeichnung, std::string art, int creditPoints)
{
	this->bezeichnung = bezeichnung;
	this->art = art;
	this->creditPoints = creditPoints;
}

bool operator==(Modul& modul, std::string str)
{
	return modul.ID == str;
}

std::ostream& operator<<(std::ostream& os, Modul& obj)
{
	os << obj.ID << "-" << obj.bezeichnung << "-" << obj.art << "-CP " << obj.creditPoints;
	return os;
}
