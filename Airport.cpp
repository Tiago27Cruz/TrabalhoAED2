//
// Created by Tiago Cruz on 27/12/2022.
//

#include "Airport.h"
#include <string>

Airport::Airport(std::string code) {
    this->code = code;
}

Airport::Airport(string code, string name, string city, string country, float latitude, float longitude){
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}

void Airport::AddFlight(Flight flight) {
    flights.push_back(flight);
}

void Airport::setVisit(bool state) {
    visited = state;
}

