#include <iostream>
#include <fstream>
#include <string>

struct Pipe
{
	std::string name;
	float length;
	int diameter;
	bool isRepairing = false;
};

struct CompressorStation
{
	std::string name;
	short int workshopNum;
	short int activeWorkshopNum;
	float effectiveness;
};

void showMenu() {
	std::cout << "Gas pipeline transport model \n\n";
	std::cout << "Menu: \n";
	std::cout << "1. Add a pipe \n";
	std::cout << "2. Add a compressor station \n";
	std::cout << "3. View all objects \n";
	std::cout << "4. Edit a pipe \n";
	std::cout << "5. Edit a compressor station \n";
	std::cout << "6. Save \n";
	std::cout << "7. Open \n";
	std::cout << "0. Exit \n\n";
	std::cout << "Please select an action :";
}

void checkCinError() {
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "ERROR\n";
	}
}

void addPipe(Pipe& pipe) {
	std::cout << "Enter name(mileage) of the pipe: ";
	getline(std::cin >> std::ws, pipe.name);

	while (true) {
		std::cout << "\nEnter pipe length (in meters): ";
		std::cin >> pipe.length;

		checkCinError();
		if (pipe.length <= 0) {
			std::cout << "ERROR. Pipe length can`t be less than 0 meters or be equal 0 meters\n";
		}
		else if (pipe.length > 50) {
			std::cout << "ERROR. Pipe length can`t be more than 50 meters\n";
		}
		else {
			break;
		}
	}

	while (true) {
		std::cout << "\nEnter pipe diameter (in millimeters): ";
		std::cin >> pipe.diameter;

		checkCinError();
		if (pipe.diameter <= 0) {
			std::cout << "ERROR. Pipe diameter can`t be less than 0 millimeters or be equal 0 millimeters\n";
		}
		else if (pipe.diameter > 5000) {
			std::cout << "ERROR. Pipe diameter can`t be more than 5000 millimeters\n";
		}
		else {
			break;
		}
	}

	while (true) {
		std::cout << "\nChoose pipe status (0 - in repairing, 1 - not in repairing): ";
		std::cin >> pipe.isRepairing;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "ERROR\n";
		}
		else {
			break;
		}
	}
}

void addCs(CompressorStation& cs) {
	std::cout << "Enter name of the compressor station: ";
	getline(std::cin >> std::ws, cs.name);

	while (true) {
		std::cout << "\nEnter the number of workshops: ";
		std::cin >> cs.workshopNum;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "ERROR\n";
		}
		else if (cs.workshopNum <= 0) {
			std::cout << "ERROR. The number of workshops can`t be less than 0 or be equal 0\n";
		}
		else if (cs.workshopNum > 100) {
			std::cout << "ERROR. The number of workshops can`t be more than 100\n";
		}
		else {
			break;
		}
	}

	while (true) {
		std::cout << "\nEnter the number of active workshops: ";
		std::cin >> cs.activeWorkshopNum;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "ERROR\n";
		}
		else if (cs.activeWorkshopNum < 0) {
			std::cout << "ERROR. The number of active workshops can`t be less than 0\n";
		}
		else if (cs.activeWorkshopNum > 100) {
			std::cout << "ERROR. The number of active workshops can`t be more than 100\n";
		}
		else if (cs.activeWorkshopNum > cs.workshopNum) {
			std::cout << "ERROR. The number of active workshops can`t be more than the number of workshops\n";
		}
		else {
			break;
		}
	}

	while (true) {
		std::cout << "\nEnter the compressor station effectiveness: ";
		std::cin >> cs.effectiveness;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "ERROR\n";
		}
		else {
			break;
		}
	}
}

std::ostream& operator << (std::ostream& out, const Pipe& pipe) {
	out << "Information about pipes:\n\n"
		<< "Pipe name: " << pipe.name
		<< "\nPipe length: " << pipe.length
		<< "\nPipe diameter: " << pipe.diameter
		<< "\nPipe status: " << ((pipe.isRepairing) ? "not " : "") << "in repairing\n\n\n";
	return out;
}

std::ostream& operator << (std::ostream& out, const CompressorStation& cs) {
	out << "Information about compressor stations:\n\n"
		<< "Compressor station name: " << cs.name
		<< "\nThe number of workshops: " << cs.workshopNum
		<< "\nThe number of active workshops: " << cs.activeWorkshopNum
		<< "\nThe compressor station effectiveness: " << cs.effectiveness << "\n\n\n";
	return out;
}

void editPipe(Pipe& pipe) {
	while (true) {
		std::cout << "Enter new pipe status (0 - in repairing, 1 - not in repairing): ";
		std::cin >> pipe.isRepairing;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "ERROR\n";
		}
		else {
			break;
		}
	}
}

void editCs(CompressorStation& cs) {
	while (true) {
		std::cout << "\nEnter new value of active workshops: ";
		std::cin >> cs.activeWorkshopNum;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "ERROR\n";
		}
		else if (cs.activeWorkshopNum < 0) {
			std::cout << "ERROR. The number of active workshops can`t be less than 0\n";
		}
		else if (cs.activeWorkshopNum > 100) {
			std::cout << "ERROR. The number of active workshops can`t be more than 100\n";
		}
		else if (cs.activeWorkshopNum > cs.workshopNum) {
			std::cout << "ERROR. The number of active workshops can`t be more than the number of workshops\n";
		}
		else {
			break;
		}
	}
}

void savePipe(Pipe& pipe, bool pipeExist) {
	std::ofstream out;
	out.open("data.txt");

	if (out.is_open()) {
		if (pipeExist)
			out << "1" << "\n" << pipe.name << "\n" << pipe.length << "\n" << pipe.diameter << "\n" << pipe.isRepairing << "\n";
		else
			out << "0\n";
	}
	out.close();
}

void saveCs(CompressorStation& cs, bool csExist) {
	std::ofstream out;
	out.open("data.txt", std::ios::app);

	if (out.is_open() && csExist)
		out << "1" << "\n" << cs.name << "\n" << cs.workshopNum << "\n" << cs.activeWorkshopNum << "\n" << cs.effectiveness << "\n";
	else
		out << "0";
	out.close();
}

bool loadPipe(Pipe& pipe, std::ifstream& in) {
	int pipeCount;

	if (in.is_open()) {
		in >> pipeCount;
		for (int i = 0; i < pipeCount; i++) {
			getline(in >> std::ws, pipe.name);
			in >> pipe.length;
			in >> pipe.diameter;
			in >> pipe.isRepairing;
		}
		if (pipeCount)
			return true;
	}
	return false;
}

bool loadCs(CompressorStation& cs, std::ifstream& in) {
	int csCount;

	if (in.is_open()) {
		in >> csCount;
		for (int i = 0; i < csCount; i++) {
			getline(in >> std::ws, cs.name);
			in >> cs.workshopNum;
			in >> cs.activeWorkshopNum;
			in >> cs.effectiveness;
		}
		if (csCount)
			return true;
	}
	return false;
}

int main()
{
	Pipe firstPipe;
	bool pipeExist = false;
	CompressorStation firstCs;
	bool csExist = false;

	while (1) // Infinity cycle causes a menu
	{
		showMenu();
		unsigned short int action; // Action in menu
		std::cin >> action;

		if (std::cin.good() && action >= 0 && action <= 7) {
			switch (action) {
			case 0:
				return 0;

			case 1:
				if (pipeExist) {
					std::cout << "Pipe is already exist\n\n";
				}
				else {
					addPipe(firstPipe);
					std::cout << "New pipe added successfully!\n\n";
					pipeExist = true;
				}
				break;

			case 2:
				if (csExist) {
					std::cout << "Compressor station is already exist\n\n";
				}
				else {
					addCs(firstCs);
					std::cout << "New compressor station added successfully!\n\n";
					csExist = true;
				}
				break;
			case 3:
				if (pipeExist) {
					std::cout << firstPipe;
				}
				else {
					std::cout << "Pipe does not exist\n\n";
				}
				if (csExist) {
					std::cout << firstCs;
				}
				else {
					std::cout << "Compressor station does not exist\n\n";
				}
				break;
			case 4:
				if (pipeExist) {
					editPipe(firstPipe);
					std::cout << "The pipe was successfully edited!\n\n";
				}
				else {
					std::cout << "ERROR. Pipe does not exist\n\n";
				}
				break;
			case 5:
				if (csExist) {
					editCs(firstCs);
					std::cout << "The compressor station was successfully edited!\n\n";
				}
				else {
					std::cout << "ERROR. Compressor station does not exist\n\n";
				}
				break;
			case 6:
				savePipe(firstPipe, pipeExist);
				if (pipeExist)
					std::cout << "The pipe was successfully saved!\n\n";
				else
					std::cout << "The pipe does not exist\n\n";

				saveCs(firstCs, csExist);
				if (csExist) {
					std::cout << "The compressor station was successfully saved!\n\n";
				}
				else
					std::cout << "The compressor station does not exist\n\n";

				break;
			case 7:
				std::ifstream file;
				file.open("data.txt");
				pipeExist = loadPipe(firstPipe, file);
				if (pipeExist)
					std::cout << "The pipe was successfully loaded!\n\n";
				else
					std::cout << "Pipe does not exist\n\n";

				csExist = loadCs(firstCs, file);
				if (csExist) {
					std::cout << "The compressor station was successfully loaded!\n\n";
				}
				else
					std::cout << "The compressor station does not exist\n\n";
				break;
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "ERROR\n\n";
		}
	}
	return 0;
}
