//
// Created by Tiago Cruz on 27/12/2022.
//

#ifndef TRABALHO_AED2_GRAPH_H
#define TRABALHO_AED2_GRAPH_H

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include "Airport.h"
#include <string.h>

using namespace std;

class Graph {
    int n;              // Graph size (vertices are numbered from 1 to n)
    tabHAirport airports; // The list of airports being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes);

    // Add edge from source to destination with a certain weight
    void addFlight(string src, string target, string airline);

    // Depth-First Search: example implementation
    void dfs(int v);

    // Breadth-First Search: example implementation
    void bfs(int v);

    void insertAirports();
    void insertFlights();
};


#endif //TRABALHO_AED2_GRAPH_H
