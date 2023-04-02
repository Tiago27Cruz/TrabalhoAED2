//
// Created by Tiago Cruz on 27/12/2022.
//

#ifndef TRABALHO_AED2_GRAPH_H
#define TRABALHO_AED2_GRAPH_H

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <cmath>
#include <fstream>
#include <sstream>
#include "Estatisticas.h"

using namespace std;

class Graph {
    struct Airline{
        string code;
        string name;
        string callsign;
        string country;
    };
    struct Flight{
        string source;
        string target;
        unordered_set<string> flight_airline;
        bool visited;

    };

    struct Airport{
        string code;
        string name;
        string city;
        string country;
        double latitude;
        double longitude;
        double distance;
        int flight_nr;
        list<vector<string>> path;
        unordered_map<string, Flight> flights;
        unordered_set<string> airlines;
        bool visited;
        bool in_stack;
        bool is_articulation;
        int num;
        int low;
        int airline_count;
    };
    struct CompareByFlights {
        int operator() (const Airport& p1, const Airport& p2)
        {
            return p1.flights.size() > p2.flights.size();
        }
    };
    struct CompareByAirlines{
        int operator() (const Airport& p1, const Airport& p2)
        {
            return p1.airlines.size() > p2.airlines.size();
        }
    };
    struct CompareByAirlineInFlight{
        int operator() (const Airport& p1, const Airport& p2)
        {
            return p1.airline_count > p2.airline_count;
        }
    };
    typedef unordered_map<string, Airport> unMap;
    typedef unordered_map<string, Airline> unAir;
    //typedef unordered_map<string, vector<string>, CityHash, CityHash> ciMap;
    int n; // Graph size (vertices are numbered from 1 to n)
    unMap airports;     // The list of airports being represented
    unAir airlines;
    int destination_count;
    int size = 0;
    unordered_set<string> different_airlines;
    unordered_set<string> different_countries;
    unordered_set<string> different_cities;
    //ciMap cities;
    Estatisticas stats;
public:
    //vector<Airport> best_flight(string src, string target);
    //void addFlight(string src, string target, string airline);
    unMap get_airports() {return airports;};
    unAir get_airlines() {return airlines;};
    //dfs
    void dfs(string src, int max);
    void dfs_airport_info(string src, int max); /**/
    void best_paths_minimum_airlines(string src, string target);
    /**
     * Verifica se um aeroporto é articulation point ou não, na rede global
     * O(|V| + |E|)
     * @param airport
     * @param airport_stack
     * @param res
     * @param index
     */
    void dfs_articulation(Airport& airport, stack<Airport*>& airport_stack, list<Airport>& res, int index);
    /**
     * Verifica se um aeroporto é articulation point ou não, mas apenas na rede de airlines dadas pelo utilizador
     * O(|V| + |E|)
     * @param airport
     * @param airport_stack
     * @param res
     * @param index
     * @param airlines
     */
    void dfs_articulation(Airport& airport, stack<Airport*>& airport_stack, list<Airport>& res, int index, unordered_set<string> airlines);
    //bfs auxiliar methods
    void AddBestPath(Airport& airport);
    void AddPath(Airport& airport);
    void AddBranch(list<vector<string>> path, Airport& airport);
    void AddBranch(list<vector<string>> path, vector<string> best_path, Airport& airport);
    double calculateDistance(double lat1, double lon1, double lat2, double lon2);
    //bfs
    void bfs(string src, string target);
    void bfs(string src, string target, unordered_set<string> airlines);
    void bfs_bycity(string city, string target);
    void bfs_bycity(string city, string target, unordered_set<string> airlines);
    void bfs_bycords(double latitude, double longitude, double distance, string target);
    void bfs_bycords(double latitude, double longitude, double distance, string target, unordered_set<string> airlines);
    /**
     * Percorre todos os aeroportos, deixando-os com os valores iniciais, depois itera pelo resto dos flights/aeroportos, incremententando o valor da distância
     * O(|V| + |E|)
     * @param airport
     */
    void bfs_Diametro(Airport& airport);
    /**
     * Percorre todos os aeroportos, deixando-os com os valores iniciais, depois itera pelo resto dos flights/aeroportos, incremententando o valor da distância,
     * mas passando à frente os aeroportos cujo país não é o desejado.
     * O(|V| + |E|)
     * @param airport
     * @param country
     */
    void bfs_DiametroCountry(Airport& airport, string country);
    //topk
    /**
     * Itera por todos os aeroportos, se o tamanho da priority queue (pq) for menor que K, coloca imediatamente na pq,
     * se não, itera pelos voos do aeroporto e pelas airlines do voo e insere em different_airlines caso esta seja única,
     * por fim, se tiver mais airlines que o aeroporto no topo da priority queue, remove-o e insere o novo
     * O(|V|*|E|*n)
     * @param k
     * @param pq
     */
    void topk_airlines(int k, priority_queue <Airport, vector<Airport>, CompareByAirlines> &pq);
    /**
     * Itera por todos os aeroportos, passando sempre à frente caso o país do mesmo não seja o desejado, se o tamanho da priority queue (pq) for menor que K,
     * coloca imediatamente na pq, se não, itera pelos voos do aeroporto e pelas airlines do voo e insere em different_airlines caso esta seja única,
     * por fim, se tiver mais airlines que o aeroporto no topo da priority queue, remove-o e insere o novo
     * O(|V|*|E|*n)
     * @param k
     * @param pq
     * @param country
     */
    void topk_airlinesCountry(int k, priority_queue <Airport, vector<Airport>, CompareByAirlines> &pq, string country);
    /**
     * Itera pelos aeroportos, passando à frente caso a airline não esteja presente no dado aeroporto, itera pelos voos do aeroporto e guarda o número de vezes que a airline
     * dada aparece. Guarda os k aeroportos com maior número de voos nessa dada airline.
     * O(|V|*|E|)
     * @param k
     * @param pq
     * @param airline
     */
    void topk_flightsInAnAirline(int k, priority_queue <Airport, vector<Airport>, CompareByAirlineInFlight> &pq, string airline);
    /**
     * Itera pelo unordered_map airports e coloca numa priority queue os aeroportos com o maior número de voos num dado range (k)
     * O(|V|)
     * @param k
     * @param pq
     */
    void topk_flights(int k, priority_queue <Airport, vector<Airport>, CompareByFlights> &pq);
    /**
     * Itera pelo unordered_map airports e coloca numa priority queue os aeroportos com o maior número de voos num dado range (k) e passa à frente caso o país
     * do aeroporto não esteja localizado num dado país
     * O(|V|)
     * @param k
     * @param pq
     * @param country
     */
    void topk_flightsCountry(int k, priority_queue <Airport, vector<Airport>, CompareByFlights> &pq, string country);
    //printers
    /**
     * Inicializa todos os aeroportos com visited a false, depois percorre novamente todos os aeroportos, fazendo uma bfs e, novamente, percorre todos os aeroportos de modo a
     * encontrar o maior diâmetro, mostrando o seu valor no fim
     * O(|V|^2)
     */
    void print_Diametro();
    /**
     * Inicializa todos os aeroportos com visited a false, depois percorre novamente todos os aeroportos, fazendo uma bfs e, novamente, percorre todos os aeroportos de modo a
     * encontrar o maior diâmetro, mas passando os que não tem o país correspondente à frente, mostrando o seu valor no fim
     * O(|V|^2)
     * @param country
     */
    void print_DiametroCountry(string country);

    /**
     * Inicializa todos os aeroportos com valores default, depois percorre todos os aeroportos e chama a função dfs_articulation para todos os aeroportos que
     * não foram visitados e mostra o número de articulation points
     * O(|V|)
     */
    void print_totalArticulationPoints();
    /**
     * Inicializa todos os aeroportos com valores default, depois percorre todos os aeroportos e chama a função dfs_articulation para todos os aeroportos que
     * não foram visitados e mostra o número de articulation points, usando apenas as ligações de uma dada airline
     * O(|V|)
     * @param airlines
     */
    void print_specificArticulationPoints(unordered_set<string> airlines);

    /**
     * Mostra o número de aeroportos, voos ou companhias aereas de um país (country) conforme pedido, chamando a função homónima da classe Estatisticas
     * O(1)
     * @param country
     * @param type
     */
    void print_typeInCountry(string Country, string type);
    /**
     * Mostra o número de aeroportos ou voos de uma cidade (city) conforme pedido, chamando a função homónima da classe Estatisticas
     * O(1)
     * @param City
     * @param type
     */
    void print_typeInCity(string City, string type);
    /**
     * Mostra o número de voos de uma airline, chamando a função homónima da classe Estatisticas
     * O(1)
     * @param airline
     * @param type
     */
    void print_typeByAirline(string airline, string type);
    /**
     * Mostra o número de países em que a airline está presente, chamando a função homónima da classe Estatisticas
     * O(1)
     * @param airline
     */
    void print_nCountriesAirline(string airline);
    /**
     * Mostra o número de aeroportos em que a airline está presente, chamando a função homónima da classe Estatisticas
     * O(1)
     * @param airline
     */
    void print_nAirportsAirline(string airline);

    void print_bestDistance(Airport airport);
    void print_bestDistance(string src, string target);
    void print_bestPath(Airport airport);
    void print_bestPath(Airport airport, unordered_set<string> check);
    void print_bestPath(string src, string target);
    void print_bestPath(string src, string target, unordered_set<string> airlines);
    void print_bestCityPath(string src, string target);
    void print_bestCityPath(string src, string target, unordered_set<string> airlines);
    void print_bestCordPath(double latitude, double longitude, double distance, string target);
    void print_bestCordPath(double latitude, double longitude, double distance, string target, unordered_set<string> airlines);
    void print_flightnr(Airport airport);
    void print_bestflightnr(string src, string target);
    void print_bestflightnr(string src, string target, unordered_set<string> airlines);
    void printAll(string src, string target);
    void printAll(string src, string target, unordered_set<string> airlines);
    /**
     * Chama a função topk_flights e mostra o top k de aeroportos com maior número de voos
     * O(k)
     * @param k
     */
    void print_topk_flights(int k);
    /**
     * Chama a função topk_flightsCountry e mostra o top k de aeroportos com maior número de voos num dado país
     * O(k)
     * @param k
     * @param country
     */
    void print_topk_flightsCountry(int k, string country);
    /**
     * Chama a função topk_airlines e mostra o top k de aeroportos com maior número de airlines únicas
     * O(k)
     * @param k
     */
    void print_topk_airlines(int k);
    /**
     * Chama a função topk_airlinesCountry e mostra o top k de aeroportos com maior número de airlines únicas num dado país
     * O(k)
     * @param k
     */
    void print_topk_airlinesCountry(int k, string country);
    /**
     * Chama a função topk_flightsInAnAirline e mostra o top k de aeroportos com mais voos de uma dada airline
     * O(k)
     * @param k
     */
    void print_topk_flightsInAnAirline(int k, string airline);
    /**
     * Mostra o número de airlines (únicas) que se encontram no aeroporto indicado
     * O(1)
     * @param src
     */
    void print_all_different_airlines(string src);
    /**
     * Mostra o número de aeroportos que são possíveis atingir através do aeroporto indicado
     * O(1)
     * @param src
     */
    void print_all_different_destinies(string src);
    /**
     * Mostra o número de países que são possíveis atingir através do aeroporto indicado
     * O(1)
     * @param src
     */
    void print_all_different_countries(string src);
    /**
     * Mostra o número de cidades que são possíveis atingir através do aeroporto indicado.
     * O(1)
     * @param src
     */
    void print_all_different_cities(string src);
    /**
     * Executa o dfs e as funções que mostram as informações do aeroporto dado correspondente às diferentes airlines, destinos, países e cidades
     * O(1)
     * @param src
     */
    void print_all_airport_information(string src);
    /**
     * Executa o dfs com um limite (max) e as funções que mostram as informações do aeroporto dado correspondente às diferentes airlines, destinos, países e cidades
     * O(1)
     * @param src
     * @param max
     */
    void print_all_airport_information_in_range(string src, int max);
    //file reading
    /**
     * Lê o ficheiro airports.csv e guarda os aeroportos numa struct e num unordered_map (airports) e atualiza os unordered_maps respetivos da classe Estatisticas
     * O(n)
     */
    void insertAirports();
    /**
     * Lê o ficheiro flights.csv e guarda os voos numa struct, guardando as airlines num unordered_set e insere-se no unordered_set de flights da struct airport e atualiza os unordered_maps respetivos da classe Estatisticas
     * O(n)
     */
    void insertFlights();
    /**
     * Lê o ficheiro airlines.csv e insere as airlines num unordered_map (airlines) e atualiza os unordered_maps respetivos da classe Estatisticas
     * O(n)
     */
    void insertAirline();

    /**
     * recebe uma string name e, se for um código de aeroporto, retorna esse mesmo código, se não, chama a função homónima da classe Estatisticas que retorna o código do aeroporto,
     * caso seja um nome válido ou "error" caso não seja
     * O(1)
     * @param name
     * @return
     */
    string find_code(string name);
    /**
     * Retorna um vetor com o menor número de mudanças possíveis de airlines no vetor passado por parâmetro.
     * O(n^2)
     * @param res
     * @return
     */
    vector<string> find_airline(vector<string> res);
    /**
     * Retorna um vetor com o menor número de mudanças possíveis de airlines no vetor passado por parâmetro e só podendo escolher as airlines de check.
     * O(n^2)
     * @param res
     * @param check
     * @return
     */
    vector<string> find_airline(vector<string> res, unordered_set<string> check);
    /**
     * Verifica a existência de uma cidade (city) no ficheiro de aeroportos ao chamar a função homónima da classe estatisticas
     * O(1)
     * @param city
     * @return
     */
    bool isValidCity(string city);
    /**
     * Verifica a existência de um país (country) no ficheiro de aeroportos ao chamar a função homónima da classe estatisticas
     * O(1)
     * @param country
     * @return
     */
    bool isValidCountry(string country);
};

#endif //TRABALHO_AED2_GRAPH_H
