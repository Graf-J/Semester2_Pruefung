#include <iostream>
#include <string>

#include "List.h"
#include "List.cpp"
#include "Modul.h"
#include "Lehrveranstaltung.h"

void parseL(std::string input, int colonPosition, std::string& ID, std::string& bezeichnung, int& semester, std::string& pruefungsform) {
	size_t firstSemicolonPosition = input.find(";");
	ID = input.substr(colonPosition + 1, firstSemicolonPosition - colonPosition - 1);

	size_t secondSemicolonPosition = input.find(";", firstSemicolonPosition + 1);
	bezeichnung = input.substr(firstSemicolonPosition + 1, secondSemicolonPosition - firstSemicolonPosition - 1);

	size_t thirdSemicolonPosition = input.find(";", secondSemicolonPosition + 1);
	semester = atoi(input.substr(secondSemicolonPosition + 1, thirdSemicolonPosition - secondSemicolonPosition - 1).c_str());

	pruefungsform = input.substr(thirdSemicolonPosition + 1);
}

void parseM(std::string input, int colonPosition, std::string& ID, std::string& bezeichnung, std::string& art, int& creditPoints) {
	size_t firstSemicolonPosition = input.find(";");
	ID = input.substr(colonPosition + 1, firstSemicolonPosition - colonPosition - 1);

	size_t secondSemicolonPosition = input.find(";", firstSemicolonPosition + 1);
	bezeichnung = input.substr(firstSemicolonPosition + 1, secondSemicolonPosition - firstSemicolonPosition - 1);

	size_t thirdSemicolonPosition = input.find(";", secondSemicolonPosition + 1);
	art = input.substr(secondSemicolonPosition + 1, thirdSemicolonPosition - secondSemicolonPosition - 1);

	creditPoints= atoi(input.substr(thirdSemicolonPosition + 1).c_str());
}

void parseJoin(std::string input, int colonPosition, std::string& lehrveranstaltungID, std::string& modulID) {
	size_t firstSemicolonPosition = input.find(";");
	lehrveranstaltungID = input.substr(colonPosition + 1, firstSemicolonPosition - colonPosition - 1);

	modulID = input.substr(firstSemicolonPosition + 1);
}

int main()
{
	List<Modul*> modules;
	List<Lehrveranstaltung*> lehrveranstaltungen;
	
	while (true) {
		try {
			std::string input;
			std::getline(std::cin, input);

			size_t colonPosition = input.find(":");
			std::string command = input.substr(0, colonPosition);

			if (command == "INSERT_L") {
				std::string ID;
				std::string bezeichnung;
				int semester;
				std::string pruefungsform;
				parseL(input, colonPosition, ID, bezeichnung, semester, pruefungsform);

				lehrveranstaltungen.add(new Lehrveranstaltung(ID, bezeichnung, semester, pruefungsform));
				std::cout << "[INSERT] Lehrveranstaltung: " << ID << std::endl;
			}
			else if (command == "INSERT_M") {
				std::string ID;
				std::string bezeichnung;
				std::string art;
				int creditPoints;
				parseM(input, colonPosition, ID, bezeichnung, art, creditPoints);

				modules.add(new Modul(ID, bezeichnung, art, creditPoints));
				std::cout << "[INSERT] Modul: " << ID << std::endl;
			}
			else if (command == "JOIN") {
				std::string lehrveranstaltungID;
				std::string modulID;
				parseJoin(input, colonPosition, lehrveranstaltungID, modulID);

				Modul* modul = modules.find(modulID);
				Lehrveranstaltung* lehrveranstaltung = lehrveranstaltungen.find(lehrveranstaltungID);
				lehrveranstaltung->setModul(modul);
				std::cout << "[JOIN]   Modul: " << modulID << " -> Lehrveranstaltung: " << lehrveranstaltungID << std::endl;
			}
			else if (command == "DELETE_L") {
				std::string ID = input.substr(colonPosition + 1);

				lehrveranstaltungen.remove(ID);
				std::cout << "[DELETE] Lehrveranstaltung: " << ID << std::endl;
			}
			else if (command == "DELETE_M") {
				std::string ID = input.substr(colonPosition + 1);

				bool moduleFound = false;
				for (int i = 0; i < lehrveranstaltungen.getLength(); i++) {
					Modul* modul = lehrveranstaltungen[i]->getModul();
					if (modul) {
						if (*modul == ID) {
							moduleFound = true;
							break;
						}
					};
				}

				if (moduleFound) throw std::exception("Module in use");

				modules.remove(ID);
				std::cout << "[DELETE] Modul: " << ID << std::endl;
			}
			else if (command == "UPDATE_L") {
				std::string ID;
				std::string bezeichnung;
				int semester;
				std::string pruefungsform;
				parseL(input, colonPosition, ID, bezeichnung, semester, pruefungsform);

				Lehrveranstaltung* lehrveranstaltung = lehrveranstaltungen.find(ID);
				lehrveranstaltung->update(bezeichnung, semester, pruefungsform);
				std::cout << "[UPDATE] Lehrveranstaltung: " << ID << std::endl;
			}
			else if (command == "UPDATE_M") {
				std::string ID;
				std::string bezeichnung;
				std::string art;
				int creditPoints;
				parseM(input, colonPosition, ID, bezeichnung, art, creditPoints);

				Modul* modul = modules.find(ID);
				modul->update(bezeichnung, art, creditPoints);
				std::cout << "[UPDATE] Modul: " << ID << std::endl;
			}
			else if (command == "SELECT") {
				std::string ID = input.substr(colonPosition + 1);

				if (ID == "*") {
					std::cout << "[SELECT] Lehrveranstaltung: *" << std::endl;
					for (int i = 0; i < lehrveranstaltungen.getLength(); i++) {
						std::cout << *lehrveranstaltungen[i] << std::endl;
					}
				}
				else {
					Lehrveranstaltung* lehrveranstaltung = lehrveranstaltungen.find(ID);
					std::cout << "[SELECT] Lehrveranstaltung: " << ID << "\n" << *lehrveranstaltung << std::endl;
				}
			}
			else if (command == "EXIT") {
				std::cout << "[EXIT]" << std::endl;
				break;
			}
			else {
				throw std::exception("Unknown Command");
			}
		}
		catch (std::exception ex) {
			std::cout << "[ERROR]  " << ex.what() << std::endl;
		}
	};

	return 0;
}
