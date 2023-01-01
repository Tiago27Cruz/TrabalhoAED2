//
// Created by Tiago Cruz on 27/12/2022.
//

#include <sstream>
#include "graph.h"

using namespace std;

int main() {
    Graph graph = Graph(3020);
    graph.insertAirports();
    graph.insertFlights();
    graph.print_all_airport_information_in_range("CDG", 1);
    /*stack<string> stk;
    stk.push("Menu");
    cout << "Welcome Message\n";

    while(!stk.empty()) {
        string mode = stk.top();
        string in;
        if (mode == "Menu") {
            stk.pop();
            cout << "-> Search flights\n";
            getline(cin, in);
            stk.push(in);
        }
        else if (mode=="search") {
            stk.pop();
            cout << "-> Departure from a specified airport\n";
            cout << "-> Departure from a specified city\n";
            cout << "-> Departure from a specified area\n";
            getline(cin, in);
            stk.push(in);
        }
        else if (mode == "airport") {
            stk.pop();
            string src;
            string target;
            cout << "Please enter the airport of you're departure\n";
            getline(cin, src);
            cout << "Please enter the airport of you're destination\n";
            getline(cin, target);
            graph.print_bestpath(src, target);
        }
        else if (mode == "city") {
            stk.pop();
            string src;
            string target;
            cout << "Please enter the city of you're departure\n";
            getline(cin, src);
            cout << "Please enter the airport of you're destination\n";
            getline(cin, target);
            graph.print_bestcitypath(src, target);
            stk.push("search");
        }
        else if (mode == "area") {
            stk.pop();
            string latitude;
            string longitude;
            string radius;
            string target;
            cout << "Please enter the latitude, longitude and radius of the area of you're departure, separated by a comma\n";
            getline(cin, in);
            stringstream itStream(in);
            getline(itStream, latitude, ',');
            getline(itStream, longitude, ',');
            getline(itStream, radius, ',');
            cout << "Please enter the airport of you're destination\n";
            getline(cin, target);
            graph.print_bestcordpath(stod(latitude), stod(longitude), stod(radius), target);
            stk.push("search");
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