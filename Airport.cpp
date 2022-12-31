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
void Airport::AddPath(string code) {
    for(vector<string> &v : path){
        v.push_back(code);
    }
}
void Airport::AddBestPath(string code){
    best_path.push_back(code);
}
void Airport::AddBranch(vector<vector<string>> path, vector<string> best_path, string code){
    for(vector<string> v : path) {
        v.push_back(code);
        this->path.push_back(v);
    }
    best_path.push_back(code);
    this->path.push_back(best_path);
}
void Airport::AddBranch(vector<vector<string>> path, string code){
    for(vector<string> v : path) {
        v.push_back(code);
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
void Airport::setDistance(double distance) {
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
void Airport::print_bestdistance() {
    cout << "The Bestpath distance is : " << distance << '\n';
}
void Airport::print_bestpath(){
    cout << "Possible paths :\n";
    for(vector<vector<string>>::iterator iter=path.begin(); iter!=path.end(); ++iter) {
        for (int j = 0; j<iter->size(); j++) {
            if(j!=0) cout << " -> ";
            cout << iter->at(j);
        }
        cout << '\n';
    }
    cout << "The shortest path is :\n";
    for(int i = 0; i<best_path.size(); i++) {
        if(i != 0) cout << " -> ";
        cout << best_path[i];
    }
    cout << '\n';
}

void Airport::print_flightnr(){
    cout << "The Bestpath flight number is : " << flight_nr << '\n';
}


