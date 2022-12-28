//
// Created by Tiago Cruz on 27/12/2022.
//

#include "graph.h"

using namespace std;

int main() {
    Graph graph = Graph(3020);
    graph.insertAirports();
    graph.insertFlights();
    graph.print_distance("Charles De Gaulle", "La Guardia");
    cout << "jomi\n";
    return 0;
}