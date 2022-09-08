#pragma once

#include "Modul.h"
#include <string>

class Lehrveranstaltung
{
private:
	std::string ID;
	std::string bezeichnung;
	int semester;
	std::string pruefungsform;
	Modul* modul;
	
public:
	Lehrveranstaltung(std::string ID, std::string bezeichnung, int semester, std::string pruefungsform);

	Modul* getModul();
	void setModul(Modul* modul);
	void update(std::string bezeichnung, int semester, std::string pruefungsform);

	friend bool operator==(Lehrveranstaltung& lehrveranstaltung, std::string str);
	friend std::ostream& operator<<(std::ostream& os, Lehrveranstaltung& obj);
};

