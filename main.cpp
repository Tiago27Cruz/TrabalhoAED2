//
// Created by Tiago Cruz on 27/12/2022.
//

#include "graph.h"

using namespace std;

int main() {
    Graph graph = Graph(3020);
    graph.insertAirports();
    graph.insertFlights();
    graph.addFlight("CDG", "MAG", "ANG");
    graph.addFlight("LGA", "MAG", "ANG");
    graph.print_distance("CDG", "MAG");
    cout << "jomi\n";
    return 0;
}