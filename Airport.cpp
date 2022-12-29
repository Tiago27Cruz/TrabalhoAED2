//
// Created by Tiago Cruz on 27/12/2022.
//

#include "Airport.h"
#include <string>
#include <cmath>
#include <iostream>
Airport::Airport() {
    this->code = "";
}

Airport::Airport(std::string code) {
    this->code = code;
}

Airport::Airport(string code, string name, string city, string country, float latitude, float longitude){
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}

void Airport::AddFlight(Flight flight) {
    flights.push_back(flight);
}
void Airport::AddPath(Airport airport) {
    for(vector<Airport> v : path){
        v.push_back(airport);
    }
}
void Airport::AddBestPath(Airport airport){
    best_path.push_back(airport);
}
void Airport::AddBranch(vector<vector<Airport>> path, vector<Airport> best_path, Airport airport){
    for(vector<Airport> v : path) {
        v.push_back(airport);
        this->path.push_back(v);
    }
    best_path.push_back(airport);
    this->path.push_back(best_path);
}
void Airport::AddBranch(vector<vector<Airport>> path, Airport airport){
    for(vector<Airport> v : path) {
        v.push_back(airport);
        this->path.push_back(v);
    }
}
void Airport::change_best_path(){
    path.push_back(best_path);
}
void Airport::PathClear() {
    path.clear();
    best_path.clear();
}

void Airport::setVisit(bool state) {
    visited = state;
}
void Airport::setDistance(int distance) {
    this->distance = distance;
}
double Airport::calculateDistance(double lat1, double lon1, double lat2, double lon2){
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}
void Airport::print_distance() {
    cout << distance << '\n';
}
void Airport::print_bestpath(){
    for(int i = 0; i<best_path.size(); i++) {
        cout << best_path[i].getCode() << " ";
    }
    cout << '\n';
}
void Airport::print_flightnr(){
    cout << flight_nr << '\n';
}


