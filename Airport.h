//
// Created by Tiago Cruz on 27/12/2022.
//

#ifndef TRABALHO_AED2_AEROPORTO_H
#define TRABALHO_AED2_AEROPORTO_H

#include "flight.h"
#include <string>
#include <list>
#include <unordered_set>

using namespace std;

class Airport{
    string code;
    string name;
    string city;
    string country;
    double latitude;
    double longitude;
    double distance;
    list<Flight> flights;
    bool visited;

public:
    Airport(string code);
    Airport(string code, string name, string city, string country, float latitude, float longitude);
    string getCode() const {return code;};
    list<Flight> getFlights() const {return flights;};
    double get_latitude()const{return latitude;}
    double get_longitude()const{return longitude;}
    double get_distance()const{return distance;}
    bool wasVisited() const {return visited;};
    void setVisit(bool state);
    void setDistance(int distance);
    double calculateDistance(double lat1, double lon1, double lat2, double lon2);
    void AddFlight(Flight flight);
    void print_distance();
};

struct airportHash
{
    int operator() (const Airport &a) const {
        return 0;
    }
    bool operator()(const Airport &a1, const Airport &a2)const{
        return (a1.getCode() == a2.getCode());
    }
};

typedef unordered_set<Airport, airportHash, airportHash> tabHAirport;

#endif //TRABALHO_AED2_AEROPORTO_H
