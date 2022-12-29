//
// Created by Tiago Cruz on 27/12/2022.
//

#ifndef TRABALHO_AED2_AEROPORTO_H
#define TRABALHO_AED2_AEROPORTO_H

#include "flight.h"
#include <string>
#include <list>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Airport{
    string code;
    string name;
    string city;
    string country;
    double latitude;
    double longitude;
    double distance;
    int flight_nr;
    vector<vector<Airport>> path;
    vector<Airport> best_path;
    list<Flight> flights;
    bool visited;

public:
    Airport();
    Airport(string code);
    Airport(string code, string name, string city, string country, float latitude, float longitude);
    string getCode() const {return code;};
    string getCity() const {return city;};
    list<Flight>& getFlights() {return flights;};
    double get_latitude()const{return latitude;}
    double get_longitude()const{return longitude;}
    double get_distance()const{return distance;}
    int get_flight_nr()const{return flight_nr;}
    vector<vector<Airport>> get_path()const{return path;}
    vector<Airport> get_best_path()const{return best_path;}
    bool wasVisited() const {return visited;};
    void setVisit(bool state);
    void setDistance(int distance);
    void setFlightnr(int flight_nr){this->flight_nr = flight_nr;}
    void setPath(vector<vector<Airport>> path){this->path = path;}
    void setBestPath(vector<Airport> best_path){this->best_path = best_path;}
    void change_best_path();
    double calculateDistance(double lat1, double lon1, double lat2, double lon2);
    void AddFlight(Flight flight);
    void AddPath(Airport airport);
    void AddBestPath(Airport airport);
    void AddBranch(vector<vector<Airport>> path, vector<Airport> best_path, Airport airport);
    void AddBranch(vector<vector<Airport>> path, Airport airport);
    void PathClear();
    void print_distance();
    void print_bestpath();
    void print_flightnr();
};



struct AirportHash
{
    int operator() (const Airport &a) const {
        return 0;
    }
    bool operator()(const Airport &a1, const Airport &a2)const{
        return (a1.getCode() == a2.getCode());
    }
};
struct CityHash
{
    int operator() (const Airport &a) const {
        return 0;
    }
    bool operator()(const Airport &a1, const Airport &a2)const{
        return (a1.getCity() == a2.getCity());
    }
};


typedef unordered_map<string, Airport, AirportHash, AirportHash> unMap;
typedef unordered_map<string, vector<string>, CityHash, CityHash> ciMap;
#endif //TRABALHO_AED2_AEROPORTO_H
