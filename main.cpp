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
    //graph.print_by_cords(49.012779, 2.550000, 25, "JFK");
    graph.printAll("CDG", "MAG");
    //graph.print_bestpath("CDG", "JFK");
    cout << "jomi\n";
    return 0;
}