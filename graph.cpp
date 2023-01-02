//
// Created by Tiago Cruz on 27/12/2022.
//

#include <fstream>
#include <sstream>
#include "graph.h"
#include <cmath>

Graph::Graph(int num) : n(num) {}

void Graph::AddBestPath(Airport& airport){
    vector<string> v = {airport.code};
    airport.path.push_back(v);
}
double Graph::calculateDistance(double lat1, double lon1, double lat2, double lon2){
    return 6371 * (2 * asin(sqrt((pow(sin(((lat2 - lat1) *
                                           M_PI / 180.0) / 2), 2) +
                                  pow(sin(((lon2 - lon1) *
                                           M_PI / 180.0) / 2), 2) *
                                  cos(((lat1) * M_PI / 180.0)) * cos(((lat2) * M_PI / 180.0))))));
}
void Graph::AddBranch(list<vector<string>> path, vector<string> best_path, Airport &airport){
    int count = 0;
    best_path.push_back(airport.code);
    airport.path.push_front(best_path);
    for(vector<string> v : path) {
        if(count != 0) {
            v.push_back(airport.code);
            airport.path.push_back(v);
        }
        count++;
    }
}
void Graph::AddBranch(list<vector<string>> path, Airport& airport){
    for(vector<string> v : path) {
        v.push_back(airport.code);
        airport.path.push_back(v);
    }
}
void Graph::AddPath(Airport& airport) {
    for(vector<string> &v : airport.path){
        v.push_back(airport.code);
    }
}
void Graph::dfs(string src, int max) {
    if(max == 0){
        return;
    }
    Airport& airport = airports[src];
    airport.visited = true;
    for (unordered_map<string, Flight>::iterator iter = airport.flights.begin(); iter != airport.flights.end(); iter++) {
        Flight& e = iter->second;
        string wTarget = e.target;
        Airport& w = airports[wTarget];
        /*if(different_airlines.find(e.source) == different_airlines.end()){
            different_airlines.insert(e.source);
        }*/
        total_flights++;
        if (!w.visited) {
            if (different_countries.find(w.country) == different_countries.end()) {
                different_countries.insert(w.country);
            }
            if(different_cities.find(w.city) == different_cities.end()){
                different_cities.insert(w.city);
            }
            destination_count++;
            dfs(wTarget, max-1);
        }
    }
}

void Graph::dfs_normal(string src, int max){
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        airport.visited = false;
    }
    destination_count = 0;
    total_flights = 0;
    different_countries.clear();
    different_airlines.clear();
    different_cities.clear();
    dfs(src, max);
}

void Graph::dfs_articulation(Airport& airport, stack<Airport> *airport_stack, list<Airport> *res, int index) {
    airport.visited = true;
    airport.low = index;
    airport.num = index;
    index++;
    airport.in_stack = true;
    airport_stack->push(airport);

    int count = 0;
    for (unordered_map<string, Flight>::iterator iter = airport.flights.begin(); iter != airport.flights.end(); iter++) {
        Flight& e = iter->second;
        string wTarget = e.target;
        Airport& w = airports[wTarget];
        if (!w.visited) {
            count++;
            dfs_articulation(w, airport_stack, res, index);
            airport.low = min(airport.low, w.low);
        }
        else if (w.in_stack) {
            airport.low = min(airport.low, w.num);
        }

        if (airport.num != 1 && !airport.is_articulation && w.low >= airport.num) {
            res->push_back(airport);
            airport.is_articulation = true;
        }
        else if (!airport.is_articulation && airport.num == 1 && count > 1) {
            res->push_back(airport);
            airport.is_articulation = true;
        }
    }
    //res->sort();
}

void Graph::bfs(string src, string target) {
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        airport.visited=false;
        airport.distance=-1.0;
        airport.flight_nr=-1;
    }

    queue<Airport*> q;
    Airport& airport = airports[src];

    airport.distance=0.0;
    airport.flight_nr=0;
    airport.path.clear();
    AddBestPath(airport);
    airport.visited=true;
    q.push(&airport);

    while (!q.empty()) {
        Airport u = *q.front();
        q.pop();
        if (u.code == target)
            break;
        for (unordered_map<string, Flight>::iterator iter = u.flights.begin(); iter != u.flights.end(); iter++) {
            Flight& e = iter->second;
            string wTarget = e.target;
            Airport &w = airports[wTarget];
            double distance = calculateDistance(u.latitude, u.longitude, w.latitude, w.longitude) + u.distance;
            int flight_nr = u.flight_nr + 1;
            if (w.flight_nr >= flight_nr || w.flight_nr <= 0) {
                if (w.flight_nr == flight_nr) {
                    if(w.distance > distance){
                        AddBranch(u.path, u.path.front(), w);
                        w.distance=distance;
                        w.flight_nr=flight_nr;
                    }
                    else if (w.distance != distance) {
                        AddBranch(u.path, w);
                    }
                }
                else{
                    w.distance=distance;
                    w.path=u.path;
                    AddPath(w);
                    w.flight_nr=flight_nr;
                }
            }
            if (!w.visited) {
                q.push(&w);
                w.visited = true;
            }
        }
    }
}
void Graph::bfs(string src, string target, unordered_set<string> airlines) {
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        airport.visited=false;
        airport.distance=-1.0;
        airport.flight_nr=-1;
        airport.path.clear();
    }

    queue<Airport*> q;
    Airport& airport = airports[src];

    airport.distance=0.0;
    airport.flight_nr=0;
    airport.path.clear();
    AddBestPath(airport);
    airport.visited = true;
    q.push(&airport);

    while (!q.empty()) {
        Airport u = *q.front();
        q.pop();
        if (u.code == target)
            break;
        for (unordered_map<string, Flight>::iterator iter = u.flights.begin(); iter != u.flights.end(); iter++) {
            Flight& e = iter->second;
            string wTarget = e.target;
            Airport &w = airports[wTarget];
            /*if(airlines.find(e.airline) == airlines.end()){
                continue;
            }*/
            double distance = calculateDistance(u.latitude, u.longitude, w.latitude, w.longitude) + u.distance;
            int flight_nr = u.flight_nr + 1;
            if (w.flight_nr >= flight_nr || w.flight_nr <= 0) {
                if (w.flight_nr == flight_nr) {
                    if(w.distance > distance){
                        AddBranch(u.path, u.path.front(), w);
                        w.distance=distance;
                        w.flight_nr=flight_nr;
                    }
                    else if (w.distance != distance) {
                        AddBranch(u.path, w);
                    }
                }
                else{
                    w.distance=distance;
                    w.path = u.path;
                    AddPath(w);
                    w.flight_nr=flight_nr;
                }
            }
            if (!w.visited) {
                q.push(&w);
                w.visited = true;
            }
        }
    }
}
void Graph::bfs_bycity(string city, string target) {
    double distance = -1.0;
    list<vector<string>> path;
    int flight_nr = -1;
    Airport &target_airport = airports[target];
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++) {
        Airport &airport = iter->second;
        if (airport.city == city) {
            bfs(airport.code, target);
            if ((target_airport.flight_nr <= flight_nr || flight_nr == -1) && target_airport.flight_nr != -1) {
                if (target_airport.flight_nr == flight_nr) {
                    if (target_airport.distance < distance) {
                        distance = target_airport.distance;
                        flight_nr = target_airport.flight_nr;
                        list<vector<string>> res = target_airport.path;
                        int count = 0;
                        path.push_front(res.front());
                        for (vector<string> &v : res) {
                            if(count!=0)path.push_back(v);
                            count++;
                        }
                    }
                    else {
                        list<vector<string>> res = target_airport.path;
                        for (vector<string> &v : res) {
                            path.push_back(v);
                        }
                    }
                } else {
                    distance = target_airport.distance;
                    flight_nr = target_airport.flight_nr;
                    path = target_airport.path;
                }
            }
        }
    }
    target_airport.path=path;
    target_airport.flight_nr=flight_nr;
    target_airport.distance=distance;
}
void Graph::bfs_bycity(string city, string target, unordered_set<string> airlines) {
    double distance = -1.0;
    list<vector<string>> path;
    int flight_nr = -1;
    Airport &target_airport = airports[target];
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++) {
        Airport &airport = iter->second;
        if (airport.city == city) {
            bfs(airport.code, target, airlines);
            if ((target_airport.flight_nr <= flight_nr || flight_nr == -1) &&
                target_airport.flight_nr != -1) {
                if (target_airport.flight_nr == flight_nr) {
                    if (target_airport.distance < distance) {
                        distance = target_airport.distance;
                        flight_nr = target_airport.flight_nr;
                        list<vector<string>> res = target_airport.path;
                        int count = 0;
                        path.push_front(res.front());
                        for (vector<string> &v : res) {
                            if(count!=0)path.push_back(v);
                            count++;
                        }
                    }
                    else {
                        list<vector<string>> res = target_airport.path;
                        for (vector<string> &v : res) {
                            path.push_back(v);
                        }
                    }
                } else {
                    distance = target_airport.distance;
                    flight_nr = target_airport.flight_nr;
                    path = target_airport.path;
                }
            }
        }
    }
    target_airport.path=path;
    target_airport.flight_nr=flight_nr;
    target_airport.distance=distance;
}

void Graph::bfs_bycords(double latitude, double longitude, double distance, string target){
    double dist = -1.0;
    list<vector<string>> path;
    int flight_nr = -1;
    Airport &target_airport = airports[target];
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        double d = calculateDistance(latitude, longitude, airport.latitude, airport.longitude);
        if(d <= distance){
            bfs(airport.code, target);
            if ((target_airport.flight_nr <= flight_nr || flight_nr == -1) && target_airport.flight_nr != -1) {
                if (target_airport.flight_nr == flight_nr) {
                    if (target_airport.distance < distance) {
                        dist = target_airport.distance;
                        flight_nr = target_airport.flight_nr;
                        list<vector<string>> res = target_airport.path;
                        int count = 0;
                        path.push_front(res.front());
                        for (vector<string> &v : res) {
                            if(count!=0)path.push_back(v);
                            count++;
                        }
                    }
                    else {
                        list<vector<string>> res = target_airport.path;
                        for (vector<string> &v : res) {
                            path.push_back(v);
                        }
                    }
                } else {
                    dist = target_airport.distance;
                    flight_nr = target_airport.flight_nr;
                    path = target_airport.path;
                }
            }
        }
    }
    target_airport.path=path;
    target_airport.flight_nr=flight_nr;
    target_airport.distance=dist;
}

void Graph::print_totalArticulationPoints() {
    list<Airport> res;
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        airport.visited=false;
        airport.distance=-1.0;
        airport.flight_nr=-1;
        airport.path.clear();
        airport.in_stack = false;
        airport.is_articulation = false;
    }
    stack<Airport> airport_stack;
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        if (!airport.visited)
            dfs_articulation(airport, &airport_stack, &res, 1);
    }

    if(res.empty()){
        cout << "There are no articulation points!\n";
        return;
    }
    cout << "The airticulation points are: \n";
    for(Airport airport : res){
        cout << airport.code << "\n";
    }
    //return answer;
}



void Graph::print_typeInCountry(string Country, string type){
    /*
    int count = 0;
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        if(iter->second.country==Country){
            count++;
        }
    }
    cout << "There are " << count << " airports in " << Country << '\n';
     */
    if (type=="all"){
        print_typeInCountry(Country, "airport");
        print_typeInCountry(Country, "flights");
        print_typeInCountry(Country, "airlines");
    }
    else stats.print_typeInCountry(Country, type);
}

void Graph::print_typeInCity(string City, string type) {
    if (type=="all"){
        print_typeInCity(City, "airport");
        print_typeInCity(City, "flights");
    }
    else stats.print_typeInCity(City, type);
}

void Graph::print_bestDistance(Airport airport) {
    cout << "The Bestpath distance is : " << airport.distance << '\n';
}

void Graph::print_bestDistance(string src, string target){
    bfs(src, target);
    Airport& airport = airports[target];
    print_bestDistance(airport);
}

void Graph::print_bestPath(Airport airport){
    cout << "Possible paths :\n";
    for(list<vector<string>>::iterator iter=airport.path.begin(); iter!=airport.path.end(); ++iter) {
        for (int j = 0; j<iter->size(); j++) {
            if(j!=0) cout << " -> ";
            cout << iter->at(j);
        }
        cout << '\n';
    }
    cout << "The shortest path is :\n";
    for(int i = 0; i<airport.path.front().size(); i++) {
        if(i != 0) cout << " -> ";
        cout << airport.path.front()[i];
    }
    cout << '\n';
}
void Graph::print_bestPath(string src, string target){
    bfs(src, target);
    Airport &airport = airports[target];
    print_bestPath(airport);
}

void Graph::print_bestCityPath(string src, string target){
    bfs_bycity(src, target);
    Airport &airport = airports[target];
    print_bestPath(airport);
}

void Graph::print_bestCordPath(double latitude, double longitude, double distance, string target){
    bfs_bycords(latitude, longitude, distance, target);
    Airport &airport = airports[target];
    if(airport.flight_nr != -1) {
        print_bestPath(airport);
        print_bestDistance(airport);
    } else{
        cout << "no flight found";
    }
}

void Graph::print_flightnr(Airport airport){
    cout << "The Bestpath flight number is : " << airport.flight_nr << '\n';
}

void Graph::print_bestflightnr(string src, string target){
    bfs(src, target);
    Airport &airport = airports[target];
    print_flightnr(airport);
}

void Graph::print_all_flights(string src){
    cout << "Total " << src << " flights: " << total_flights << '\n';
}

void Graph::print_all_different_airlines(string src){
    cout << "Total " << src << " different airline flights: " << different_airlines.size() << '\n';
}

void Graph::print_all_different_destinies(string src){
    cout << "Total " << src << " different destinies: " << destination_count << '\n';
}

void Graph::print_all_different_countries(string src){
    cout << "Total " << src << " different countries: " << different_countries.size() << '\n';
}

void Graph::print_all_different_cities(string src){
    cout << "Total " << src << " different cities: " << different_cities.size() << '\n';
}

void Graph::print_all_airport_information(string src){
    dfs_normal(src, -1);
    print_all_flights(src);
    print_all_different_airlines(src);
    print_all_different_destinies(src);
    print_all_different_countries(src);
    print_all_different_cities(src);
}

void Graph::print_all_airport_information_in_range(string src, int max){
    dfs_normal(src, max);
    print_all_flights(src);
    print_all_different_airlines(src);
    print_all_different_destinies(src);
    print_all_different_countries(src);
    print_all_different_cities(src);
}

void Graph::printAll(string src, string target){
    bfs(src, target);
    Airport &airport = airports[target];
    cout << "From " << src << " to " << target << ":\n";
    print_bestPath(airport);
    print_flightnr(airport);
    print_bestDistance(airport);
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
    print_bestPath(airport);
    print_flightnr(airport);
    print_bestDistance(airport);
    cout << '\n';
}

string Graph::find_code(string name) {
    if (airports.find(name)->second.code==name) return name;
    for (unMap::iterator iter=airports.begin(); iter!=airports.end();++iter) {
        if (iter->second.name==name) return iter->first;
    }
    return name;
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

        Airport airport;
        airport.code=Code;airport.name=Name;airport.city=City;airport.country=Country;airport.latitude=latitude;airport.longitude=longitude;
        airports.insert(pair<string, Airport>(Code, airport));
        stats.addCountry(Country, "airport");
        stats.addCity(City, "airport");
    }
}

void Graph::insertFlights() {
    ifstream fout;
    string file = "../flights.csv";
    fout.open(file);
    string temp, source, target, airline;
    getline(fout, temp);
    while (getline(fout, temp)) {
        stringstream itStream(temp);
        getline(itStream, source, ',');
        getline(itStream, target, ',');
        getline(itStream, airline, '\r');
        if(airports[source].flights.find(target) != airports[source].flights.end()){
            Flight &f = airports[source].flights[target];
            f.flight_airline.insert(airline);
            stats.addCountry(airports[source].country, "flights");
            stats.addCity(airports[source].city, "flights");
            stats.addAirline(airline, "flights");
        }
        else {
            Flight flight;
            flight.source = source;
            flight.target = target;
            airports[source].flights.insert(pair<string, Flight>(target, flight));
            airports[source].flights[target].flight_airline.insert(airline);
        }
    }
}

    void Graph::insertAirline() {
        ifstream fout;
        string file = "../airlines.csv";
        fout.open(file);
        string temp, code, name, callsign, country;
        getline(fout, temp);
        while (getline(fout, temp)) {
            stringstream itStream(temp);
            getline(itStream, code, ',');
            getline(itStream, name, ',');
            getline(itStream, callsign, ',');
            getline(itStream, country, '\r');

            Airline airline;
            airline.code = code;
            airline.name = name;
            airline.callsign = callsign;
            airline.country = country;
            airlines.insert(pair<string, Airline>(code, airline));
            stats.addCountry(country, "airlines");
        }
    }