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

Airport CSVReader::findAirportByCoord(const double lat, const double longi) const{
    auto it=airports.begin();
    while(it!=airports.end()){
        if(it->getLatitude()==lat&&it->getLongitude()==longi) return *it;
        it++;
    }
    return Airport();
}
list<Airport> CSVReader::findAirportsAround(const double lat, const double longi,
                                                                     const double radius) const {
    auto it= airports.begin();
    Airport center= Airport("","", nullptr,lat,longi);
    list<Airport> temp;
    while(it!=airports.end()){
        if(center.calcDistanceHaversine(*it) <= radius){
            temp.push_back(*it);
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




list<Flight> CSVReader::bfs(const string &source, const string &dest) {
    list<Flight> res;
    for (const Airport& airport : airports) {
        airport.visited = false;
        airport.predecessor = nullptr;
    }
    queue<string> q; // queue of unvisited nodes
    q.push(source);
    auto it = airports.find(Airport(source));
    it->visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        string u = q.front(); q.pop();
        // show node order
        //cout << u << " ";
        auto find = airports.find(Airport(u));
        if (find->getCode() == dest) {
            Flight* pred = find->predecessor;
            while (pred != nullptr) {
                res.push_front(*pred);
                string prev = find->predecessor_code;
                auto back = airports.find(Airport(prev));
                pred = back->predecessor;
                find = back;
            }
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
    return res;
}
Airport CSVReader::findAirportByName(const std::string airportName) const {
    auto it = airports.begin();
    while(it!=airports.end()){
        if(it->getName()==airportName) return *it;
        it++;
    }
    return Airport();
}
list<Airport> CSVReader::findAirportByCity(const std::string city, const std::string country) const {
    auto it = airports.begin();
    list<Airport> res;
    while(it!=airports.end()){
        if(it->getCity()->get_country()==country&&it->getCity()->get_name()==city) res.push_back(*it);
        it++;
    }
    return res;
}


//throws error when theres no valid input
list<Airport> CSVReader::decipherInput(string src,double radius=0) {
    list<Airport> source;
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
        source=target;
        if(source.empty()){
            throw error;
        }
        return source;
    }

    string line=src;
    if(line.find('-')!=string::npos){
        stringstream ss(line);
        string temp,city,country;
        list<Airport> res;
        getline(ss,temp,'-');
        city=temp;
        getline(ss,temp,'-');
        country=temp;
        res=findAirportByCity(city,country);
        source=res;
        if(source.empty()){
            throw error;
        }
        return source;
    }

    Airport target=Airport(src,"", nullptr,0,0);
    Airport halfFound;
    auto it=airports.find(target);
    if(it==airports.end()){
        halfFound=findAirportByName(src);
        if(halfFound==Airport()){
            throw error;
        }
        source.push_back(halfFound);
        return source;
    }
    source.push_back(*it);
    return source;
}

