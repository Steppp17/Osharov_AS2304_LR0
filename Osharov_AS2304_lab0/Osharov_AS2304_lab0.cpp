#include <iostream>
#include <unordered_map>
#include <limits>
#include "utils.h"
#include "Pipe.h"
#include "Compr_station.h"
#include <chrono>
#include <format>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
using namespace chrono;


void show_commands();


int main()
{
	Network network;
	network.from_file("data");
	redirect_output_wrapper cerr_out(cerr);
	string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_" + time + ".txt");
	if (logfile)
		cerr_out.redirect(logfile);
	std::unordered_map<int, Pipe> pipes;
	std::unordered_map<int, Compr_station> compr_stations;
	int choice;

	while (true) {
		show_commands();
		std::cout << "\nEnter your choice: ";
		choice = get_num_value(0, 16);
		switch (choice) {
		case 1:
		{
			network.add_new_pipe();
			break;
		}
		case 2:
		{
			network.add_new_cs();
			break;
		}
		case 3:
		{
			network.add_new_edge();
			break;
		}
		case 4:
		{
			std::cout << "Pipes:" << std::endl;
			network.show_pipes();
			std::cout << "Compresor stations:" << std::endl;
			network.show_compr_stations();
			std::cout << "Edges:" << std::endl;
			network.show_edges();
			break;
		}
		case 5:
		{
			if (network.show_pipes()) {
				int id;
				std::cout << "Select pipe id: ";
				id = get_num_value(0, std::numeric_limits<int>::max());
				if (network.del_pipe(id)) std::cout << "Pipe was deleted" << std::endl;
				else std::cout << "There is no pipe with that id" << std::endl;
			}
			break;
		}
		case 6:
		{
			if (network.show_compr_stations()) {
				int id;
				std::cout << "Input CS id: ";
				id = get_num_value(0, std::numeric_limits<int>::max());
				if (network.del_compr_station(id)) std::cout << "CS was deleted" << std::endl;
			}
			break;
		}
		case 7:
		{
			if (network.show_pipes()) {
				int id;
				std::cout << "Input pipe id: " << std::endl;
				id = get_num_value(0, std::numeric_limits<int>::max());;

				if (network.edit_pipe(id)) std::cout << "Pipe was edited" << std::endl;
				else std::cout << "There is no pipe with that id" << std::endl;
			}
			break;
		}
		case 8:
		{
			if (network.show_compr_stations()) {
				int id;
				std::cout << "Input CS id: " << std::endl;
				id = get_num_value(0, std::numeric_limits<int>::max());

				if (network.edit_compr_station(id)) std::cout << "CS was edited" << std::endl;
				else std::cout << "There is no CS with that id" << std::endl;
			}
			break;
		}
		case 9:
		{
			if (network.get_pipes_size() != 0) network.filter_pipes();
			else std::cout << "There are no Pipes" << std::endl;
			break;
		}
		case 10:
		{
			if (network.get_compr_stations_size() != 0)	network.filter_compr_stations();
			else std::cout << "There are no CS" << std::endl;
			break;
		}
		case 11:
		{
			network.top_sort();
			break;
		}
		case 12:
		{
			network.shortest_path();
			break;
		}
		case 13:
		{
			network.get_max_flow();
			break;
		}
		case 14:
		{
			std::string name;
			std::cout << "Input name of file for saving: ";
			std::cin >> name;
			if (network.to_file(name)) std::cout << "Data was saved" << std::endl;
			else std::cout << "Data was not saved" << std::endl;
			break;
		}
		case 15:
		{
			std::string name;
			std::cout << "Input name of file for loading: ";
			std::cin >> name;
			if (network.from_file(name)) std::cout << "Data was loaded" << std::endl;
			else std::cout << "There is no file with that name" << std::endl;
			break;
		}
		case 0:
		{
			std::cout << "Goodbye\n";
			return 0;
		}
		default:
		{
			std::cout << "Invalid choice\n";
			break;
		}
		}
	}
}

void show_commands() {
	std::cout << "1.Add a pipe" << std::endl
		<< "2.Add a CS" << std::endl
		<< "3.Add a edge" << std::endl
		<< "4.View all objects" << std::endl
		<< "5.Delete single pipe" << std::endl
		<< "6.Delete single CS" << std::endl
		<< "7.Edit single pipe" << std::endl
		<< "8.Edit single CS" << std::endl
		<< "9.Filter pipes" << std::endl
		<< "10.Filter CS" << std::endl
		<< "11.Topological sort network" << std::endl
		<< "12.Shortest paths" << std::endl
		<< "13.Max flow" << std::endl
		<< "14.Save" << std::endl
		<< "15.Load" << std::endl
		<< "0.Exit" << std::endl;
}