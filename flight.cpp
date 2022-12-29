//
// Created by Tiago Cruz on 27/12/2022.
//

#include "flight.h"

Flight::Flight(string source, string target, string airline){
    this->source = source;
    this->target = target;
    this->airline = airline;
    this->visited = false;
}