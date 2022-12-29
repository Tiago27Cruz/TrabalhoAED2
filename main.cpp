//
// Created by Tiago Cruz on 27/12/2022.
//

#include "graph.h"

using namespace std;

int main() {
    Graph graph = Graph(3020);
    graph.insertAirports();
    graph.insertFlights();
    //graph.print_distance_bycity("Paris", "JFK");
    graph.print_distance("MAG", "JFK");
    graph.print_bestpath("MAG", "JFK");
    graph.print_flightnr("MAG", "JFK");
    cout << "jomi\n";
    return 0;
}