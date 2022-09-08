#include <iostream>
#include "Lehrveranstaltung.h"

Lehrveranstaltung::Lehrveranstaltung(std::string ID, std::string bezeichnung, int semester, std::string pruefungsform)
{
	this->ID = ID;
	this->bezeichnung = bezeichnung;
	this->semester = semester;
	this->pruefungsform = pruefungsform;
	modul = nullptr;
}

Modul* Lehrveranstaltung::getModul()
{
	return modul;
}

void Lehrveranstaltung::setModul(Modul* modul)
{
	this->modul = modul;
}

void Lehrveranstaltung::update(std::string bezeichnung, int semester, std::string pruefungsform)
{
	this->bezeichnung = bezeichnung;
	this->semester = semester;
	this->pruefungsform = pruefungsform;
}

bool operator==(Lehrveranstaltung& lehrveranstaltung, std::string str)
{
	return lehrveranstaltung.ID == str;
}

std::ostream& operator<<(std::ostream& os, Lehrveranstaltung& obj)
{
	os << "Lehrveranstaltung: ID " << obj.ID << "\n"
		<< "\t" << obj.bezeichnung
		<< "\n\tSemester: " << obj.semester
		<< "\n\tPruefungsform: " << obj.pruefungsform;

	if (obj.modul) os << "\n\tModul: " << (*obj.modul);

	return os;
}
