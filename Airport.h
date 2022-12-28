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
    vector<Airport> path;
    list<Flight> flights;
    bool visited;

public:
    Airport();
    Airport(string code);
    Airport(string code, string name, string city, string country, float latitude, float longitude);
    string getCode() const {return code;};
    list<Flight> getFlights() const {return flights;};
    double get_latitude()const{return latitude;}
    double get_longitude()const{return longitude;}
    double get_distance()const{return distance;}
    int get_flight_nr()const{return flight_nr;}
    vector<Airport> get_path()const{return path;}
    bool wasVisited() const {return visited;};
    void setVisit(bool state);
    void setDistance(int distance);
    void setFlightnr(int flight_nr){this->flight_nr = flight_nr;}
    void setPath(vector<Airport> path){this->path = path;}
    double calculateDistance(double lat1, double lon1, double lat2, double lon2);
    void AddFlight(Flight flight);
    void AddPath(Airport airport);
    void PathClear();
    void print_distance();
};

/*namespace std{
    template<>
    struct hash<Airport>
    {
        size_t operator()(const Airport &key)
        {
            return hash<string>()(key.getCode());
        }
    };
}
 typedef unordered_map<string, Airport>;
 */
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

struct AirportHash
{
    int operator() (const Airport &a) const {
        return 0;
    }
    bool operator()(const Airport &a1, const Airport &a2)const{
        return (a1.getCode() == a2.getCode());
    }
};

typedef unordered_map<string, Airport, AirportHash, AirportHash> tabHairport;

typedef unordered_map<string, Airport, AirportHash, AirportHash> unMap;
#endif //TRABALHO_AED2_AEROPORTO_H
