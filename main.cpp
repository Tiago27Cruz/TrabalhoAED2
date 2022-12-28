//
// Created by Tiago Cruz on 27/12/2022.
//

#include "graph.h"

using namespace std;

int main(int argc, char* argv[]) {
    Graph graph = Graph(3020);
    graph.insertAirports();
    graph.insertFlights();
    cout << "jomi\n";
    return 0;
}