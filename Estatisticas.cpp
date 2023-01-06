//
// Created by Isabel on 02/01/2023.
//

#include "Estatisticas.h"

void Estatisticas::addCountry(string country, string type) {
    if (type=="airport") {
        if (countries.find(country) == countries.end()) {
            countries.insert(pair<string, vector<int>>(country, {1, 0, 0}));
        } else {
            countries[country][0] = countries.find(country)->second[0] + 1;
        }
    }
    else if (type=="flights") {
        if (countries.find(country) == countries.end()) {
            countries.insert(pair<string, vector<int>>(country, {0, 1, 0}));
        } else {
            countries[country][1] = countries.find(country)->second[1] + 1;
        }
    }
    else if (type=="airlines") {
        if (countries.find(country) == countries.end()) {
            countries.insert(pair<string, vector<int>>(country, {0, 0, 1}));
        } else {
            countries[country][2] = countries.find(country)->second[2] + 1;
        }
    }
}
void Estatisticas::addCity(string city, string type) {
    if (type=="airport") {
        if (cities.find(city) == cities.end()) {
            cities.insert(pair<string, vector<int>>(city, {1, 0, 0}));
        } else {
            cities[city][0] = cities.find(city)->second[0] + 1;
        }
    }
    else if (type=="flights") {
        if (cities.find(city) == cities.end()) {
            cities.insert(pair<string, vector<int>>(city, {0, 1, 0}));
        } else {
            cities[city][1] = cities.find(city)->second[1] + 1;
        }
    }
}
void Estatisticas::addAirline(string airline, string type) {
    if(type == "flights"){
        if(airlines.find(airline)==airlines.end()){
            airlines.insert(pair<string, vector<int>>(airline, {1}));
        } else {
            airlines[airline][0] = airlines.find(airline)->second[0] +1;
        }
    }
}

void Estatisticas::addAirlineCountry(string airline, string country){
    if(airlineCountry.find(airline) == airlineCountry.end()){
        unordered_set<string> temp;
        temp.insert(country);
        airlineCountry.insert(pair<string, unordered_set<string>>(airline, temp));
    } else{
        unordered_set<string> temp = airlineCountry[airline];
        temp.insert(country);
        airlineCountry[airline] = temp;
    }
}

void Estatisticas::addAirlineAirport(string airline, string airport) {
    if(airlineAirports.find(airline) == airlineAirports.end()){
        unordered_set<string> temp;
        temp.insert(airport);
        airlineAirports.insert(pair<string, unordered_set<string>>(airline, temp));
    } else{
        unordered_set<string> temp = airlineAirports[airline];
        temp.insert(airport);
        airlineAirports[airline] = temp;
    }
}

bool Estatisticas::isValidCity(string city) {
    return (cities.find(city) != cities.end());
}

bool Estatisticas::isValidCountry(string country) {
    return (countries.find(country) != countries.end());
}
void Estatisticas::print_typeInCountry(string country, string type) {
    if(type == "airport")cout << "There are " << countries[country][0] << " airports in " << country << '\n';
    else if(type == "flights")cout << "There are " << countries[country][1] << " flights coming from " << country << '\n';
    else if(type == "airlines")cout << "There are " << countries[country][2] << " airlines from " << country << '\n';
    else cout << "Incorrect type! \n";
}
void Estatisticas::print_typeInCity(string city, string type) {
    if(type == "airport")cout << "There are " << cities[city][0] << " airports in " << city << '\n';
    else if(type == "flights")cout << "There are " << cities[city][1] << " flights coming from " << city << '\n';
    else cout << "Incorrect type! \n";
}
void Estatisticas::print_typeByAirline(string airline, string type){
    if(type == "flights") cout << "There are " << airlines[airline][0] << " flights from airline " << airline << '\n';
}

void Estatisticas::print_nCountriesAirline(string airline) {
    cout << airline << " is active in " << airlineCountry[airline].size() << " countries\n";
}

void Estatisticas::print_nAirportsAirline(std::string airline) {
    cout << airline << " is active in " << airlineAirports[airline].size() << " airports\n";
}