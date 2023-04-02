//
// Created by Isabel on 02/01/2023.
//

#ifndef TRABALHOAED2_ESTATISTICAS_H
#define TRABALHOAED2_ESTATISTICAS_H
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Estatisticas {
    unordered_map<string, vector<int>> countries;
    unordered_map<string, vector<int>> cities;
    unordered_map<string, vector<int>> airlines;
    unordered_map<string, unordered_set<string>> airlineCountry;
    unordered_map<string, unordered_set<string>> airlineAirports;
    unordered_map<string, string> airportNameCode;
public:
    /**
     * Insere o nome do aeroporto num unordered_map, tendo o seu código como valor correspondente
     * O(1)
     * @param code
     * @param name
     */
    void addAirportNameCode(string code, string name);

    /**
     * Insere o nome de um país (country) no unordered_map countries e adiciona 1 à contagem do seu tipo (type) (airport, flight ou airline)
     * O(1)
     * @param country
     * @param type
     */
    void addCountry(string country, string type);

    /**
     * Insere o nome de uma cidade (city) no unordered_map cities e adiciona 1 à contagem do seu tipo (type) (airport ou flight)
     * O(1)
     * @param city
     * @param type
     */
    void addCity(string city, string type);

    /**
     * Insere o nome de uma airline no unordered_map airlines e adiciona 1 à contagem das suas flights
     * O(1)
     * @param airline
     * @param type
     */
    void addAirline(string airline, string type);
    /**
     * Insere o nome de uma airline no unordered_map airlineCountry e insere o país (country) num set, que ficará associado a uma airline
     * O(1)
     * @param airline
     * @param country
     */
    void addAirlineCountry(string airline, string country);
    /**
     * Insere o nome de uma airline no unordered_map airlineCountry e insere o aeroporto (airport) num set, que ficará associado a uma airline
     * O(1)
     * @param airline
     * @param country
     */
    void addAirlineAirport(string airline, string airport);

    /**
     * Verifica a existência de uma cidade (city) no ficheiro de aeroportos através da função find no unordered_map cities
     * O(1)
     * @param city
     * @return
     */
    bool isValidCity(string city);
    /**
     * Verifica a existência de um país (country) no ficheiro de aeroportos através da função find no unordered_map cities
     * O(1)
     * @param country
     * @return
     */
    bool isValidCountry(string country);
    /**
     * Verifica se uma dada airline está presente num dado aeroporto (airport) através do uso do operador [] em unordered_map e find no unordered_set
     * O(1)
     * @param airline
     * @param airport
     * @return
     */
    bool airlineInAirport(string airline, string airport);

    /**
     * Mostra o número de aeroportos, voos ou companhias aereas de um país (country) conforme pedido
     * O(1)
     * @param country
     * @param type
     */
    void print_typeInCountry(string country, string type);
    /**
     * Mostra o número de aeroportos ou voos de uma cidade (city) conforme pedido
     * O(1)
     * @param city
     * @param type
     */
    void print_typeInCity(string city, string type);
    /**
     * Mostra o número de voos de uma airline
     * O(1)
     * @param airline
     * @param type
     */
    void print_typeByAirline(string airline, string type);
    /**
     * Mostra o número de países em que a airline está presente
     * O(1)
     * @param airline
     */
    void print_nCountriesAirline(string airline);
    /**
     * Mostra o número de aeroportos em que a airline está presente
     * O(1)
     * @param airline
     */
    void print_nAirportsAirline(string airline);

    /**
     * Se encontrar o nome do aeroporto em airportNameCode, devolve o código, se não, quer dizer que o aeroporto não existe, logo devolver a string "error"
     * O(1)
     * @param name
     * @return
     */
    string find_code(string name);
};


#endif //TRABALHOAED2_ESTATISTICAS_H
