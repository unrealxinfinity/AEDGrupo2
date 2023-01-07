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
 * @attention Complexity: O(n1 + n2 + n3) (n1 = number of lines in arlines.csv; n2 = number of lines in airports.csv; n3 = number of lines in flights.csv)
 */
void CSVReader::populate() {
    read_airports();
    read_airlines();
    read_flights();
}

/**
 * Reads airports.csv and stores the data \n
 * @attention Complexity: O(n) (n = number of lines in file)
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
 * @attention Complexity: O(n) (n = number of lines in file)
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
 * @attention Complexity: O(1) (unsure since the documentation for functions like pow() don't specify @attention Complexity)
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
 * @attention Complexity: O(n) (n = number of lines in file)
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
 * @attention Complexity: O(n) (n = number of airports)
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
 * Determines whether a flight is flown by one of the airlines in a set. If the list is empty, always returns true \n
 * @attention Complexity: O(1)
 * @param f flight in question
 * @param airlines desired airlines
 * @return true if flown by desired airlines or desired airline set is empty, false otherwise
 */
bool CSVReader::isFlownByAirline(const Flight& f,const unordered_set<string>& airline) const {
    if(airline.empty()) return true;
    Airline target= Airline(f.airline_,"","","");
    auto found=this->airlines.find(target);
    auto search = airline.find(found->getCode());
    if (search != airline.end()) return true;
    search = airline.find(found->getName());
    if (search != airline.end()) return true;
    search = airline.find(found->get_callsign());
    if (search != airline.end()) return true;
    /*auto it = airline.begin();
    while(it!=airline.end()){
        string airline_str= *it;
        if(found->getCode()== airline_str || found->getName()==airline_str||found->get_callsign()==airline_str) return true;
        it++;
    }*/
    return false;
}

/**
 * Performs a depth-first search that determines wether an airport is an articulation point or not \n
 * @attention Complexity: O(V+E) (V = number of airports, E = number of flights)
 * @param code code of airport being visited
 * @param index index of current visit
 * @param initial code of the airport that will determine the result
 * @return true if the airport is an articulation point, false otherwise
 */
bool CSVReader::dfs_art(const string &code, int index, const string& initial) {
    auto find = airports.find(Airport(code));
    find->visited = true;
    find->num = index;
    find->low = index;
    index++;
    find->in_stack = true;

    int count = 0;
    for (const auto& e : find->flights) {
        auto dest = airports.find(Airport(e.destAirportCode_));
        if (!dest->visited) {
            count++;
            if (dfs_art(e.destAirportCode_, index, initial)) return true;
            find->low = min(find->low, dest->low);
        }
        else if (dest->in_stack) {
            find->low = min(find->low, dest->num);
        }

        if (find->num != 1 && !find->is_destination && dest->low >= find->num) {
            find->is_destination = true;
            if (code == initial) return true;
        }
        else if (!find->is_destination && find->num == 1 && count > 1) {
            find->is_destination = true;
            if (code == initial) return true;
        }
    }
    return false;
}

/**
 * Determines which countries can be reached from a given airport in a given number of flights \n
 * @attention Complexity: O(V + Elog(p)) (V = number of airports, E = number of flights, p = number of distinct reachable countries)
 * @param n number of flights
 * @param source source airport code
 * @return unordered_set with the names of reachable countries
 */
set<string> CSVReader::reachableCountries(unsigned n, const string& source) {
    set<string> countries;
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
                target->visited = true;
            }
        }
    }
    return countries;
}
/**Calculates the reachable airports with n flights from an airport
 * @attention Complexity: O(N + Flog(p)) (N = Number of airports, F = number of flights, p = number of distinct reachable airports)
 * @param n flights
 * @param source source airport
 * @return set of reachable airport codes
 */
set<string> CSVReader::reachableAirports(unsigned int n, const string& source){
    set<string> reachableairports;
    for (const Airport& airport : airports) {
        airport.visited = false;
        airport.predecessor = nullptr;
    }
    queue<pair<int, string>> q;
    q.emplace(0, source);

    while (!q.empty() && q.front().first <= n) {
        auto u = q.front(); q.pop();
        auto find = airports.find(Airport(u.second));
        reachableairports.insert(find->getCode());
        for (const auto& e : find->flights) {
            string w = e.destAirportCode_;
            auto target = airports.find(Airport(w));
            if (!target->visited) {
                q.emplace(u.first + 1, w);
                target->visited = true;
            }
        }
    }
    return reachableairports;
}
/**Calculates the reachable cities from an airport
 * @attention Complexity: O(N + Flog(p)) (N=number of airports, F= Number of flights, p = number of distinct reachable cities)
 * @param n number of flights
 * @param source source airport
 * @return a pair of reachable cities and their respective countries
 */
set<pair<string,string>> CSVReader::reachableCities(unsigned int n, const std::string &source) {
    set<pair<string,string>> reachablecities;
    for (const Airport& airport : airports) {
        airport.visited = false;
        airport.predecessor = nullptr;
    }
    queue<pair<int, string>> q;
    q.emplace(0, source);

    while (!q.empty() && q.front().first <= n) {
        auto u = q.front(); q.pop();
        auto find = airports.find(Airport(u.second));
        reachablecities.insert({find->getCity()->get_name(),find->getCity()->get_country()});
        for (const auto& e : find->flights) {
            string w = e.destAirportCode_;
            auto target = airports.find(Airport(w));
            if (!target->visited) {
                q.emplace(u.first + 1, w);
                target->visited = true;
            }
        }
    }
    return reachablecities;
}

/**
 * Performs a multi-source breadth-first search to find a path between two airports
 * @attention Complexity: O(V + E) (V = number of airports, E = number of flights)
 * @param source source airport codes
 * @param dest destination airport codes
 * @param preferences desired airlines (if no preference, use empty list)
 * @return list of flights used and name of source used (useful for when there are multiple sources)
 */
pair<list<Flight>, string> CSVReader::bfs(const list<string> &source, const list<string> &dest, const unordered_set<string>& preferences) {
    list<Flight> flights;
    for (const Airport& airport : airports) {
        airport.visited = false;
        airport.is_destination = false;
        airport.predecessor = nullptr;
    }
    for (const string& s : dest) {
        auto it = airports.find(Airport(s));
        it->is_destination = true;
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
        /*bool found = false;
        for (const string& s : dest) {
            if (find->getCode() == s) found = true;
        }*/
        if (find->is_destination) {
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
 * @attention Complexity: O(n) (n = number of airports)
 * @param airportName name of airport
 * @return code of airport, empty string if airport does not exist
 */
string CSVReader::findAirportByName(const std::string& airportName,const string& city, const string& country) const {


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
 * @attention Complexity : O(n) (n = number of airports)
 * @param city name of city
 * @param country name of country
 * @return codes of all airports in the city
 */
list<string> CSVReader::findAirportByCity(const std::string& city, const std::string& country) const {
    auto it = airports.begin();
    list<string> res;
    while(it!=airports.end()){
        if(it->getCity()->get_country()==country&&it->getCity()->get_name()==city) res.push_back(it->getCode());
        it++;
    }
    return res;
}


/**
 * Decodes the input given by user following certain format
 * @attention Complexity: O(N) being N the linear search for airports with given input
 * @param src string given by user from input- can be the following formats : "(latitude,longitude)","airportName_city_country","city-country", "airportCode"
 * @param radius in case of search by coordinates, needs radius to find airports around the coordinates given by user input
 * @return list of airport codes in string
 */
list<string> CSVReader::decipherInput(const string& src,const double radius) {
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
 * Outputs in the terminal the shortest path from a source to a destination airport given any inputs by user following any kind of criteria(ex: city, coordinates, airport name/code)
 * @attention Complexity : O(V + E + n) (V = number of airports, E = number of flights, n = size of found path)
 * @param src string of source airport
 * @param dest string of destination airport
 * @param radius radius around a given coordinate to find airports
 * @param preferences list of user prefered airlines, empty means user has no airline preference
 */
void CSVReader::showShortestPath(const std::string& src,const string& dest, const double radius, const unordered_set<string>& preferences) {
    list<string>origin =this->decipherInput(src,radius);
    list<string>destination=this->decipherInput(dest,radius);
    auto travel=this->bfs(origin,destination,preferences);
    if(travel.first.empty()){
        cout<<"Nao existe voo associado."<<endl;
    }
    else {
        auto startingPointPtr = airports.find(Airport(travel.second));
        cout << "Aeroporto: " << startingPointPtr->getName() << "(" << startingPointPtr->getCode() << ")"<<endl;
        auto it = travel.first.begin();
        while (it != travel.first.end()) {
            auto airportPtr = airports.find(Airport(it->destAirportCode_));
            auto airlinePtr = airlines.find(Airline(it->airline_));
            cout << "[Pelo voo:" << airlinePtr->getName() << "(" << airlinePtr->getCode() << ")" << "]" <<endl;
            cout<< "Aeroporto: " << airportPtr->getName() << "(" << airportPtr->getCode() << ")"<<endl;
            it++;
        }
        cout << endl;
        cout << "You will need to attend " << travel.first.size() << " flights in total!" << endl;
    }
}

/**
 * Determines which flights depart at a given airport \n
 * @attention Complexity : O(n) (n = number of flights in the given airport) (Complexity is not O(1) due to copy constructor when returning the list)
 * @param cod code of airport
 * @return list of flights departing from airport
 */
list<Flight> CSVReader::flightsFromAirport(const string &cod) {
    auto it = airports.find(Airport(cod));
    if (it == airports.end()) throw -1;
    return it->flights;
}

/**
 * Determines which flights arrive at a given airport \n
 * @attention Complexity: O(n) (n = number of flights)
 * @param cod code of airport
 * @return list of pairs of source airport code and flight arriving at airport
 */
list<pair<string,Flight>> CSVReader::flightsToAirport(const string &cod) {
    list<pair<string,Flight>> res;
    for (const Airport& airport : airports)
        for (const Flight& flight : airport.flights)
            if (flight.destAirportCode_ == cod)
                res.emplace_back(airport.getCode(), flight);
    if(res.empty()) throw -1;
    return res;
}
/**
 * Calculates the nr of airports related to the whole web or by country
 * @attention Complexity: O(1) if operation done for the whole network and O(N) if its specific for a country (N = nr of related Airports);
 * @param tipo type of operation - if for the whole web or only for the country being it "rede" or "pais" respectively
 * @param country in case the operation is related to a country, it's the related country
 * @return nr or related airports
 */
int CSVReader::calculateNrAirports(const std::string& tipo,const string& country) {
    int airportCount=0;
    bool found=false;
    int error=-1;
    if(tipo=="rede"){
        return airports.size();
    }
    if(tipo=="pais"){
        for (const Airport& a :airports){
            City *city = a.getCity();
            if(city->get_country()==country){
                airportCount++;
                found=true;
            }
        }
    }
    if(!found) throw error;
    return airportCount;
}
/**Calculates the nr of flights related to the whole network or by country or by airline
 * @attention Complexity: O(1) if operation done for the whole network and O(N) if its specific for a country/airline (N= nr of related Airports);
 * @param tipo type of operation - if for the whole network or only for the country being it "rede" or "pais" or "companhia aerea" respectively
 * @param country in case the operation is related to a country/airline, it's the related country/airline
 * @return nr of flights that meet the criteria
 */
int CSVReader::calculateNrFlights(const std::string& tipo, const std::string& countryOrAirline) {
    int res=0;
    int error=-1;
    bool found=false;
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
                found=true;
            }
        }
    }
    if (tipo=="companhia aerea"){
        for(Airport a: airports){
            for(Flight f: a.getFlights()){
                if(f.airline_==countryOrAirline){
                    res++;
                    found=true;
                }
            }
        }
    }
    if(!found) throw error;
    return res;
}

/**Calculates the number of airlines;
 * Complexity: Worst Case O(N) for search type by country (N=number of airlines), O(1) case search type by the network
 * @param tipo type of search
 * @param country country to search in
 * @return number of airlines that meet the criteria
 */
int CSVReader::calculateNrAirlines(const string& tipo, const string& country) {
    int res=0;
    int error=-1;
    bool found=false;
    if(tipo=="rede"){
        return airlines.size();
    }
    if(tipo=="pais"){
        for(Airline a: airlines){
            if(a.getCountry()==country){
                res++;
                found=true;
            }
        }
    }
    if(!found) throw error;
    return res;
}
/**Searches for the airport with the max nr of flights
 * @attention Complexity: O(N) (N = number of airports)
 * @param prevMax given this max the function searches the airport with max nr of flights but that max has to be <= than actual max
 * @param country country case search criteria is by country
 * @param existingAirports airports already found to be avoided
 * @return airport with the max nr of flights
 */
Airport CSVReader::maxFlightsAirport(const int prevMax,const string& country,const unordered_set<Airport,AirportHash>& existingAirports) {
    int max=0;
    int error=-1;
    bool found=false;
    Airport temp;
    if(prevMax!=-1){
        for(Airport a: airports){
            City *city=a.getCity();
            if(city->get_country()==country || country.empty()) {
                if (existingAirports.find(a) == nullptr &&  a.getFlights().size() <= prevMax) {
                    if (a.getFlights().size() > max) {
                        max = a.getFlights().size();
                        temp = a;
                    }
                }
                found=true;
            }
        }

    }
    else{
        for(const Airport& a: airports){
            City *city=a.getCity();
            if(city->get_country()==country || country.empty()) {
                if (a.getFlights().size() > max) {
                    max = a.getFlights().size();
                    temp = a;
                }
                found=true;
            }
        }
    }
    if(!found) throw error;
    return temp;
}
/**
 * Shows the ranking of the airports with the most flights
 *@attention Complexity : O(N*K) (N = nr of related airports, K = number of airports to be shown)
 * @param tipo "rede","pais" according to desired type of search
 * @param country only necessary for tipo=="pais", otherwise ""
 * @param k nr of lines to be shown
 */
void CSVReader::showTopKAirports(const std::string& tipo, const std::string& country, const int k) {
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
 * Shows the global statistics given a type(ex: of all the network, a country or airline ),a mode (ex: statistics of nr of airports,nr of flights, nr of companies,top k airports with the most flights or companies) \n
 * Possible combinations: rede-nAirports, pais-nAirports, rede-nFlights, pais-nFlights, companhia aerea-nFlights, rede - top-k airports, pais - top-k airports;
 * @attention Complexity : O(N) average (N = Nr of airports), O(N * E) worst case (N = Nr of related airports, E = Nr of related airlines)
 * @param tipo it can be "rede","pais", or "companhia aerea"
 * @param modo it can be "nAirports","nFlights","nAirlines","top-k airports"
 * @param country it can be optional depends on if "pais" is involved, if not necessary then ""
 * @param airline optional parameter, only for companhia aerea-nFlights for now, if not necessary then ""
 * @param k  number of airports to be shown - optional parameter, only necessary in certain cases like "top-k airports"
 */
void CSVReader::globalStatistics(const string& tipo, const std::string& modo,const string& country, const string& airline, const int k) {
    int error=-1;
    //Case type of global statistics is all
    if(modo=="nAirports"){
        cout<<"O tipo:"<<tipo<<" foi escolhido e no total existem:"<<calculateNrAirports(tipo,country)<<" aeroportos relacionados com esse/a "<<tipo<<endl;
    }
    if(modo=="nFlights"){
        if(tipo=="pais") {
            cout << "O tipo:" << tipo << " foi escolhido e no total existem:" << calculateNrFlights(tipo, country)<< " voos relacionados com esse/a " << tipo << endl;
        }
        else if(tipo=="companhia aerea"){
            cout << "O tipo:" << tipo << " foi escolhido e no total existem:" << calculateNrFlights(tipo, airline)<< " voos relacionados com esse/a " << tipo << endl;

        }
    }
    if(modo=="nAirlines"){
        cout<<"O tipo:"<<tipo<<" foi escolhido e no total existem:"<<calculateNrAirlines(tipo,country)<<" companhias aereas relacionados com esse/a "<<tipo<<endl;
    }
    if(modo=="top-k airports"){
        if(k<=0) throw error;
        cout<<"O tipo:"<<tipo<<" foi escolhido e o ranking por nr de voos é o seguinte:"<<endl;
        showTopKAirports(tipo,country,k);
    }
}
/**Calculates airlines that have flights on the airport
 * @attention Complexity: O(nlog(m)) (n = number of flights the airport has; m = number of distinct airlines from airport)
 * @param cod airport code
 * @return set of unique Airlines that has flights on the airport
 */
set<Airline> CSVReader::airlinesFromAirport(const std::string &cod) {
    set<Airline> uniqueAirlines;
    list<Flight> temp= flightsFromAirport(cod);
    for(Flight a : temp){
        auto ins=airlines.find(Airline(a.airline_,"","",""));
        uniqueAirlines.insert(*ins);
    }
    return uniqueAirlines;
}
/**Checks for the flights that arrive at a specific airport \n
 *
 * @attention Complexity: O(n + mlog(p)) (n = number of airports; m = number of flights to airport; p = number of distinct airlines to airport)
 * @param cod airport Code
 * @return set of unique airlines that arrive at the airport
 */
set<Airline> CSVReader::airlinesToAirport(const std::string &cod) {
    set<Airline> uniqueAirlines;
    auto temp = flightsToAirport(cod);
    for(const auto& a : temp){
        auto ins=airlines.find(Airline(a.second.airline_,"","",""));
        uniqueAirlines.insert(*ins);
    }
    return uniqueAirlines;
}
/**Checks for the dest countries that flights from a certain airport reach
 * @attention Complexity: O(nlog(m)) (n = number of flights the airport has; m = number of distinct countries from airport)
 * @param cod airport code
 * @return set of unique names of countries
 */
set<string> CSVReader::countriesFromAirport(const std::string &cod) {
    auto temp= flightsFromAirport(cod);
    set<string> countries;
    for(const Flight& f:temp){
        auto targetIt= airports.find(Airport(f.destAirportCode_));
        City *cityP=targetIt->getCity();
        countries.insert(cityP->get_country());
    }
    return countries;
}
/** Checks for the source countries of the flights
 * @attention Complexity: O(n + mlog(p)) (n = number of airports; m = number of flights to airport; p = number of distinct countries to airport)
 * @param cod airport code
 * @return set of unique countries that arrive at airport
 */
set<string> CSVReader::countriesToAirport(const std::string &cod) {
    list<pair<string,Flight>> flights= flightsToAirport(cod);
    set<string> countries;
    for (const auto& p:flights){
        auto targetIt=airports.find(Airport(p.first));
        City *cityP=targetIt->getCity();
        countries.insert(cityP->get_country());
    }
    return countries;
}

/** Calculates the cities that are reachable by the outgoing flights in that airport
 * @attention Complexity: O(nlog(m)) (n = number of flights the airport has; m = number of distinct cities from airport)
 * @param cod airport code
 * @return set of cities with pair of respective airportCode-country
 */
set<pair<string,pair<string,string>>> CSVReader::citiesFromAirport(const std::string &cod) {
    list<Flight> temp= flightsFromAirport(cod);
    set<pair<string,pair<string,string>>> res;
    for(Flight f:temp){
        auto targetIt= airports.find(Airport(f.destAirportCode_));
        City *cityP=targetIt->getCity();
        res.insert({cityP->get_name(),{targetIt->getCode(),cityP->get_country()}});
    }
    return res;
}

/** Calculate the source cities of incoming flights to an airport
 * @attention Complexity: O(n + mlog(p)) (n = number of airports; m = number of flights to airport; p = number of distinct cities to airport)
 * @param cod airport code
 * @return set of cities with pair of respective airportCode-country
 */
set<pair<string,pair<string,string>>> CSVReader::citiesToAirport(const std::string &cod) {
    list<pair<string, Flight>> flights = flightsToAirport(cod);
    set<pair<string,pair<string,string>>> res;
    for (const auto &p: flights) {
        auto targetIt = airports.find(Airport(p.first));
        City *cityP = targetIt->getCity();
        res.insert({cityP->get_name(),{targetIt->getCode(),cityP->get_country()}});
    }
    return res;
}

/**
 * Determines wether a given airport is an articulation point in the network \n
 * @attention Complexity: O(V + E) (V = number of airports, E = number of flights)
 * @param code code of airport
 * @return true if airport is an articulation point, false otherwise
 */
bool CSVReader::isArticulationPoint(const string &code) {
    for (const Airport& airport : airports) {
        airport.visited = false;
        airport.in_stack = false;
        airport.is_destination = false;
    }
    stack<string> s;
    for (const Airport& airport : airports)
        if (!airport.visited) {
            dfs_art(airport.getCode(), 1, airport.getCode());
            auto find = airports.find(Airport(code));
            if (find->visited)
                return find->is_destination;
        }
    return false;
}
