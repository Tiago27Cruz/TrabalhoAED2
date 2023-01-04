//
// Created by Tiago Cruz on 27/12/2022.
//

#include <sstream>
#include "graph.h"

using namespace std;

bool is_valid(Graph graph, string code) {
    code = graph.find_code(code);
    if(code == "error") return false;
    if (graph.get_airports().find(code)!=graph.get_airports().end()) return true;
    return false;
}
bool is_validAirline(Graph graph, string airline){
    if(graph.get_airlines().find(airline)==graph.get_airlines().end()) return false;
    return true;
}

void searchMenu(Graph *graph){
    bool open = true;
    string airline, src, target, latitude, longitude, radius;
    unordered_set<string> airlines;

    while(open){
        int in;
        cout << "1 -> Departure from a specified airport\n"
                "2 -> Departure from a specified city\n"
                "3 -> Departure from a specified area\n"
                "0 -> Go Back\n";
        while(!(cin >> in)){
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input!\n";
            cout << "1 -> Departure from a specified airport\n"
                    "2 -> Departure from a specified city\n"
                    "3 -> Departure from a specified area\n"
                    "0 -> Go Back\n";
        }
        switch(in){
            case 0:
                open = false;
                break;
            case 1: {
                cout << "What do you prefer?\n"
                        "1 -> Minimum number of flights\n"
                        "2 -> Minimum number of airlines\n"
                        "0 -> Go Back\n";
                while (!(cin >> in)) {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Invalid input!\n";
                    cout << "What do you prefer?\n"
                            "1 -> Minimum number of flights\n"
                            "2 -> Minimum number of airlines\n"
                            "0 -> Go Back\n";
                }
                switch(in){
                    case 0: break;
                    case 1: {
                        cout << "Do you wish to specify airlines?\n"
                                "1 -> Yes\n"
                                "2 -> No\n"
                                "0 -> Go Back\n";
                        while (!(cin >> in)) {
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cout << "Invalid input!\n";
                            cout << "Do you wish to specify airlines?\n"
                                    "1 -> Yes\n"
                                    "2 -> No\n"
                                    "0 -> Go Back\n";
                        }
                        switch (in) {
                            case 0:
                                break;
                            case 1:
                                airline = "";
                                cout << "Please insert the specified airlines and write done when done!\n";
                                while (airline != "done") {
                                    cin.clear();
                                    cin.ignore(INT_MAX, '\n');
                                    cin >> airline;
                                    if (airline == "done") break;
                                    else if (is_validAirline(*graph, airline)) {
                                        airlines.insert(airline);
                                        cout
                                                << "Airline inserted! Please insert another airline or write done if you're finished!\n";
                                    } else {
                                        cout << "Please insert a valid airline!\n";
                                    }
                                }

                                cout << "Please enter the airport of your departure or write back to go back\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cin >> src;
                                while (!is_valid(*graph, src) && src != "back") {
                                    cout << "Please enter a valid code/name!\n";
                                    cin.clear();
                                    cin.ignore(INT_MAX, '\n');
                                    cin >> src;
                                }
                                if (src == "back") { break; }
                                cout << "Please enter the airport of your destination or write back to go back\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cin >> target;
                                while (!is_valid(*graph, target) && target != "back") {
                                    cout << "Please enter a valid code/name!\n";
                                    cin.clear();
                                    cin.ignore(INT_MAX, '\n');
                                    cin >> target;
                                }
                                if (target == "back") { break; }

                                graph->print_bestPath(graph->find_code(src), graph->find_code(target), airlines);
                                break;
                            case 2:
                                cout << "Please enter the airport of your departure or write back to go back\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cin >> src;
                                while (!is_valid(*graph, src) && src != "back") {
                                    cout << "Please enter a valid code/name!\n";
                                    cin.clear();
                                    cin.ignore(INT_MAX, '\n');
                                    cin >> src;
                                }
                                if (src == "back") { break; }
                                cout << "Please enter the airport of your destination or write back to go back\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cin >> target;
                                while (!is_valid(*graph, target) && target != "back") {
                                    cout << "Please enter a valid code/name!\n";
                                    cin.clear();
                                    cin.ignore(INT_MAX, '\n');
                                    cin >> target;
                                }
                                if (src == "back") { break; }
                                graph->print_bestPath(graph->find_code(src), graph->find_code(target));
                                break;
                            default:
                                cout << "Invalid input!\n";
                                break;
                        }
                        break;
                    }
                    case 2:{
                        cout << "Please enter the airport of your departure or write back to go back\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cin >> src;
                        while (!is_valid(*graph, src) && src != "back") {
                            cout << "Please enter a valid code/name!\n";
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cin >> src;
                        }
                        if (src == "back") { break; }
                        cout << "Please enter the airport of your destination or write back to go back\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cin >> target;
                        while (!is_valid(*graph, target) && target != "back") {
                            cout << "Please enter a valid code/name!\n";
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cin >> target;
                        }
                        if (target == "back") { break; }
                        graph->dfs_minimum_airlines(src, target);
                        break;}
                    default:
                        cout << "Invalid input!\n";
                        break;
                }
                break;
            }
            case 2: {
                cout << "Do you wish to specify airlines?\n"
                        "1 -> Yes\n"
                        "2 -> No\n"
                        "0 -> Go Back\n";
                while (!(cin >> in)) {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Invalid input!\n";
                    cout << "Do you wish to specify airlines?\n"
                            "1 -> Yes\n"
                            "2 -> No\n"
                            "0 -> Go Back\n";
                }
                switch (in) {
                    case 0:
                        break;
                    case 1:
                        airline = "";
                        cout << "Please insert the specified airlines and write done when done!\n";
                        while (airline != "done") {
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cin >> airline;
                            if (airline == "done") break;
                            else if (is_validAirline(*graph, airline)) {
                                airlines.insert(airline);
                                cout
                                        << "Airline inserted! Please insert another airline or write done if you're finished!\n";
                            } else {
                                cout << "Please insert a valid airline!\n";
                            }
                        }
                        cout << "Please enter the city of your departure or write back to go back\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cin >> src;

                        while (!graph->isValidCity(src) && src != "back") {
                            cout << "Please enter a valid city!\n";
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cin >> src;
                        }
                        if (src == "back") { break; }
                        cout << "Please enter the airport of your destination\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cin >> target;
                        while (!is_valid(*graph, target) && target != "back") {
                            cout << "Please enter a valid code/name!\n";
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cin >> target;
                        }
                        if (target == "back") { break; }
                        graph->print_bestCityPath(src, graph->find_code(target), airlines);
                        break;
                    case 2:
                        cout << "Please enter the city of your departure or write back to go back\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cin >> src;

                        while (!graph->isValidCity(src) && src != "back") {
                            cout << "Please enter a valid city!\n";
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cin >> src;
                        }
                        if (src == "back") { break; }
                        cout << "Please enter the airport of your destination\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cin >> target;
                        while (!is_valid(*graph, target) && target != "back") {
                            cout << "Please enter a valid code/name!\n";
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cin >> target;
                        }
                        if (target == "back") { break; }
                        graph->print_bestCityPath(src, graph->find_code(target));
                        break;
                    default:
                        cout << "Invalid Input!\n";
                        break;
                }
                break;
            }
            case 3: {
                cout << "Do you wish to specify airlines?\n"
                        "1 -> Yes\n"
                        "2 -> No\n"
                        "0 -> Go Back\n";
                while (!(cin >> in)) {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Invalid input!\n";
                    cout << "Do you wish to specify airlines?\n"
                            "1 -> Yes\n"
                            "2 -> No\n"
                            "0 -> Go Back\n";
                }

                    if(in == 0)
                        break;
                    else if(in == 1) {
                        airline = "";
                        cout << "Please insert the specified airlines and write done when done!\n";
                        while (airline != "done") {
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cin >> airline;
                            if (airline == "done") break;
                            else if (is_validAirline(*graph, airline)) {
                                airlines.insert(airline);
                                cout
                                        << "Airline inserted! Please insert another airline or write done if you're finished!\n";
                            } else {
                                cout << "Please insert a valid airline!\n";
                            }
                        }
                        cout
                                << "Please enter the latitude, longitude and radius of the area of your departure, separated by a comma\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cin >> src;
                        if (src == "back") { break; }
                        stringstream itStream(src);
                        getline(itStream, latitude, ',');
                        getline(itStream, longitude, ',');
                        getline(itStream, radius, ',');
                        cout << "Please enter the airport of your destination\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cin >> target;
                        while (!is_valid(*graph, target) && target != "back") {
                            cout << "Please enter a valid code/name!\n";
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cin >> target;
                        }
                        if (target == "back") { break; }
                        graph->print_bestCordPath(stod(latitude), stod(longitude), stod(radius),
                                                  graph->find_code(target), airlines);
                    }
                    else if(in == 2) {
                        cout
                                << "Please enter the latitude, longitude and radius of the area of your departure, separated by a comma\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cin >> src;
                        if (src == "back") { break; }
                        stringstream stringStream(src);
                        getline(stringStream, latitude, ',');
                        getline(stringStream, longitude, ',');
                        getline(stringStream, radius, ',');
                        cout << "Please enter the airport of your destination\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cin >> target;
                        while (!is_valid(*graph, target) && target != "back") {
                            cout << "Please enter a valid code/name!\n";
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cin >> target;
                        }
                        if (target == "back") { break; }
                        graph->print_bestCordPath(stod(latitude), stod(longitude), stod(radius),
                                                  graph->find_code(target));
                    }
                    else {
                        cout << "Invalid input!\n";
                        break;
                    }
                    break;
            }
            default:
                cout << "Invalid input!\n";
                break;
        }
    }
}

void infoMenu(Graph graph){
    bool open = true;
    string str;

    while(open){
        int in;
        cout << "1 -> Show an airport entire information\n"
                "2 -> Show anything by country\n"
                "3 -> Show anything by city\n"
                "4 -> Show anything by airline\n"
                "0 -> Go Back\n";
        while(!(cin >> in)){
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input!\n";
            cout << "1 -> Show an airport entire information\n"
                    "2 -> Show anything by country\n"
                    "3 -> Show anything by city\n"
                    "4 -> Show anything by airline\n"
                    "0 -> Go Back\n";
        }
        switch(in){
            case 0:
                open = false;
                break;
            case 1:
                str = "";
                cout << "Please enter an airport or write back to go back\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> str;
                while (!is_valid(graph, str) && str != "back") {
                    cout << "Please enter a valid code/name!\n";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cin >> str;
                }
                if(str == "back"){
                    break;
                }
                graph.print_all_airport_information(graph.find_code(str));
                break;
            case 2: {
                str = "";
                cout << "Please enter a country or write back to go back\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> str;
                while (!graph.isValidCountry(str) && str != "back") {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Invalid input! Please insert a valid country\n";
                    cin >> str;
                }
                if (str == "back") break;


                cout << "What do you wish to know?\n"
                        "1 -> Number of airports\n"
                        "2 -> Number of flights\n"
                        "3 -> Number of airlines\n"
                        "0 -> Go Back\n";
                while (!(cin >> in)) {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Invalid input!\n";
                    cout << "What do you wish to know?\n"
                            "1 -> Number of airports\n"
                            "2 -> Number of flights\n"
                            "3 -> Number of airlines\n"
                            "0 -> Go Back\n";
                }
                switch (in) {
                    case 0:
                        break;
                    case 1:
                        graph.print_typeInCountry(str, "airport");
                        break;
                    case 2:
                        graph.print_typeInCountry(str, "flights");
                        break;
                    case 3:
                        graph.print_typeInCountry(str, "airlines");
                        break;
                    default:
                        cout << "Invalid input\n";
                        break;
                }
                break;
            }
            case 3: {
                str = "";
                cout << "Please enter a city or write back to go back\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> str;
                while (!graph.isValidCity(str) && str != "back") {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Invalid input! Please insert a valid city\n";
                    cin >> str;
                }
                if (str == "back") break;


                cout << "What do you wish to know?\n"
                        "1 -> Number of airports\n"
                        "2 -> Number of flights\n"
                        "0 -> Go Back\n";
                while (!(cin >> in)) {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Invalid input!\n";
                    cout << "What do you wish to know?\n"
                            "1 -> Number of airports\n"
                            "2 -> Number of flights\n"
                            "0 -> Go Back\n";
                }
                switch (in) {
                    case 0:
                        break;
                    case 1:
                        graph.print_typeInCity(str, "airport");
                        break;
                    case 2:
                        graph.print_typeInCity(str, "flights");
                        break;
                    default:
                        cout << "Invalid input\n";
                        break;
                }
                break;
            }
            case 4: {
                str = "";
                cout << "Please enter an airline or write back to go back\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> str;
                while (!is_validAirline(graph, str) && str != "back") {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Invalid input! Please insert a valid airline\n";
                    cin >> str;
                }
                if (str == "back") break;

                cout << "What do you wish to know?\n"
                        "1 -> Number of countries\n"
                        "2 -> Number of flights\n"
                        "3 -> Number of airports\n"
                        "0 -> Go Back\n";
                while (!(cin >> in)) {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Invalid input!\n";
                    cout << "What do you wish to know?\n"
                            "1 -> Number of countries\n"
                            "2 -> Number of flights\n"
                            "3 -> Number of airports\n"
                            "0 -> Go Back\n";
                }
                switch (in) {
                    case 0:
                        break;
                    case 1:
                        graph.print_nCountriesAirline(str);
                        break;
                    case 2:
                        graph.print_typeByAirline(str, "flights");
                        break;
                    case 3:
                        graph.print_nAirportsAirline(str);
                        break;
                    default:
                        cout << "Invalid input\n";
                        break;
                }
                break;
            }
            default:
                cout << "Invalid input\n";
                break;
        }
    }
}

int main() {
    Graph graph = Graph(3020);
    graph.insertAirports();
    graph.insertAirline();
    graph.insertFlights();
    graph.dfs_minimum_airlines("CDG", "MAG");
    //graph.bfs_by_best_airline("CDG", "MAG");
    cout << "begin" << '\n';
    //unordered_set<string> airlines;
    //airlines.insert("ANG");

    //graph.print_specificArticulationPoints(airlines);
    graph.print_totalArticulationPoints();
    //graph.print_bestPath("MAG", "CDG");
    //graph.print_typeInCountry("United States", "all");
    //graph.print_typeInCity("Paris", "all");
    //graph.print_typeByAirline("MLA", "flights");
    //graph.print_totalArticulationPoints();
    //graph.print_all_airport_information_in_range("CDG", 1);
    //graph.printAll("CDG", "MAG");

    bool open = true;

    while(open){
        cout << "Welcome Message\n";
        int in;
        cout << "1 -> Search flights\n"
                "2 -> Airport info\n"
                "0 -> Quit\n";
        while(!(cin >> in)){
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input!\n";
            cout << "1 -> Search flights\n"
                    "2 -> Airport info\n"
                    "0 -> Quit\n";
        }
        switch(in){
            case 0:
                open = false;
                break;
            case 1:
                searchMenu(&graph);
                break;
            case 2:
                infoMenu(graph);
                break;
            default:
                cout << "Invalid input!\n";
                break;
        }


    }
    //graph.printAll_bycity("Paris", "JFK");
    //graph.print_by_cords(49.012779, 2.550000, 25, "JFK");
    //graph.printAll("ORY", "JFK");
    //graph.print_bestpath("CDG", "JFK");
    //graph.print_bestdistance("CDG", "MAG");
    return 0;
}