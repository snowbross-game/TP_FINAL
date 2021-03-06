#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include<queue>
#include <climits>
#include "general.h"

using namespace std;

class MapDijkstraMachine
{
public:
	MapDijkstraMachine(unsigned int n_rows, unsigned int n_cols);
	~MapDijkstraMachine();
	Position get_next_movement_shortest_path(int source_x, int source_y, int destination_x, int destination_y);
	void load_on_machine(const char* map_string);
private:
/*
	static const int sz = 10001; //Maximum possible number of vertices. Preallocating space for DataStructures accordingly
	vector<pair<int, int> > a[sz]; //Adjacency list
	int dis[sz]; //Stores shortest distance
	bool vis[sz] = { 0 }; //Determines whether the node has been visited or not
*/
	void run_algorithm(int source_x, int source_y);


	int n_vertices;
	int n_edges;

	int rows; 
	int cols;

	// The output array. dist[i] will hold the shortest distance from src to i 
	int *dist;

	// sptSet[i] will true if vertex  i is included / in shortest path tree or shortest distance from src to i is finalized 
	bool *sptSet;

	// Parent array to store shortest path tree 
	int *parent;

	void form_path_to_vertex(int destination);
	
	int minDistance();
	int **graph;

	std::queue<int> shortest_path;

	void build_graph(const char * map_string);

};

