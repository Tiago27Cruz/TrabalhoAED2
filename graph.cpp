//
// Created by Tiago Cruz on 27/12/2022.
//

#include <fstream>
#include <sstream>
#include "graph.h"

Graph::Graph(int num) : n(num) {
}
void Graph::addFlight(string src, string target, string airline){
    Flight flight = Flight(src, target, airline);

    Airport airport = Airport(src);
    airport = *airports.find(airport);

    airports.erase(airport);
    airport.AddFlight(flight);
    airports.insert(airport);
}
vector<Airport> Graph::best_flight(string src, string target){

}

void Graph::dfs(string src) {
    // show node order
    // cout << v << " ";
    for (tabHAirport::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport airport = *iter;
        airports.erase(airport);
        airport.setVisit(false);
        airports.insert(airport);
    }

    Airport airport = Airport(src);
    airport = *airports.find(airport);

    airports.erase(airport);
    airport.setVisit(true);
    airports.insert(airport);

    for (auto e : airport.getFlights()) {
        string wTarget = e.getTarget();
        Airport w = Airport(wTarget);
        w = *airports.find(w);
        if (!w.wasVisited())
            dfs(wTarget);
    }
}

void Graph::bfs(string src) {
    for (tabHAirport::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport airport = *iter;
        airports.erase(airport);
        airport.setVisit(false);
        airports.insert(airport);
    }

    queue<Airport> q;
    Airport airport = Airport(src);
    airport = *airports.find(airport);

    airports.erase(airport);
    airport.setDistance(0.0);
    airport.setVisit(true);
    airports.insert(airport);

    q.push(airport);
    while (!q.empty()) {
        Airport u = q.front();
        q.pop();
        for (auto e : u.getFlights()) {
            string wTarget = e.getTarget();
            Airport w = Airport(wTarget);
            w = *airports.find(w);
            airports.erase(w);
            w.setDistance(w.calculateDistance(u.get_latitude(), u.get_longitude(), w.get_latitude(), w.get_longitude()) + u.get_distance());
            airports.insert(w);
            if (!w.wasVisited()) {
                q.push(w);
                w.setVisit(true);
            }
        }
    }
}
void Graph::print_distance(string src, string target){
    bfs(src);
    Airport airport = Airport(target);
    airport = *airports.find(airport);
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
        airports.insert(airport);

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