//
// Created by Tiago Cruz on 27/12/2022.
//

#include <sstream>
#include "graph.h"

using namespace std;

bool is_valid(Graph graph, string code) {
    code = graph.find_code(code);
    if (graph.get_airports().find(code)!=graph.get_airports().end()) return true;
    return false;
}
/*
bool is_validcity(Graph graph, string code) {
    code = graph.find_code(code);
    if (graph.get_airports().find(code)!=graph.get_airports().end()) return true;
    return false;
}*/

int main() {
    Graph graph = Graph(3020);
    graph.insertAirports();
    graph.insertAirline();
    graph.insertFlights();
    cout << "begin" << '\n';
    graph.print_bestPath("CDG", "MAG");
    graph.print_typeInCountry("United States", "all");
    graph.print_typeInCity("Paris", "all");
    //graph.print_totalArticulationPoints();
    //graph.print_all_airport_information_in_range("CDG", 1);
    //graph.printAll("CDG", "MAG");

    /*
    stack<string> stk;
    stk.push("Menu");
    cout << "Welcome Message\n";
    while(!stk.empty()) {
        string mode = stk.top();
        string in;
        if (mode == "Menu") {
            cout << "-> Search flights\n";
            cout << "-> Airport info\n";
            getline(cin, in);
            stk.push(in);
        }
        else if (mode=="search") {
            cout << "-> Departure from a specified airport\n";
            cout << "-> Departure from a specified city\n";
            cout << "-> Departure from a specified area\n";
            getline(cin, in);
            stk.push(in);
        }
        else if (mode == "airport") {
            string src;
            string target;
            cout << "Please enter the airport of your departure\n";
            getline(cin, src);
            while (!is_valid(graph, src) && src!="back") {
                cout << "Please enter a valid code/name!\n";
                getline(cin, src);
            }
            if (src=="back") {stk.push(src); continue;}
            cout << "Please enter the airport of your destination\n";
            getline(cin, target);
            while (!is_valid(graph, target) && target!="back") {
                cout << "Please enter a valid code/name!\n";
                getline(cin, target);
            }
            if (target=="back") {stk.push(target); continue;}
            graph.print_bestpath(graph.find_code(src), graph.find_code(target));
        }
        else if (mode == "city") {
            string src;
            string target;
            cout << "Please enter the city of your departure\n";
            getline(cin, src);/*
            while (!is_validcity(graph, src) && src!="back") {
                cout << "Please enter a valid code/name!\n";
                getline(cin, src);
            }
            if (src=="back") {stk.push(src); continue;}
            cout << "Please enter the airport of your destination\n";
            getline(cin, target);
            while (!is_valid(graph, target) && target!="back") {
                cout << "Please enter a valid code/name!\n";
                getline(cin, target);
            }
            if (target=="back") {stk.push(target); continue;}
            graph.print_bestcitypath(src, graph.find_code(target));
            stk.push("search");
        }
        else if (mode == "area") {
            string latitude;
            string longitude;
            string radius;
            string target;
            cout << "Please enter the latitude, longitude and radius of the area of your departure, separated by a comma\n";
            getline(cin, in);
            if (in=="back") {stk.push(in); continue;}
            stringstream itStream(in);
            getline(itStream, latitude, ',');
            getline(itStream, longitude, ',');
            getline(itStream, radius, ',');
            cout << "Please enter the airport of your destination\n";
            getline(cin, target);
            while (!is_valid(graph, target) && target!="back") {
                cout << "Please enter a valid code/name!\n";
                getline(cin, target);
            }
            if (target=="back") {stk.push(target); continue;}
            graph.print_bestcordpath(stod(latitude), stod(longitude), stod(radius), graph.find_code(target));
            stk.push("search");
        }
        else if (mode=="info") {
            cout << "Please enter the airport\n";
            getline(cin, in);
            while (!is_valid(graph, in) && in!="back") {
                cout << "Please enter a valid code/name!\n";
                getline(cin, in);
            }
            if (in=="back") {stk.push(in); continue;}
            graph.print_all_airport_information(graph.find_code(in));
        }
        else if (mode=="back") {
            stk.pop();
            stk.pop();
        }
        else {
        cout << "Please enter a valid input!\n";
        stk.pop();
        }
    }*/

    /*string s = " ";
    cout << "begin" << '\n';
    while(s != "back") {
        cin >> s;
        if (s == "all") {
            graph.print_bestcordpath(49.012779, 2.550000, 50, "MAG");
            //graph.printAll_bycity("Paris", "JFK");
        }
        if(s == "airline"){
            unordered_set<string> airlines;
            graph.printAll("CDG", "MAG");
            cin >> s;
            airlines.insert("AAL");
            airlines.insert("MPP");
            graph.printAll("CDG", "MAG", airlines);
        }
        if(s == "flights"){
            graph.print_all_airport_information("CDG");
        }
    }
    //graph.printAll_bycity("Paris", "JFK");
    //graph.print_by_cords(49.012779, 2.550000, 25, "JFK");
    //graph.printAll("ORY", "JFK");
    //graph.print_bestpath("CDG", "JFK");
    //graph.print_bestdistance("CDG", "MAG");
    cout << "jomi\n";*/
    return 0;
}