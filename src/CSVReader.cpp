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


/**
 * Reads all files and initializes data \n
 * Complexity: O(n1 + n2 + n3) (n1 = number of lines in arlines.csv; n2 = number of lines in airports.csv; n3 = number of lines in flights.csv)
 */
void CSVReader::populate() {
    read_airports();
    read_airlines();
    read_flights();
}

/**
 * Reads airports.csv and stores the data \n
 * Complexity: O(n) (n = number of lines in file)
 */
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

/**
 * Reads arlines.csv and stores the data \n
 * Complexity: O(n) (n = number of lines in file)
 */
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

/**
 * Calculates the distance between two points using the Haversine formula \n
 * Complexity: O(1) (unsure since the documentation for functions like pow() don't specify complexity)
 * @param lat1 latitude of first point
 * @param lon1 longitude of first point
 * @param lat2 latitude of second point
 * @param lon2 longitude of second point
 * @return distance between two points
 */
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

/**
 * Reads flights.csv and stores the data \n
 * Complexity: O(n) (n = number of lines in file)
 */
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

/**
 * Determines which airports are within a certain radius of a point \n
 * Complexity: O(n) (n = number of airports)
 * @param lat latitude of point
 * @param longi longitude of point
 * @param radius radius in which to search (meters)
 * @return list of airport codes within the desired radius
 */
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

/**
 * Determines whether a flight is flown by one of the airlines in a list. If the list is empty, always returns true \n
 * Complexity: O(n) (n = number of airlines in preference list)
 * @param f flight in question
 * @param airlines desired airlines
 * @return true if flown by desired airlines or desired airline list is empty, false otherwise
 */
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

/**
 * Determines which countries can be reached from a given airport in a given number of flights \n
 * Complexity: O(V + E) (V = number of airports, E = number of flights)
 * @param n number of flights
 * @param source source airport code
 * @return unordered_set with the names of reachable countries
 */
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

/**
 * Performs a multi-source breadth-first search to find a path between two airports
 * Complexity: O(V + E) (V = number of airports, E = number of flights)
 * @param source source airport codes
 * @param dest destination airport codes
 * @param preferences desired airlines (if no preference, use empty list)
 * @return list of flights used and name of source used (useful for when there are multiple sources)
 */
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

/**
 * Gets an airport's name by its code \n
 * Complexity: O(n) (n = number of airports)
 * @param airportName name of airport
 * @return code of airport, empty string if airport does not exist
 */
string CSVReader::findAirportByName(const std::string airportName) const {
    auto it = airports.begin();
    while(it!=airports.end()){
        if(it->getName()==airportName) return (*it).getCode();
        it++;
    }
    return "";
}

/**
 * Get all airports in a given city \n
 * Complexity: O(n) (n = number of airports)
 * @param city name of city
 * @param country name of country
 * @return codes of all airports in the city
 */
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

/**
 * Determines which flights depart at a given airport \n
 * Complexity: O(n) (n = number of flights in the given airport) (complexity is not O(1) due to copy constructor when returning the list)
 * @param cod code of airport
 * @return list of flights departing from airport
 */
list<Flight> CSVReader::flightsFromAirport(const string &cod) {
    auto it = airports.find(Airport(cod));
    if (it == airports.end()) return {};
    return it->flights;
}

/**
 * Determines which flights arrive at a given airport \n
 * Complexity: O(n) (n = number of flights)
 * @param cod code of airport
 * @return list of flights arriving at airport
 */
list<pair<string,Flight>> CSVReader::flightsToAirport(const string &cod) {
    list<pair<string,Flight>> res;
    for (const Airport& airport : airports)
        for (const Flight& flight : airport.flights)
            if (flight.destAirportCode_ == cod)
                res.emplace_back(airport.getCode(), flight);
    return res;
}



