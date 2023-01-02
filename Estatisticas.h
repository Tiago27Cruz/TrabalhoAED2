//
// Created by Isabel on 02/01/2023.
//

#ifndef TRABALHOAED2_ESTATISTICAS_H
#define TRABALHOAED2_ESTATISTICAS_H
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Estatisticas {
    unordered_map<string, vector<int>> countries;
    unordered_map<string, vector<int>> cities;
    unordered_map<string, vector<int>> airlines;
public:
    void addCountry(string country, string type);
    void addCity(string city, string type);
    void addAirline(string airline, string type);

    void print_typeInCountry(string country, string type);
    void print_typeInCity(string city, string type);
    void print_typeByAirline(string airline, string type);
};


#endif //TRABALHOAED2_ESTATISTICAS_H
