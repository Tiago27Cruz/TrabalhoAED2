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
#include <unordered_set>
#include <stack>
#include <string.h>
#include "Estatisticas.h"

using namespace std;
class Graph {
    struct Airline{
        string code;
        string name;
        string callsign;
        string country;
        int starting_airport = 0;
    };
    struct Flight{
        string source;
        string target;
        unordered_set<string> flight_airline;
        bool visited;
    };

    struct Airport{
        string code;
        string name;
        string city;
        string country;
        double latitude;
        double longitude;
        double distance;
        int flight_nr;
        list<vector<string>> path;
        unordered_map<string, Flight> flights;
        bool visited;
        bool in_stack;
        bool is_articulation;
        int num;
        int low;
    };
    typedef unordered_map<string, Airport> unMap;
    typedef unordered_map<string, Airline> unAir;
    //typedef unordered_map<string, vector<string>, CityHash, CityHash> ciMap;
    int n; // Graph size (vertices are numbered from 1 to n)
    unMap airports;     // The list of airports being represented
    unAir airlines;
    int total_flights;
    int destination_count;
    unordered_set<string> different_airlines;
    unordered_set<string> different_countries;
    unordered_set<string> different_cities;
    //ciMap cities;
    Estatisticas stats;
public:
    Graph(int nodes);
    vector<Airport> best_flight(string src, string target);
    void addFlight(string src, string target, string airline);
    unMap get_airports() {return airports;};
    unAir get_airlines() {return airlines;};

    void dfs(string src, int max);
    void dfs_by_best_airline(string src, string target, string origin, vector<string> res, unordered_set<string> temp);
    void dfs_normal(string src, int max);
    void dfs_articulation(Airport& airport, stack<Airport*>& node_stack, list<Airport>* res, int index);
    void dfs_specificArticulation(Airport& airport, stack<Airport*>& airport_stack, list<Airport> *res, int index, unordered_set<string> airlines);

    void AddBestPath(Airport& airport);
    double calculateDistance(double lat1, double lon1, double lat2, double lon2);
    void AddBranch(list<vector<string>> path, vector<string> best_path, Airport& airport);
    void AddBranch(list<vector<string>> path, Airport& airport);
    void AddPath(Airport& airport);

    void bfs(string src, string target);
    void bfs(string src, string target, unordered_set<string> airlines);
    void bfs_bycity(string city, string target);
    void bfs_bycity(string city, string target, unordered_set<string> airlines);
    void dfs_minimum_airlines(string src, string target);
    void bfs_bycords(double latitude, double longitude, double distance, string target);
    void bfs_bycords(double latitude, double longitude, double distance, string target, unordered_set<string> airlines);



    void insertAirports();
    void insertFlights();
    void insertAirline();

    void print_totalArticulationPoints();
    void print_specificArticulationPoints(unordered_set<string> airlines);

    void print_typeInCountry(string Country, string type);
    void print_typeInCity(string City, string type);
    void print_typeByAirline(string airline, string type);
    void print_nCountriesAirline(string airline);
    void print_nAirportsAirline(string airline);

    void print_bestDistance(Airport airport);
    void print_bestDistance(string src, string target);
    void print_bestPath(Airport airport);
    void print_bestPath(string src, string target);
    void print_bestPath(string src, string target, unordered_set<string> airlines);
    void print_bestCityPath(string src, string target);
    void print_bestCityPath(string src, string target, unordered_set<string> airlines);
    void print_bestCordPath(double latitude, double longitude, double distance, string target);
    void print_bestCordPath(double latitude, double longitude, double distance, string target, unordered_set<string> airlines);
    void print_flightnr(Airport airport);
    void print_bestflightnr(string src, string target);
    void print_bestflightnr(string src, string target, unordered_set<string> airlines);
    void print_all_flights(string src);
    void print_all_different_airlines(string src);
    void print_all_different_destinies(string src);
    void print_all_different_countries(string src);
    void print_all_different_cities(string src);
    void print_all_airport_information(string src);
    void print_all_airport_information_in_range(string src, int max);
    void printAll(string src, string target);
    void printAll(string src, string target, unordered_set<string> airlines);

    string find_code(string name);
    bool isValidCity(string city);
    bool isValidCountry(string country);
};

#endif //TRABALHO_AED2_GRAPH_H
