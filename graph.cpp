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

/*void Graph::dfs(int v) {
    // show node order
    // cout << v << " ";
    airports[v].setVisit(true);
    for (auto e : airports[v].getFlights()) {
        string target = e.getTarget();
        int w = e.target;
        if (!airports[w].wasVisited())
            dfs(w);
    }
}

void Graph::bfs(int v) {
    for (int i=1; i<=n; i++){
        airports[i].setVisit(false);
    }
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    airports[v].setVisit(true);
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        // show node order
        //cout << u << " ";
        for (auto e : airports[u].getFlights()) {
            int w = e.target;
            if (!airports[w].wasVisited()) {
                q.push(w);
                airports[w].setVisit(true);
            }
        }
    }
}*/

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