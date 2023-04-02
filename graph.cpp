//
// Created by Tiago Cruz on 27/12/2022.
//

#include "graph.h"

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
        for(unordered_set<string>::iterator it = e.flight_airline.begin(); it != e.flight_airline.end(); it++){
            if(different_airlines.find(*it) == different_airlines.end()){
                different_airlines.insert(*it);
            }
        }
        //total_flights++;
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
void Graph::dfs_airport_info(string src, int max){
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        airport.visited = false;
    }
    destination_count = 0;
    //total_flights = 0;
    different_countries.clear();
    different_airlines.clear();
    different_cities.clear();
    dfs(src, max);
}

void Graph::best_paths_minimum_airlines(string src, string target){
    bfs(src, target);
    stack<vector<string>> super_res;
    stack<vector<string>> path;
    Airport &target_airport = airports[target];
    int min_size;
    for(vector<string> v : target_airport.path){
        unordered_set<string> temp;
        vector<string> res = find_airline(v);
        if(super_res.empty()){
            super_res.push(res);
            path.push(v);
            min_size = size;
        }
        else{
            if(size <= min_size){
                if(size == min_size){
                    super_res.push(res);
                    path.push(v);
                }
                else{
                    while(!super_res.empty()) {
                        super_res.pop();
                        path.pop();
                    }
                    super_res.push(res);
                    path.push(v);
                    min_size = size;
                }
            }
        }
    }
    cout << "The best paths with the least amount of airline changes are:\n";
    while(!super_res.empty()){
        vector<string> top_path = path.top();
        vector<string> top_res = super_res.top();
        for(int i = 0; i < top_path.size(); i++){
            if(i != 0) cout << " -> ";
            if(i != top_path.size()-1)cout << top_path[i] << "(" << top_res[i] << ")";
            else cout << top_path[i] << '\n';
        }
        super_res.pop();
        path.pop();
    }
    cout << min_size << " total airline changes\n";
}

void Graph::dfs_articulation(Airport& airport, stack<Airport*>& airport_stack, list<Airport>& res, int index) {
    airport.visited = true;
    airport.num = index;
    airport.low = index;
    airport.in_stack = true;
    int child = 0;
    bool isArticulation = false;
    airport_stack.push(&airport);

    for (unordered_map<string, Flight>::iterator iter = airport.flights.begin(); iter != airport.flights.end(); iter++) {
        Flight& e = iter->second;
        string wTarget = e.target;
        Airport& w = airports[wTarget];

        if (!w.visited) {
            child++;
            dfs_articulation(w, airport_stack, res, ++index);
            airport.low = min(airport.low, w.low);
            if(w.low >= airport.num) isArticulation=true;
        }
        else if (w.in_stack) {
            airport.low = min(airport.low, w.num);
        }
    }


    airport_stack.top()->in_stack = false;
    airport_stack.pop();

    if((airport.num > 1 && isArticulation) || (airport.num==1 && child > 1)){
        res.push_front(airport);
    }
}

void Graph::dfs_articulation(Airport& airport, stack<Airport*>& airport_stack, list<Airport>& res, int index, unordered_set<string> airlines) {
    airport.visited = true;
    airport.low = index;
    airport.num = index;
    airport.in_stack = true;
    int child = 0;
    bool isArticulation = false;
    airport_stack.push(&airport);

    for (unordered_map<string, Flight>::iterator iter = airport.flights.begin(); iter != airport.flights.end(); iter++) {
        Flight& e = iter->second;
        string wTarget = e.target;
        Airport& w = airports[wTarget];

        for(auto it = e.flight_airline.begin(); it != e.flight_airline.end(); it++){
            if(airlines.find(*it) == airlines.end()) continue;

            if (!w.visited) {
                child++;
                dfs_articulation(w, airport_stack, res, ++index);
                airport.low = min(airport.low, w.low);
                if(w.low >= airport.num)isArticulation=true;
            }
            else if (w.in_stack) {
                airport.low = min(airport.low, w.num);
            }
            break;
        }
    }
    airport_stack.top()->in_stack = false;
    airport_stack.pop();

    if((airport.num > 1 && isArticulation) || (airport.num==1 && child > 1)){
        res.push_front(airport);
    }
}


void Graph::AddBestPath(Airport& airport){
    vector<string> v = {airport.code};
    airport.path.push_back(v);
}

void Graph::AddPath(Airport& airport) {
    for(vector<string> &v : airport.path){
        v.push_back(airport.code);
    }
}

double Graph::calculateDistance(double lat1, double lon1, double lat2, double lon2){
    return 6371 * (2 * asin(sqrt((pow(sin(((lat2 - lat1) *
                                           M_PI / 180.0) / 2), 2) +
                                  pow(sin(((lon2 - lon1) *
                                           M_PI / 180.0) / 2), 2) *
                                  cos(((lat1) * M_PI / 180.0)) * cos(((lat2) * M_PI / 180.0))))));
}

void Graph::AddBranch(list<vector<string>> path, Airport& airport){
    for(vector<string> v : path) {
        v.push_back(airport.code);
        airport.path.push_back(v);
    }
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
    bool airline_check = false;

    while (!q.empty()) {
        Airport u = *q.front();
        q.pop();
        if (u.code == target)
            break;
        for (unordered_map<string, Flight>::iterator iter = u.flights.begin(); iter != u.flights.end(); iter++) {
            Flight& e = iter->second;
            for(unordered_set<string>::iterator it = airlines.begin(); it != airlines.end(); it++){
                if(e.flight_airline.find(*it) != e.flight_airline.end()) airline_check = true;
            }
            if(!airline_check) continue;
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
void Graph::bfs_bycords(double latitude, double longitude, double distance, string target, unordered_set<string> airlines){
    double dist = -1.0;
    list<vector<string>> path;
    int flight_nr = -1;
    Airport &target_airport = airports[target];
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        double d = calculateDistance(latitude, longitude, airport.latitude, airport.longitude);
        if(d <= distance){
            bfs(airport.code, target, airlines);
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

void Graph::bfs_Diametro(Airport& airport) {
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& ap = iter->second;
        ap.visited=false;
        ap.distance=-1.0;
    }
    queue<Airport*> q; // queue of unvisited nodes

    airport.distance=0.0;
    airport.flight_nr=0;
    airport.path.clear();
    airport.visited=true;
    q.push(&airport);

    while (!q.empty()) {
        Airport u = *q.front();
        q.pop();
        for (auto iter = u.flights.begin(); iter != u.flights.end(); iter++) {
            Flight& e = iter->second;
            string wTarget = e.target;
            Airport &w = airports[wTarget];

            if(!w.visited){
                q.push(&w);
                w.distance = u.distance+1;
                w.visited = true;
            }
        }
    }
}

void Graph::bfs_DiametroCountry(Airport& airport, string country) {
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& ap = iter->second;
        ap.visited=false;
        ap.distance=-1.0;
    }
    queue<Airport*> q; // queue of unvisited nodes

    airport.distance=0.0;
    airport.flight_nr=0;
    airport.path.clear();
    airport.visited=true;
    q.push(&airport);

    while (!q.empty()) {
        Airport u = *q.front();
        q.pop();
        for (auto iter = u.flights.begin(); iter != u.flights.end(); iter++) {
            Flight& e = iter->second;
            string wTarget = e.target;
            Airport &w = airports[wTarget];

            if(!w.visited && w.country != country){
                q.push(&w);
                w.distance = u.distance+1;
                w.visited = true;
            }
        }
    }
}

void Graph::topk_flights(int k, priority_queue <Airport, vector<Airport>, CompareByFlights> &pq){
    for(unordered_map<string, Airport>::iterator it = airports.begin(); it != airports.end(); it++){
        Airport airport = it->second;
        if(pq.size() < k){
            pq.push(airport);
        }
        else{
            if(airport.flights.size() > pq.top().flights.size()){
                pq.pop();
                pq.push(airport);
            }
        }
    }
}

void Graph::topk_flightsInAnAirline(int k, priority_queue <Airport, vector<Airport>, CompareByAirlineInFlight> &pq, string airline){
    for(unordered_map<string, Airport>::iterator it = airports.begin(); it != airports.end(); it++){
        Airport& airport = it->second;
        if(!stats.airlineInAirport(airline, airport.code)) continue;
        airport.airline_count = 0;
        for(auto mapFlight : airport.flights){
            Flight flight = mapFlight.second;
            if(flight.flight_airline.find(airline) != flight.flight_airline.end()){
                airport.airline_count++;
            }
        }
        if(pq.size() < k){
            pq.push(airport);
        }
        else if(airport.airline_count > pq.top().airline_count){
            pq.pop();
            pq.push(airport);
        }
    }
}

void Graph::topk_flightsCountry(int k, priority_queue <Airport, vector<Airport>, CompareByFlights> &pq, string country){
    for(unordered_map<string, Airport>::iterator it = airports.begin(); it != airports.end(); it++){
        Airport airport = it->second;
        if(airport.country!=country) continue;
        if(pq.size() < k){
            pq.push(airport);
        }
        else{
            if(airport.flights.size() > pq.top().flights.size()){
                pq.pop();
                pq.push(airport);
            }
        }
    }
}

void Graph::topk_airlines(int k, priority_queue <Airport, vector<Airport>, CompareByAirlines> &pq){
    for(unordered_map<string, Airport>::iterator it = airports.begin(); it != airports.end(); it++){
        Airport airport = it->second;
        if(pq.size() < k) {
            pq.push(airport);
        }
        else {
            for (unordered_map<string, Flight>::iterator iter = airport.flights.begin(); iter != airport.flights.end(); iter++) {
                Flight flight = iter->second;
                for (unordered_set<string>::iterator aether = flight.flight_airline.begin(); aether != flight.flight_airline.end(); aether++) {
                    if (iter == airport.flights.begin()) different_airlines = flight.flight_airline;
                    if (different_airlines.find(*aether) == different_airlines.end()) {
                        different_airlines.insert(*aether);
                    }
                }
            }
            airport.airlines = different_airlines;
            if(airport.airlines.size() > pq.top().airlines.size()){
                pq.pop();
                pq.push(airport);
            }
        }
    }
}

void Graph::topk_airlinesCountry(int k, priority_queue <Airport, vector<Airport>, CompareByAirlines> &pq, string country){
    for(unordered_map<string, Airport>::iterator it = airports.begin(); it != airports.end(); it++){
        Airport airport = it->second;
        if(airport.country!=country) continue;
        if(pq.size() < k) {
            pq.push(airport);
        }
        else {
            for (unordered_map<string, Flight>::iterator iter = airport.flights.begin(); iter != airport.flights.end(); iter++) {
                Flight flight = iter->second;
                for (unordered_set<string>::iterator aether = flight.flight_airline.begin(); aether != flight.flight_airline.end(); aether++) {
                    if (iter == airport.flights.begin()) different_airlines = flight.flight_airline;
                    if (different_airlines.find(*aether) == different_airlines.end()) {
                        different_airlines.insert(*aether);
                    }
                }
            }
            airport.airlines = different_airlines;
            if(airport.airlines.size() > pq.top().airlines.size()){
                pq.pop();
                pq.push(airport);
            }
        }
    }
}

void Graph::print_Diametro(){
    for (auto& aMap : airports){
        Airport& airport = aMap.second;
        airport.visited = false;
    }
    int max = 0;
    for(auto it = airports.begin(); it != airports.end(); it++){
        Airport& airport = it->second;
        bfs_Diametro(airport);
        for(auto iter = it; iter != airports.end(); iter++){
            Airport& w = iter->second;
            int distance = w.distance;
            if(distance > max) max = distance;
        }
    }
    cout << "This network's diameter is: " << max << "\n";
}

void Graph::print_DiametroCountry(string country){
    for (auto& aMap : airports){
        Airport& airport = aMap.second;
        airport.visited = false;
    }
    int max = 0;
    for(auto it = airports.begin(); it != airports.end(); it++){
        Airport& airport = it->second;
        if(airport.country != country) continue;
        bfs_DiametroCountry(airport, country);
        for(auto iter = it; iter != airports.end(); iter++){
            Airport& w = iter->second;
            if(w.country != country) continue;
            int distance = w.distance;
            if(distance > max) max = distance;
        }
    }
    cout << "The diameter is: " << max << "\n";
}

void Graph::print_totalArticulationPoints() {
    list<Airport> res;
    stack<Airport*> airport_stack;
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        airport.visited=false;
        airport.in_stack = false;
        airport.num = 0;
        airport.low = 0;
    }
    int idx = 1;
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        if (!airport.visited){
            dfs_articulation(airport, airport_stack, res, idx);
        }
        idx++;
    }

    if(res.empty()){
        cout << "There are no articulation points!\n";
        return;
    }
    cout << "The articulation points are: " << res.size() << "\n";
}

void Graph::print_specificArticulationPoints(unordered_set<string> airlines) {
    list<Airport> res;
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        airport.visited=false;
        airport.in_stack = false;
        airport.num = 0;
        airport.low = 0;
    }
    stack<Airport*> airport_stack;
    for (unMap::iterator iter = airports.begin(); iter != airports.end(); iter++){
        Airport& airport = iter->second;
        if (!airport.visited)
            dfs_articulation(airport, airport_stack, res, 1, airlines);
    }

    if(res.empty()){
        cout << "There are no articulation points!\n";
        return;
    }
    cout << "The articulation points are: " << res.size() << "\n";
    for(Airport airport : res){
        //cout << airport.code << "\n";
    }
    //return answer;
}

void Graph::print_typeInCountry(string Country, string type){
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

void Graph::print_typeByAirline(string airline, string type) {
    stats.print_typeByAirline(airline, type);
}

void Graph::print_nCountriesAirline(string airline) {
    stats.print_nCountriesAirline(airline);
}

void Graph::print_nAirportsAirline(std::string airline) {
    stats.print_nAirportsAirline(airline);
}

void Graph::print_bestDistance(Airport airport) {
    cout << "The Bestpath distance is : " << airport.distance << '\n';
}

void Graph::print_bestDistance(string src, string target){
    bfs(src, target);
    Airport& airport = airports[target];
    print_bestDistance(airport);
}
vector<string> Graph::find_airline(vector<string> res, unordered_set<string> check){
    unordered_set<string> temp;
    vector<string> airlines;
    int count = 0;
    size = 0;
    for(int i = 1; i < res.size(); i++) {
        Airport &current_airport = airports[res[i - 1]];
        Flight &flight = current_airport.flights[res[i]];
        if (i == 1) {
            temp = check;
            count = 1;
            if (i == res.size() - 1) count++;
            while (count > 0) {
                airlines.push_back(*temp.begin());
                count--;
            }
            count = 1;
        } else {
            unordered_set<string> super_temp;
            bool change_airline = true;
            for (unordered_set<string>::iterator it = temp.begin(); it != temp.end(); it++) {
                if (flight.flight_airline.find(*it) != flight.flight_airline.end()) {
                    change_airline = false;
                    super_temp.insert(*it);
                }
            }
            if (change_airline || i == res.size() - 1) {
                if (i == res.size() - 1) count++;
                while (count > 0) {
                    airlines.push_back(*temp.begin());
                    count--;
                }
                temp = flight.flight_airline;
                count = 1;
                size++;
            } else {
                count++;
                temp = super_temp;
            }
        }
    }
    return airlines;
}
vector<string> Graph::find_airline(vector<string> res){
    unordered_set<string> temp;
    vector<string> airlines;
    int count = 0;
    size = 0;
    for(int i = 1; i < res.size(); i++) {
        Airport &current_airport = airports[res[i - 1]];
        Flight &flight = current_airport.flights[res[i]];
        if (i == 1) {
            temp = flight.flight_airline;
            count = 1;
            if (i == res.size() - 1) count++;
            while (count > 0) {
                airlines.push_back(*temp.begin());
                count--;
            }
            count = 1;
        } else {
            unordered_set<string> super_temp;
            bool change_airline = true;
            for (unordered_set<string>::iterator it = temp.begin(); it != temp.end(); it++) {
                if (flight.flight_airline.find(*it) != flight.flight_airline.end()) {
                    change_airline = false;
                    super_temp.insert(*it);
                }
            }
            if (change_airline || i == res.size() - 1) {
                if (i == res.size() - 1) count++;
                while (count > 0) {
                    airlines.push_back(*temp.begin());
                    count--;
                }
                temp = flight.flight_airline;
                count = 1;
                size++;
            } else {
                count++;
                temp = super_temp;
            }
        }
    }
    return airlines;
}
void Graph::print_bestPath(Airport airport){
    if(airport.path.empty()){
        cout << "There is no path available\n";
        return;
    }
    cout << airport.path.front().size();
    vector<string> airlines;
    cout << "Possible paths :\n";
    for(vector<string> v : airport.path) {
        for (int j = 0; j<v.size(); j++) {
            if(j!=0) cout << " -> ";
            else if(v.size() > 1) airlines = find_airline(v);
            if(j != v.size()-1 && v.size() > 1) cout << v[j] << "(" << airlines[j] << ")";
            else cout << v[j];
        }
        cout << '\n';
    }
    cout << "The shortest path is :\n";
    for(int i = 0; i<airport.path.front().size(); i++) {
        if(i != 0 && airport.path.front().size() > 1) cout << " -> ";
        else if(airport.path.front().size() > 1) airlines = find_airline(airport.path.front());
        if(i != airport.path.front().size()-1 && airport.path.front().size() > 1) cout << airport.path.front()[i] << "(" << airlines[i] << ")";
        else cout << airport.path.front()[i];
    }
    cout << '\n';
}
void Graph::print_bestPath(Airport airport, unordered_set<string> check){
    if(airport.path.empty()){
        cout << "There is no path available\n";
        return;
    }
    vector<string> airlines;
    cout << "Possible paths :\n";
    for(vector<string> v : airport.path) {
        for (int j = 0; j<v.size(); j++) {
            if(j!=0) cout << " -> ";
            else airlines = find_airline(v, check);
            if(j != v.size()-1) cout << v[j] << "(" << airlines[j] << ")";
            else cout << v[j];
        }
        cout << '\n';
    }
    cout << "The shortest path is :\n";
    for(int i = 0; i<airport.path.front().size(); i++) {
        if(i != 0) cout << " -> ";
        else airlines = find_airline(airport.path.front(), check);
        if(i != airport.path.front().size()-1) cout << airport.path.front()[i] << "(" << airlines[i] << ")";
        else cout << airport.path.front()[i];
    }
    cout << '\n';
}
void Graph::print_bestPath(string src, string target){
    bfs(src, target);
    Airport &airport = airports[target];
    print_bestPath(airport);
}
void Graph::print_bestPath(string src, string target, unordered_set<string> airlines){
    bfs(src, target, airlines);
    Airport &airport = airports[target];
    print_bestPath(airport, airlines);
}

void Graph::print_bestCityPath(string src, string target){
    bfs_bycity(src, target);
    Airport &airport = airports[target];
    print_bestPath(airport);
}
void Graph::print_bestCityPath(string src, string target, unordered_set<string> airlines){
    bfs_bycity(src, target, airlines);
    Airport &airport = airports[target];
    print_bestPath(airport, airlines);
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

void Graph::print_bestCordPath(double latitude, double longitude, double distance, string target, unordered_set<string> airlines){
    bfs_bycords(latitude, longitude, distance, target, airlines);
    Airport &airport = airports[target];
    if(airport.flight_nr != -1) {
        print_bestPath(airport, airlines);
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

void Graph::print_bestflightnr(string src, string target, unordered_set<string> airlines){
    bfs(src, target, airlines);
    Airport &airport = airports[target];
    print_flightnr(airport);
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

void Graph::print_topk_airlines(int k){
    priority_queue <Airport, vector<Airport>, CompareByAirlines> pq;
    topk_airlines(k, pq);
    cout << "The k airports with the most different airlines are:\n";
    while(!pq.empty()){
        k--;
        cout << pq.top().code << " -> " << pq.top().airlines.size() << '\n';
        pq.pop();
    }
    if(k>0){
        cout << "There are no more airports to show!\n";
    }
}

void Graph::print_topk_airlinesCountry(int k, string country){
    priority_queue <Airport, vector<Airport>, CompareByAirlines> pq;
    topk_airlinesCountry(k, pq, country);
    cout << "The " << k  << " airports from "<<country<< " with the most different airlines are:\n";
    while(!pq.empty()){
        k--;
        cout << pq.top().code << " -> " << pq.top().airlines.size() << '\n';
        pq.pop();
    }
    if(k>0){
        cout << "There are no more airports to show!\n";
    }
}
void Graph::print_topk_flightsInAnAirline(int k, string airline){
    priority_queue <Airport, vector<Airport>, CompareByAirlineInFlight> pq;
    topk_flightsInAnAirline(k, pq, airline);
    cout << "The " << k  << " airports with the most flights from "<< airline << " are:\n";
    while(!pq.empty()){
        k--;
        cout << pq.top().code << " -> " << pq.top().airline_count << '\n';
        pq.pop();
    }
    if(k>0){
        cout << "There are no more airports to show!\n";
    }
}

void Graph::print_topk_flights(int k){
    priority_queue <Airport, vector<Airport>, CompareByFlights> pq;
    topk_flights(k, pq);
    cout << "The k airports with the most flights are:\n";
    while(!pq.empty()){
        k--;
        cout << pq.top().code << " -> " << pq.top().flights.size() << '\n';
        pq.pop();
    }
    if(k>0){
        cout << "There are no more airports to show!\n";
    }
}
void Graph::print_topk_flightsCountry(int k, string country){
    priority_queue <Airport, vector<Airport>, CompareByFlights> pq;
    topk_flightsCountry(k, pq, country);
    cout << "The " << k<< " airports from "<< country << " with the most flights are:\n";
    while(!pq.empty()){
        cout << pq.top().code << " -> " << pq.top().flights.size() << '\n';
        pq.pop();
        k--;
    }
    if(k>0){
        cout << "There are no more airports to show!\n";
    }
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
    dfs_airport_info(src, -1);
    print_all_different_airlines(src);
    print_all_different_destinies(src);
    print_all_different_countries(src);
    print_all_different_cities(src);
}

void Graph::print_all_airport_information_in_range(string src, int max){
    dfs_airport_info(src, max);
    print_all_different_airlines(src);
    print_all_different_destinies(src);
    print_all_different_countries(src);
    print_all_different_cities(src);
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
        stats.addAirportNameCode(Code, Name);
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
        if(airports[source].flights.find(target) != airports[source].flights.end()) {
            Flight &f = airports[source].flights[target];
            f.flight_airline.insert(airline);
        } else {
            Flight flight;
            flight.source = source;
            flight.target = target;
            airports[source].flights.insert(pair<string, Flight>(target, flight));
            airports[source].flights[target].flight_airline.insert(airline);
        }
        stats.addCountry(airports[source].country, "flights");
        stats.addCity(airports[source].city, "flights");
        stats.addAirline(airline, "flights");
        stats.addAirlineAirport(airline, airports[source].code);
        stats.addAirlineCountry(airline, airports[source].country);
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

string Graph::find_code(string name) {
    if(airports.find(name) != airports.end()){
        return name;
    }

    return stats.find_code(name);
}

bool Graph::isValidCity(string city){
    return stats.isValidCity(city);
}

bool Graph::isValidCountry(string country){
    return stats.isValidCountry(country);
}