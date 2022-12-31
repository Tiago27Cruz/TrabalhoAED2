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
int Graph::dfs(string src) {

    Airport& airport = airports[src];
    airport.setVisit(true);
    int size = 0;
    for (Flight &e : airport.getFlights()) {
        string wTarget = e.getTarget();
        Airport& w = airports[wTarget];
        size++;
        if (!w.wasVisited())
            size += dfs(wTarget);
    }
    return size;
}

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
void Graph::bfs(string src, string target, unordered_set<string> airlines) {
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
            if(airlines.find(e.getAirline()) == airlines.end()){
                continue;
            }
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
void Graph::bfs_bycity(string city, string target) {
    double distance = -1.0;
    vector<string> best_path;
    vector<vector<string>> path;
    int flight_nr = -1;
    Airport &target_airport = airports[target];
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++) {
        Airport &airport = iter->second;
        if (airport.getCity() == city) {
            bfs(airport.getCode(), target);
            if ((target_airport.get_flight_nr() <= flight_nr || flight_nr == -1) && target_airport.get_flight_nr() != -1) {
                if (target_airport.get_flight_nr() == flight_nr) {
                    if (target_airport.get_distance() < distance) {
                        distance = target_airport.get_distance();
                        flight_nr = target_airport.get_flight_nr();
                        best_path = target_airport.get_best_path();
                    }
                    target_airport.change_best_path();
                    vector<vector<string>> res = target_airport.get_path();
                    for(int i = 0; i < res.size(); i++){
                        path.push_back(res[i]);
                    }
                } else {
                    distance = target_airport.get_distance();
                    flight_nr = target_airport.get_flight_nr();
                    best_path = target_airport.get_best_path();
                    target_airport.change_best_path();
                    path = target_airport.get_path();
                }
            }
        }
    }
    target_airport.setBestPath(best_path);
    target_airport.setPath(path);
    target_airport.setFlightnr(flight_nr);
    target_airport.setDistance(distance);
    /*
    cout << "From " << city << " to " << target << ":\n";
    for(int i = 0; i < path.size(); i++){
        for(int z = 0; z < path[i].size(); z++){
            if(z!=0) cout << " -> ";
            cout << path[i][z];
        }
        cout << '\n';
    }
    cout << "The Bestpath is :\n";
    for(int i = 0; i<best_path.size(); i++) {
        if(i != 0) cout << " -> ";
        cout << best_path[i];
    }
    cout << '\n';
    cout << "The Bestpath flight number is : " << flight_nr << '\n';
    cout << "The Bestpath distance is : " << distance << '\n';*/
}
void Graph::bfs_bycity(string city, string target, unordered_set<string> airlines) {
    double distance = -1.0;
    vector<string> best_path;
    vector<vector<string>> path;
    int flight_nr = -1;
    Airport &target_airport = airports[target];
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++) {
        Airport &airport = iter->second;
        if (airport.getCity() == city) {
            bfs(airport.getCode(), target, airlines);
            if ((target_airport.get_flight_nr() <= flight_nr || flight_nr == -1) &&
                target_airport.get_flight_nr() != -1) {
                if (target_airport.get_flight_nr() == flight_nr) {
                    if (target_airport.get_distance() < distance) {
                        distance = target_airport.get_distance();
                        flight_nr = target_airport.get_flight_nr();
                        best_path = target_airport.get_best_path();
                    }
                    target_airport.change_best_path();
                    vector<vector<string>> res = target_airport.get_path();
                    for (int i = 0; i < res.size(); i++) {
                        path.push_back(res[i]);
                    }
                } else {
                    distance = target_airport.get_distance();
                    flight_nr = target_airport.get_flight_nr();
                    best_path = target_airport.get_best_path();
                    target_airport.change_best_path();
                    path = target_airport.get_path();
                }
            }
        }
    }
    target_airport.setBestPath(best_path);
    target_airport.setPath(path);
    target_airport.setFlightnr(flight_nr);
    target_airport.setDistance(distance);
}

void Graph::bfs_bycords(double latitude, double longitude, double distance, string target){
    double dist = -1.0;
    vector<string> best_path;
    vector<vector<string>> path;
    int flight_nr = -1;
    Airport &target_airport = airports[target];
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        double d = airport.calculateDistance(latitude, longitude, airport.get_latitude(), airport.get_longitude());
        if(d < distance){
            bfs(airport.getCode(), target);
            if ((target_airport.get_flight_nr() <= flight_nr || flight_nr == -1) && target_airport.get_flight_nr() != -1) {
                if (target_airport.get_flight_nr() == flight_nr) {
                    if (target_airport.get_distance() < dist) {
                        dist = target_airport.get_distance();
                        flight_nr = target_airport.get_flight_nr();
                        best_path = target_airport.get_best_path();
                    }
                    target_airport.change_best_path();
                    vector<vector<string>> res = target_airport.get_path();
                    for(int i = 0; i < res.size(); i++){
                        path.push_back(res[i]);
                    }
                } else {
                    dist = target_airport.get_distance();
                    flight_nr = target_airport.get_flight_nr();
                    best_path = target_airport.get_best_path();
                    target_airport.change_best_path();
                    path = target_airport.get_path();
                }
            }
        }
    }
    target_airport.setBestPath(best_path);
    target_airport.setPath(path);
    target_airport.setFlightnr(flight_nr);
    target_airport.setDistance(distance);
    /*
    if(best_path.empty()){
        cout << "no flights to " << target << '\n';
    }
    else {
        cout << "From " << best_path[0] << " to " << target << ":\n";
        for (int i = 0; i < path.size(); i++) {
            for (int z = 0; z < path[i].size(); z++) {
                if (z != 0) cout << " -> ";
                cout << path[i][z];
            }
            cout << '\n';
        }
        cout << "The Bestpath is :\n";
        for (int i = 0; i < best_path.size(); i++) {
            if (i != 0) cout << " -> ";
            cout << best_path[i];
        }
        cout << '\n';
        cout << "The Bestpath flight number is : " << flight_nr << '\n';
        cout << "The Bestpath distance is : " << dist << '\n';
    }*/
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
void Graph::print_bestcitypath(string src, string target){
    bfs_bycity(src, target);
    Airport &airport = airports[target];
    airport.print_bestpath();
}
void Graph::print_bestcordpath(double latitude, double longitude, double distance, string target){
    bfs_bycords(latitude, longitude, distance, target);
    Airport &airport = airports[target];
    airport.print_bestpath();
}
void Graph::print_bestflightnr(string src, string target){
    bfs(src, target);
    Airport &airport = airports[target];
    airport.print_flightnr();
}
void Graph::print_all_flights(string src){
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        airport.setVisit(false);
    }
    cout << "All " << src << "flights: " << dfs(src) << '\n';
}
void Graph::printAll(string src, string target){
    bfs(src, target);
    Airport &airport = airports[target];
    cout << "From " << src << " to " << target << ":\n";
    airport.print_bestpath();
    airport.print_flightnr();
    airport.print_bestdistance();
    cout << '\n';
}
void Graph::printAll(string src, string target, unordered_set<string> airlines){
    bfs(src, target, airlines);
    Airport &airport = airports[target];
    cout << "From " << src << " to " << target << ", travelling by ";
    for (unordered_set<string>::iterator iter = airlines.begin(); iter != airlines.end(); iter++){
        if(iter != airlines.begin()) cout << ", ";
        cout << *iter;
    }
    cout << ":\n";
    airport.print_bestpath();
    airport.print_flightnr();
    airport.print_bestdistance();
    cout << '\n';
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

    /*void Graph::insertAirline() {
        ifstream fout;
        string file = "../airlines.csv";
        fout.open(file);
        string temp, code, name, callsign, country;
        getline(fout, temp);
        while(getline(fout, temp)) {
            stringstream itStream(temp);
            getline(itStream, code, ',');
            getline(itStream, name, ',');
            getline(itStream, callsign, ',');
            getline(itStream, country, ',');

        }*/
        }