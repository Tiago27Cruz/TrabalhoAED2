//
// Created by Tiago Cruz on 27/12/2022.
//

#ifndef TRABALHO_AED2_AEROPORTO_H
#define TRABALHO_AED2_AEROPORTO_H

#include "flight.h"
#include <string>
#include <list>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;
struct VectorHash
{
    int operator() (const vector<string> &a) const {
        return 0;
    }
    bool operator()(const vector<string> &a1, const vector<string> &a2)const{
        return (a1 == a2);
    }
};
typedef unordered_set<vector<string>, VectorHash, VectorHash> unSet;

class Airport{
    string code;
    string name;
    string city;
    string country;
    double latitude;
    double longitude;
    double distance;
    int flight_nr;
    int total_flight_nr;
    vector<vector<string>> path;
    vector<string> best_path;
    list<Flight> flights;
    bool visited;

public:
    Airport();
    Airport(string code);
    Airport(string code, string name, string city, string country, float latitude, float longitude);
    string getCode() const {return code;};
    string getCountry() const {return country;};
    string getCity() const {return city;};
    list<Flight>& getFlights() {return flights;};
    double get_latitude()const{return latitude;}
    double get_longitude()const{return longitude;}
    double get_distance()const{return distance;}
    int get_flight_nr()const{return flight_nr;}
    int get_total_flight_nr()const{return total_flight_nr;}
    vector<vector<string>> get_path()const{return path;}
    vector<string> get_best_path()const{return best_path;}
    bool wasVisited() const {return visited;};
    void setVisit(bool state);
    void setDistance(double distance);
    void set_total_flight_number(int total_flight_number){this->total_flight_nr = total_flight_number;}
    void setFlightnr(int flight_nr){this->flight_nr = flight_nr;}
    void setPath(vector<vector<string>> path){this->path = path;}
    void setBestPath(vector<string> best_path){this->best_path = best_path;}
    void change_best_path();
    double calculateDistance(double lat1, double lon1, double lat2, double lon2);
    void AddFlight(Flight flight);
    void AddPath(string code);
    void AddBestPath(string code);
    void AddBranch(vector<vector<string>> path, vector<string> best_path, string code);
    void AddBranch(vector<vector<string>> path, string code);
    void PathClear();
    void print_bestdistance();
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
