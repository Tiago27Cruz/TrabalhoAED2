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
/*int Graph::dfs(string src) {

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
}*/

void Graph::bfs(string src) {
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        airport.setVisit(false);
        airport.setDistance(-1.0);
        airport.setFlightnr(-1);
        airport.PathClear();
    }

    queue<Airport> q;
    Airport& airport = airports[src];

    airport.setDistance(0.0);
    airport.setFlightnr(0);
    airport.PathClear();
    airport.AddBestPath(airport);
    airport.setVisit(true);
    q.push(airport);
    while (!q.empty()) {
        Airport u = q.front();
        q.pop();
        for (Flight &e : u.getFlights()) {
            string wTarget = e.getTarget();
            Airport &w = airports[wTarget];
            double distance = w.calculateDistance(u.get_latitude(), u.get_longitude(), w.get_latitude(), w.get_longitude()) + u.get_distance();
            int flight_nr = u.get_flight_nr() + 1;
            if (w.get_flight_nr() >= flight_nr || w.get_flight_nr() <= 0) {
                if (w.get_flight_nr() == flight_nr) {
                    if(w.get_distance() > distance){
                        w.change_best_path();
                        w.setBestPath(u.get_best_path());
                        w.AddBestPath(w);
                        w.AddBranch(u.get_path(), w);
                        w.setDistance(distance);
                        w.setFlightnr(flight_nr);
                    }
                    else{
                        w.AddBranch(u.get_path(), u.get_best_path(), w);
                    }
                }
                else if(w.get_flight_nr() != flight_nr){
                    w.setDistance(distance);
                    w.setBestPath(u.get_best_path());
                    w.AddBestPath(w);
                    w.setPath(u.get_path());
                    w.AddPath(w);
                    w.setFlightnr(flight_nr);
                }
            }
            if (!w.wasVisited()) {
                q.push(w);
                w.setVisit(true);
            }
        }
    }
}
void Graph::print_distance_bycity(string city, string target) {
    vector<string> &city_airports = cities[city];
    for(string code : city_airports){
        cout << code << '\n';
        /*print_distance(code, target);
        print_bestpath(code, target);
        print_flightnr(code, target);*/
    }
}
void Graph::print_distance(string src, string target){
    bfs(src);
    Airport& airport = airports[target];
    airport.print_distance();
}
void Graph::print_bestpath(string src, string target){
    bfs(src);
    Airport &airport = airports[target];
    airport.print_bestpath();
}
void Graph::print_flightnr(string src, string target){
    bfs(src);
    Airport &airport = airports[target];
    airport.print_flightnr();
}

void Graph::insertAirports() {
    ifstream fout;
    string file = "../tempAirport.csv";
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
        vector<string> &city_data = cities[City];
        city_data.push_back(Code);

    }
}

void Graph::insertFlights(){
    ifstream fout;
    string file = "../tempFlight.csv";
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