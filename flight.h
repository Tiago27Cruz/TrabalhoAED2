//
// Created by Tiago Cruz on 27/12/2022.
//

#ifndef TRABALHO_AED2_FLIGHT_H
#define TRABALHO_AED2_FLIGHT_H
#include <string>

using namespace std;

class Flight{
    string source;
    string target;
    string airline;
    bool visited;

public:
    Flight(string source, string target, string airline);
    string getTarget(){return target;};
    string getAirline(){return airline;};
    bool wasVisited() const {return visited;};
    void setVisit(bool state) {visited = state;}
};

#endif //TRABALHO_AED2_FLIGHT_H
