#pragma once
#include <limits>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include "Pipe.h"
#include "Compr_station.h"
#include "Network.h"

#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
						std::cerr << str << std::endl

class redirect_output_wrapper
{
	std::ostream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}
	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};


template <typename T>
T get_num_value(T least, T great) {
	T val = 0;
	while (true) {
		if (std::cin >> val && (std::cin.peek() == EOF || std::cin.peek() == '\n') && (val >= least) && (val < great))
		{
			std::cerr << val << std::endl;
			return val;
		}
		else {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Please, input correct value: ";
		}
	}
}

bool bfs(const std::vector<std::vector<double>>& r_graph, int s, int t, std::vector<int>& parent);

double ford_fulkerson(std::vector<std::vector<double>>& graph, int s, int t);

bool pipe_in_rep_input();

bool check_pipe_name(const Pipe& Pp, std::string name);

bool check_pipe_in_rep(const Pipe& Pp, bool in_rep);

bool check_compr_st_name(const Compr_station& Cs, std::string name);

bool check_used_per(const Compr_station& Cs, double percent);

void topological_sort_util(int v, std::unordered_set<int>& visited,
	std::stack<int>& Stack,
	std::unordered_map<int, std::unordered_set<int>>& graph,
	std::unordered_set<int> gray);

std::stack<int> topoligical_sort(std::unordered_map<int, std::unordered_set<int>>& graph);

std::vector<double> dijkstra(std::vector<std::vector<double>> graph, int src);

int min_dist_node(const std::unordered_set<int>& spt_set, const std::vector<double>& dist);

double ford_fulkerson(std::vector<std::vector<std::vector<double>>> graph, int start, int end);

int get_max_vertex(int k, std::vector<std::vector<std::vector<double>>>& graph, std::unordered_set<int>& visited);
