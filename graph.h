//
// Created by Tiago Cruz on 27/12/2022.
//

#ifndef TRABALHO_AED2_GRAPH_H
#define TRABALHO_AED2_GRAPH_H

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include "Airport.h"
#include <stack>
#include <string.h>

using namespace std;

class Graph {
    int n;              // Graph size (vertices are numbered from 1 to n)
    unMap airports;     // The list of airports being represented
    //ciMap cities;
public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes);
    vector<Airport> best_flight(string src, string target);
    // Add edge from source to destination with a certain weight
    void addFlight(string src, string target, string airline);
    // Depth-First Search: example implementation
    int dfs(string src);

    // Breadth-First Search: example implementation
    void bfs(string src, string target);
    void bfs(string src, string target, unordered_set<string> airlines);
    void bfs_bycity(string city, string target);
    void bfs_bycity(string city, string target, unordered_set<string> airlines);
    void bfs_bycords(double latitude, double longitude, double distance, string target);
    void bfs_bycords(double latitude, double longitude, double distance, string target, unordered_set<string> airlines);

    void insertAirports();
    void insertFlights();
    void print_bestdistance(string src, string target);
    void print_bestpath(string src, string target);
    void print_bestcitypath(string src, string target);
    void print_bestcordpath(double latitude, double longitude, double distance, string target);
    void print_bestflightnr(string src, string target);
    void print_all_flights(string src);
    void printAll(string src, string target);
    void printAll(string src, string target, unordered_set<string> airlines);
};

#endif //TRABALHO_AED2_GRAPH_H
