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
string CSVReader::findAirportByName(const std::string airportName,const string city, const string country) const {


    auto it = airports.begin();
    while(it!=airports.end()){
        City *cityP=it->getCity();

        if(it->getName()==airportName &&cityP->get_name()==city&&cityP->get_country()==country ) return (*it).getCode();
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


/**
 * Decodes the input givem by user following certain format
 * Complexity: O(N) being N the linear search for airports with given input
 * @param src : String given by user from input- can be the following formats : "(latitude,longitude)","airportName_city_country","city-country", "airportCode"
 * @param radius : In case of search by coordinates, needs radius to find airports around the coordinates given by user input
 * @return list<string> : List of airport codes in string
 */
list<string> CSVReader::decipherInput(const string src,const double radius) {
    list<string>source1;
    int error=-1;

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

    line=src;

    if(line.find('_')!=string::npos){
        stringstream ss(line);
        string temp,city,country,airportName;
        string res;
        getline(ss,temp,'_');
        airportName=temp;
        getline(ss,temp,'_');
        city=temp;
        getline(ss,temp,'_');
        country=temp;
        res= findAirportByName(airportName,city,country);
        if(res==""){
            throw error;
        }
        source1.push_back(res);
        return source1;
    }

    Airport target=Airport(src,"", nullptr,0,0);
    string halfFound;
    auto it=airports.find(target);
    if(it==airports.end()) throw error;
    source1.push_back(it->getCode());
    return source1;
}
/**
 * Outputs in the terminal the shortes path from a source to a destination airport given any inputs by user following any kind of criteria(ex: city, coordinates, airport name/code)
 * Complexity:O(N) being N the size of the path to travel through
 * @param src : string of source airport
 * @param dest : string of destination airport
 * @param radius : radius around a given coordinate to find airports
 * @param preferences : list of user prefered airlines, empty means user has no airline preference
 */
void CSVReader::showShortestPath(const std::string src,const string dest, const double radius,const list<string>preferences) {
    list<string>origin =this->decipherInput(src,radius);
    list<string>destination=this->decipherInput(dest,radius);
    auto travel=this->bfs(origin,destination,preferences);
    auto startingPointPtr=airports.find(Airport(travel.second));
    cout<<"{Aeroporto: "<<startingPointPtr->getName()<<"("<<startingPointPtr->getCode()<<")}";
    auto it=travel.first.begin();
    while(it!=travel.first.end()){
        auto airportPtr=airports.find(Airport(it->destAirportCode_));
        auto airlinePtr=airlines.find(Airline(it->airline_));
        cout<<" =="<<"[Por:"<<airlinePtr->getName()<<"("<<airlinePtr->getCode()<<")"<<"]==> "<<"{Aeroporto: "<<airportPtr->getName()<<"("<<airportPtr->getCode()<<")}";
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
/**
 * Calculates the nr of airports related to the whole web or by country
 * Complexity : O(1) if operation done for the whole web and O(N) if its specific for a country (N= nr of related Airports);
 * @param tipo : Type of operation - if for the whole web or only for the country being it "rede" or "pais" respectively
 * @param country : In case the operation is related to a country, it's the related country
 * @return Nr or related airports
 */
int CSVReader::calculateNrAirports(const std::string tipo,const string country) {
    int airportCount=0;
    if(tipo=="rede"){
        return airports.size();
    }
    if(tipo=="pais"){
        for (Airport a :airports){
            City *city = a.getCity();
            if(city->get_country()==country) airportCount++;
        }
    }
    return airportCount;
}
int CSVReader::calculateNrFlights(const std::string tipo, const std::string countryOrAirline) {
    int res=0;
    if(tipo=="rede"){
            for(Airport a : airports){
                res+=a.getFlights().size();
            }
    }
    if(tipo=="pais"){
        for(Airport a : airports){
            City *city=a.getCity();
            if(city->get_country()==countryOrAirline){
                res+=a.getFlights().size();
            }
        }
    }
    if (tipo=="companhia aerea"){
        for(Airport a: airports){
            for(Flight f: a.getFlights()){
                if(f.airline_==countryOrAirline) res++;
            }
        }
    }
    return res;
}
int CSVReader::calculateNrAirlines(const std::string tipo, const std::string country) {
    int res=0;
    if(tipo=="rede"){
        return airlines.size();
    }
    if(tipo=="pais"){
        for(Airline a: airlines){
            if(a.getCountry()==country){
                res++;
            }
        }
    }
    return res;
}
Airport CSVReader::maxFlightsAirport(const int prevMax,const string country,const unordered_set<Airport,AirportHash> existingAirports) {
    int max=0;
    Airport temp;
    if(prevMax!=-1){
        for(Airport a: airports){
            City *city=a.getCity();
            if(city->get_country()==country || country=="") {
                if (existingAirports.find(a) == nullptr &&  a.getFlights().size() <= prevMax) {
                    if (a.getFlights().size() > max) {
                        max = a.getFlights().size();
                        temp = a;
                    }
                }
            }
        }
    }
    else{
        for(Airport a: airports){
            City *city=a.getCity();
            if(city->get_country()==country || country=="") {
                if (a.getFlights().size() > max) {
                    max = a.getFlights().size();
                    temp = a;
                }
            }
        }
    }
    return temp;
}
/**
 * Shows the ranking of the airports with the most flights
 * Complxity: O(N*K) (N being nr of related airports) (K being number of airports to be shown
 * @param tipo : "rede","pais"
 * @param country : only necessary for tipo=="pais", otherwise "";
 * @param k : Nr of lines to be shown
 */
void CSVReader::showTopKAirports(const std::string tipo, const std::string country, const int k) {
    int max=-1;
    int temp=1;
    unordered_set<Airport,AirportHash> existingAirports;
    if(tipo=="rede"){
        while(temp<=k){

            Airport target=maxFlightsAirport(max,"",existingAirports);
            existingAirports.insert(target);
            max=target.getFlights().size();
            cout<<temp<<"."<<"Aeroporto:"<<target.getName()<<"("<<target.getCode()<<")"<<endl;
            temp++;
        }
    }
    if(tipo=="pais"){
        while(temp<=k){
            Airport target=maxFlightsAirport(max,country,existingAirports);
            existingAirports.insert(target);
            max=target.getFlights().size();
            cout<<temp<<"."<<"Aeroporto:"<<target.getName()<<"("<<target.getCode()<<")"<<endl;
            temp++;
        }
    }
}

/**
 * Shows the global statistics given a type(ex: of all the web, a country or airline ),a mode (ex: statistics of nr of airports,nr of flights, nr of companies,top k airports with the most flights or companies)
 * Possible combinations: rede-nAirports, pais-nAirports, rede-nFlights,pais-nFlights,companhia aerea-nFlights, rede - top-k airports, pais - top-k airports;
 * Complexity : O(N) average (N=Nr of airports), O(N*E) worst case (N= Nr of related airports, E=Nr of related airlines)
 * @param tipo - it can be "rede","pais", or "companhia aeria"
 * @param modo - it can be "nAirports","nFlights","nAirlines","top-k airports"
 * @param country - it can be optional depends on if "pais" is involved, if not necessary then ""
 * @param airline - optional parameter only for comapnhjia aerea-nFlights for now, if not necessary then ""
 * @param k - k number of airports to be shown -optional paramenter only necessary in certain cases like "top-k airports"
 */
void CSVReader::globalStatistics(const string tipo, const std::string modo,const string country, const string airline, const int k) {
    //Case type of global statistics is all
    if(modo=="nAirports"){
        cout<<"O tipo:"<<tipo<<" foi escolhido e no total existem:"<<calculateNrAirports(tipo,country)<<" aeroportos relacionados com esse/a "<<tipo<<endl;
    }
    if(modo=="nFlights"){
        if(tipo=="pais") {
            cout << "O tipo:" << tipo << " foi escolhido e no total existem:" << calculateNrFlights(tipo, country)<< " voos relacionados com esse/a " << tipo << endl;
        }
        else if(tipo=="companhia aeria"){
            cout << "O tipo:" << tipo << " foi escolhido e no total existem:" << calculateNrFlights(tipo, airline)<< " voos relacionados com esse/a " << tipo << endl;

        }
    }
    if(modo=="nAirlines"){
        cout<<"O tipo:"<<tipo<<" foi escolhido e no total existem:"<<calculateNrAirlines(tipo,country)<<" companhias aereas relacionados com esse/a "<<tipo<<endl;
    }
    if(modo=="top-k airports"){
        cout<<"O tipo:"<<tipo<<" foi escolhido e o ranking por nr de voos é o seguinte:"<<endl;
        showTopKAirports(tipo,country,k);
    }
}


