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