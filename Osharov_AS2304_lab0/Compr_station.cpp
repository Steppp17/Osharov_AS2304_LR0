#include "Compr_station.h"
#include "utils.h"


int Compr_station::max_id = 0;

int Compr_station::get_num_workshops() const {
	return num_workshops;
}

void Compr_station::change_num_run_workstation(int num, int i) {
	if (this->num_run_workshops + num > this->num_workshops) {
		std::cout << "Addig more workhops than there are id" << i << std::endl;
		this->num_run_workshops = this->num_workshops;
	}
	else if (this->num_run_workshops + num < 0) {
		std::cout << "Adding is impossible less than the number or workshops id" << i << std::endl;
		this->num_run_workshops = 0;
	}
	else {
		std::cout << "Adding run workshops id" << i << std::endl;
		this->num_run_workshops = this->num_run_workshops + num;
	}
}


void Compr_station::edit() {
	std::cout << "Input number of running workshops: ";
	this->num_run_workshops = get_num_value(0, this->num_workshops + 1);
}

double Compr_station::used_per() const {
	double result = (static_cast<double>(this->num_run_workshops) / this->num_workshops) * 100;
	return result;
}


int Compr_station::get_id() const {
	return max_id;
}

int Compr_station::get_max_id() {
	max_id++;
	return max_id;
}

std::string Compr_station::get_name() const {
	return this->name;
}

int Compr_station::get_pipes_number() {
	return pipes_number;
}


void Compr_station::up_pipes_number() {
	pipes_number++;
}

void Compr_station::down_pipes_number() {
	pipes_number--;
}


std::istream& operator >> (std::istream& in, Compr_station& Cs) {
	std::cout << "Input the Name of CS: ";
	INPUT_LINE(in, Cs.name);
	std::cout << "Input number of workshops: ";
	Cs.num_workshops = get_num_value(0, std::numeric_limits<int>::max());
	std::cout << "Input number of running workshops: ";
	Cs.num_run_workshops = get_num_value(0, Cs.num_workshops + 1);
	std::cout << "Input the efficiency of CS: ";
	Cs.efficiency = get_num_value(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());

	return in;
}


std::ostream& operator << (std::ostream& out, const Compr_station& Cs) {
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "Compresor Station" << std::endl;
	std::cout << "The name of compressor station: " << Cs.name << std::endl;
	std::cout << "Number of workshops on compressor station: " << Cs.num_workshops << std::endl;
	std::cout << "Number of running workshops on compressor station: " << Cs.num_run_workshops << std::endl;
	std::cout << "Efficiency compressor station: " << Cs.efficiency << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl << std::endl;
	return out;
}


std::ifstream& operator >> (std::ifstream& fin, Compr_station& Cs) {
	std::string name;
	fin >> Cs.id;
	Cs.max_id = std::max(Cs.id, Cs.max_id);
	fin.ignore();
	if (std::getline(fin, name, '\n')) Cs.name = name;
	fin >> Cs.num_workshops >> Cs.num_run_workshops >> Cs.efficiency >> Cs.pipes_number;
	return fin;
}

std::ofstream& operator << (std::ofstream& fout, const Compr_station& Cs) {
	fout << Cs.name << std::endl
		<< Cs.num_workshops << ' '
		<< Cs.num_run_workshops << ' '
		<< Cs.efficiency << ' '
		<< Cs.pipes_number << std::endl;
	return fout;
}