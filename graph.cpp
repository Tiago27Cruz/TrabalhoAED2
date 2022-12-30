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

void Graph::bfs(string src, string target) {
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        airport.setVisit(false);
        airport.setDistance(-1.0);
        airport.setFlightnr(-1);
        airport.PathClear();
    }

    queue<Airport*> q;
    Airport& airport = airports[src];

    airport.setDistance(0.0);
    airport.setFlightnr(0);
    airport.PathClear();
    airport.AddBestPath(airport.getCode());
    airport.setVisit(true);
    q.push(&airport);

    while (!q.empty()) {
        Airport u = *q.front();
        q.pop();
        if (u.getCode() == target)
            break;
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
                        w.AddBestPath(w.getCode());

                        w.AddBranch(u.get_path(), w.getCode());
                        w.setDistance(distance);
                        w.setFlightnr(flight_nr);
                    }
                    else if (w.get_distance() != distance) {
                        w.AddBranch(u.get_path(), u.get_best_path(), w.getCode());
                    }
                }
                else{
                    w.setDistance(distance);

                    w.setBestPath(u.get_best_path());
                    w.AddBestPath(w.getCode());

                    w.setPath(u.get_path());
                    w.AddPath(w.getCode());
                    w.setFlightnr(flight_nr);
                }
            }
            if (!w.wasVisited()) {
                q.push(&w);
                w.setVisit(true);
            }
        }
    }
}
void Graph::bfs(string src, string target, string airline) {
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        airport.setVisit(false);
        airport.setDistance(-1.0);
        airport.setFlightnr(-1);
        airport.PathClear();
    }

    queue<Airport*> q;
    Airport& airport = airports[src];

    airport.setDistance(0.0);
    airport.setFlightnr(0);
    airport.PathClear();
    airport.AddBestPath(airport.getCode());
    airport.setVisit(true);
    q.push(&airport);

    while (!q.empty()) {
        Airport u = *q.front();
        q.pop();
        if (u.getCode() == target)
            break;
        for (Flight &e : u.getFlights()) {
            string wTarget = e.getTarget();
            Airport &w = airports[wTarget];
            double distance = w.calculateDistance(u.get_latitude(), u.get_longitude(), w.get_latitude(), w.get_longitude()) + u.get_distance();
            int flight_nr = u.get_flight_nr() + 1;
            if ((w.get_flight_nr() >= flight_nr || w.get_flight_nr() <= 0) && (e.getAirline() == airline)) {
                if (w.get_flight_nr() == flight_nr) {
                    if(w.get_distance() > distance){
                        w.change_best_path();
                        w.setBestPath(u.get_best_path());
                        w.AddBestPath(w.getCode());

                        w.AddBranch(u.get_path(), w.getCode());
                        w.setDistance(distance);
                        w.setFlightnr(flight_nr);
                    }
                    else if (w.get_distance() != distance) {
                        w.AddBranch(u.get_path(), u.get_best_path(), w.getCode());
                    }
                }
                else{
                    w.setDistance(distance);

                    w.setBestPath(u.get_best_path());
                    w.AddBestPath(w.getCode());

                    w.setPath(u.get_path());
                    w.AddPath(w.getCode());
                    w.setFlightnr(flight_nr);
                }
            }
            if (!w.wasVisited()) {
                q.push(&w);
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
void Graph::print_by_cords(double latitude, double longitude, double distance, string target){
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        double d = airport.calculateDistance(latitude, longitude, airport.get_latitude(), airport.get_longitude());
        if(d < distance){
            printAll(airport.getCode(), target);
        }
    }
}
void Graph::print_bestdistance(string src, string target){
    bfs(src, target);
    Airport& airport = airports[target];
    airport.print_bestdistance();
}
void Graph::print_bestpath(string src, string target){
    bfs(src, target);
    Airport &airport = airports[target];
    airport.print_bestpath();
}
void Graph::print_bestpaths(string src, string target){
    bfs(src, target);
    Airport &airport = airports[target];
    airport.print_bestpaths();
}
void Graph::print_bestflightnr(string src, string target){
    bfs(src, target);
    Airport &airport = airports[target];
    airport.print_flightnr();
}
void Graph::printAll(string src, string target){
    bfs(src, target);
    Airport &airport = airports[target];
    cout << "From " << src << " to " << target << ":\n";
    airport.print_bestpaths();
    airport.print_bestpath();
    airport.print_flightnr();
    airport.print_bestdistance();
    cout << '\n';
}
void Graph::printAll(string src, string target, stack<string> airlines){
    while(!airlines.empty()) {
        bfs(src, target, airlines.top());
        Airport &airport = airports[target];
        cout << "From " << src << " to " << target << ", travelling by " << airlines.top() << ":\n";
        airport.print_bestpaths();
        airport.print_bestpath();
        airport.print_flightnr();
        airport.print_bestdistance();
        cout << '\n';
    }
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
        vector<string> &city_data = cities[City];
        city_data.push_back(Code);

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