//
// Created by Tiago Cruz on 27/12/2022.
//

#include <fstream>
#include <sstream>
#include "graph.h"

Graph::Graph(int num) : n(num) {}


void Graph::addFlight(string src, string target, string airline){
    Flight flight = Flight(src, target, airline);

    Airport& airport = airports[src];
    airport.AddFlight(flight);
}
vector<Airport> Graph::best_flight(string src, string target){
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        airport.setVisit(false);
    }
    dfs(src);
}

int Graph::dfs(string src) {

    Airport& airport = airports[src];
    airport.setVisit(true);
    int size = 1;
    for (auto e : airport.getFlights()) {
        string wTarget = e.getTarget();
        Airport& w = airports[wTarget];
        if (!w.wasVisited())
            size += dfs(wTarget);
    }
    return size;
}

void Graph::bfs(string src) {
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        for(auto e : airport.getFlights()){
            e.setVisit(false);
        }
        airport.setVisit(false);
        airport.setDistance(-1.0);
    }

    queue<Airport> q;
    Airport& airport = airports[src];

    airport.setDistance(0.0);
    airport.setFlightnr(0);
    airport.PathClear();
    airport.setVisit(true);
    q.push(airport);
    while (!q.empty()) {
        Airport u = q.front();
        q.pop();
        for (auto e : u.getFlights()) {
            string wTarget = e.getTarget();
            Airport& w = airports[wTarget];
            double distance = w.calculateDistance(u.get_latitude(), u.get_longitude(), w.get_latitude(), w.get_longitude()) + u.get_distance();
            if(w.get_distance() < distance) {
                w.setDistance(distance);
                w.setPath(u.get_path());
                w.AddPath(w);
                w.setFlightnr(u.get_flight_nr() + 1);
            }
            if (!e.wasVisited()) {
                q.push(w);
                e.setVisit(true);
            }
        }
    }
}
void Graph::print_distance(string src, string target){
    bfs(src);
    Airport& airport = airports[target];
    airport.print_distance();
}

void Graph::insertAirports() {
    ifstream fout;
    string file = "../airports.csv";
    fout.open(file);
    string temp, Code, Name, City, Country, tempLatitude, tempLongitude;
    getline(fout, temp);
    while(getline(fout, temp)){
        stringstream itStream(temp);
        getline(itStream, Code, ',');
        getline(itStream, Name, ',');
        getline(itStream, City, ',');
        getline(itStream, Country, ',');
        getline(itStream, tempLatitude, ',');
        getline(itStream, tempLongitude, '\r');

        float latitude = stof(tempLatitude);
        float longitude = stof(tempLongitude);

        Airport airport = Airport(Code, Name, City, Country, latitude, longitude);
        airports.insert(pair<string, Airport>(Code, airport));

    }
}

void Graph::insertFlights(){
    ifstream fout;
    string file = "../flights.csv";
    fout.open(file);
    string temp, source, target, airline;
    getline(fout, temp);
    while(getline(fout, temp)){
        stringstream itStream(temp);
        getline(itStream, source, ',');
        getline(itStream, target, ',');
        getline(itStream, airline, ',');
        addFlight(source, target, airline);
    }
}