//
// Created by fuhao on 28/12/2022.
//

#include <fstream>
#include <sstream>
#include <queue>
#include "CSVReader.h"
#include "Airport.h"
#include <sstream>

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

list<string> CSVReader::findAirportsAround(const double lat, const double longi,
                                                                     const double radius) const {
    auto it= airports.begin();
    Airport center= Airport("","", nullptr,lat,longi);
    list<string> temp;
    while(it!=airports.end()){
        if(center.calcDistanceHaversine(*it) <= radius){
            temp.push_back(it->getCode());
        }
        it++;
    }
    return temp;
}


bool CSVReader::isFlownByAirline(const Flight& f,const list<string>& airlines) const {
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

unordered_set<string> CSVReader::reachableCountries(unsigned n, const string& source) {
    unordered_set<string> countries;
    for (const Airport& airport : airports) {
        airport.visited = false;
        airport.predecessor = nullptr;
    }
    queue<pair<int, string>> q;
    q.emplace(0, source);

    while (!q.empty() && q.front().first <= n) {
        auto u = q.front(); q.pop();

        auto find = airports.find(Airport(u.second));
        countries.insert(find->getCity()->get_country());
        for (const auto& e : find->flights) {
            string w = e.destAirportCode_;
            auto target = airports.find(Airport(w));
            if (!target->visited) {
                q.emplace(u.first + 1, w);
                target->visited = false;
            }
        }
    }
    return countries;
}

pair<list<Flight>, string> CSVReader::bfs(const list<string> &source, const list<string> &dest, const list<string>& preferences) {
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
            if (!isFlownByAirline(e, preferences)) continue;
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
    res.second = "PATH NOT FOUND";
    return res;
}
string CSVReader::findAirportByName(const std::string airportName) const {
    auto it = airports.begin();
    while(it!=airports.end()){
        if(it->getName()==airportName) return (*it).getCode();
        it++;
    }
    return "";
}
list<string> CSVReader::findAirportByCity(const std::string city, const std::string country) const {
    auto it = airports.begin();
    list<string> res;
    while(it!=airports.end()){
        if(it->getCity()->get_country()==country&&it->getCity()->get_name()==city) res.push_back(it->getCode());
        it++;
    }
    return res;
}


//throws error when theres no valid input
list<string> CSVReader::decipherInput(const string src,const double radius) {
    list<string>source1;
    int error=0;

    if(src.at(0)=='(' && src.at(src.size()-1)==')'){
        list<double> coordinates;
        string line = src;
        string res;
        line.erase(line.begin());
        line.erase(--line.end());
        stringstream ss(line);
        while(getline(ss,res,',')){
            coordinates.push_back(stod(res));
        }
        auto target= findAirportsAround(coordinates.front(),coordinates.back(),radius);
        source1=target;
        if(source1.empty()){
            throw error;
        }
        return source1;
    }

    string line=src;
    if(line.find('-')!=string::npos){
        stringstream ss(line);
        string temp,city,country;
        list<string> res;
        getline(ss,temp,'-');
        city=temp;
        getline(ss,temp,'-');
        country=temp;
        res=findAirportByCity(city,country);
        source1=res;
        if(source1.empty()){
            throw error;
        }
        return source1;
    }

    Airport target=Airport(src,"", nullptr,0,0);
    string halfFound;
    auto it=airports.find(target);
    if(it==airports.end()){
        halfFound=findAirportByName(src);
        if(halfFound==""){
            throw error;
        }
        source1.push_back(halfFound);
        return source1;
    }
    source1.push_back(it->getCode());
    return source1;
}

void CSVReader::showShortestPath(const std::string src,const string dest, const double radius,const list<string>preferences) {
    list<string>origin =this->decipherInput(src,radius);
    list<string>destination=this->decipherInput(dest,radius);
    auto travel=this->bfs(origin,destination,preferences);
    auto startingPointPtr=airports.find(Airport(travel.second));
    cout<<"Airport: "<<startingPointPtr->getName()<<"("<<startingPointPtr->getCode()<<")";
    auto it=travel.first.begin();
    while(it!=travel.first.end()){
        auto airportPtr=airports.find(Airport(it->destAirportCode_));
        auto airlinePtr=airlines.find(Airline(it->airline_));
        cout<<"--"<<"[By:"<<airlinePtr->getName()<<"("<<airlinePtr->getCode()<<")"<<"]-->"<<"Airport: "<<airportPtr->getName()<<"("<<airportPtr->getCode()<<")";
        it++;
    }
}

list<Flight> CSVReader::flightsFromAirport(const string &cod) {
    auto it = airports.find(Airport(cod));
    if (it == airports.end()) return {};
    return it->flights;
}

list<pair<string,Flight>> CSVReader::flightsToAirport(const string &cod) {
    list<pair<string,Flight>> res;
    for (const Airport& airport : airports)
        for (const Flight& flight : airport.flights)
            if (flight.destAirportCode_ == cod)
                res.emplace_back(airport.getCode(), flight);
    return res;
}



