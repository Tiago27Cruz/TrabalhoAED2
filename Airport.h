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
    float latitude;
    float longitude;
    list<Flight> flights;
    bool visited;

public:
    Airport(string code);
    Airport(string code, string name, string city, string country, float latitude, float longitude);
    string getCode() const {return code;};
    list<Flight> getFlights() const {return flights;};
    bool wasVisited() const {return visited;};
    void setVisit(bool state);
    void AddFlight(Flight flight);
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
