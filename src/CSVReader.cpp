//
// Created by fuhao on 28/12/2022.
//

#include <fstream>
#include <sstream>
#include <queue>
#include "CSVReader.h"
#include "Airport.h"

using namespace std;

CSVReader::CSVReader(){
    populate();
};



void CSVReader::populate() {
    read_airports();
    read_airlines();
    read_flights();
}

void CSVReader::read_airports() {
    ifstream in("data/airports.csv");
    string code, name, city, country, latitude, longitude, line;
    double latitude_d;
    double longitude_d;
    getline(in, line);
    while (getline(in, line)) {
        istringstream iss(line);
        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, city, ',');
        getline(iss, country, ',');
        getline(iss, latitude, ',');
        getline(iss, longitude, ',');
        latitude_d = stod(latitude);
        longitude_d = stod(longitude);
        auto it = cities.insert(City(city, country));
        Airport curr = Airport(code, name, &(*it.first), latitude_d, longitude_d);
        airports.insert(curr);
    }
    in.close();
}

void CSVReader::read_airlines() {
    ifstream in("data/airlines.csv");
    string code, name, callsign, country, line;
    getline(in, line);
    while (getline(in, line)) {
        istringstream iss(line);
        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, callsign, ',');
        getline(iss, country, ',');
        airlines.insert(Airline(code, name, callsign, country));
    }
    in.close();
}

double haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

void CSVReader::read_flights() {
    ifstream in("data/flights.csv");
    string source, target, airline, line;
    getline(in, line);
    while (getline(in, line)) {
        istringstream iss(line);
        getline(iss, source, ',');
        getline(iss, target, ',');
        getline(iss, airline, ',');
        auto it = airports.find(Airport(source));
        auto it_target = airports.find(Airport(target));
        double distance = it->calcDistanceHaversine(*it_target);
        it->addFlight(Flight(target, airline, distance));
    }
    in.close();
}

unordered_set<Airport, AirportHash> CSVReader::getAirports() {
    return airports;
}

Airport CSVReader::findAirportByCoord(const double lat, const double longi) const{
    auto it=airports.begin();
    while(it!=airports.end()){
        if(it->getLatitude()==lat&&it->getLongitude()==longi) return *it;
        it++;
    }
}
unordered_set<Airport,AirportHash> CSVReader::findAirportsAround(const double lat, const double longi,
                                                                     const double radius) const {
    auto it= airports.begin();
    Airport center= Airport("","", nullptr,lat,longi);
    unordered_set<Airport,AirportHash> temp;
    while(it!=airports.end()){
        if(center.calcDistanceHaversine(*it) <= radius){
            temp.insert(*it);
        }
        it++;
    }

    return temp;
}


bool CSVReader::isFlownByAirline(const Flight f,list<string> airlines) const {
    if(airlines.empty()) return true;
    Airline target= Airline(f.airline_,"","","");
    auto found=this->airlines.find(target);
    auto it = airlines.begin();
    while(it!=airlines.end()){
        string airline= *it;
        if(found->getCode()== airline || found->getName()==airline||found->get_callsign()==airline) return true;
        it++;
    }
    return false;
}




pair<list<Flight>, string> CSVReader::bfs(const list<string> &source, const list<string> &dest) {
    list<Flight> flights;
    for (const Airport& airport : airports) {
        airport.visited = false;
        airport.predecessor = nullptr;
    }
    queue<string> q; // queue of unvisited nodes
    for (const string& s : source) {
        q.push(s);
        auto it = airports.find(Airport(s));
        it->visited = true;
    }
    while (!q.empty()) { // while there are still unvisited nodes
        string u = q.front(); q.pop();
        // show node order
        //cout << u << " ";
        auto find = airports.find(Airport(u));
        bool found = false;
        for (const string& s : dest) {
            if (find->getCode() == s) found = true;
        }
        if (found) {
            Flight* pred = find->predecessor;
            string prev;
            while (pred != nullptr) {
                flights.push_front(*pred);
                prev = find->predecessor_code;
                auto back = airports.find(Airport(prev));
                pred = back->predecessor;
                find = back;
            }
            pair<list<Flight>, string> res;
            res.first = flights;
            res.second = prev;
            return res;
        }
        for (auto& e : find->flights) {
            string w = e.destAirportCode_;
            auto target = airports.find(Airport(w));
            if (!target->visited) {
                target->predecessor = &e;
                target->predecessor_code = u;
                q.push(w);
                target->visited = true;
            }
        }
    }
    pair<list<Flight>, string> res;
    return res;
}

