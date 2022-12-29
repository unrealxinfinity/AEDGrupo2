//
// Created by fuhao on 26/12/2022.
//

#include "airportsGraph.h"
using namespace std;

/*airportsGraph::airportsGraph(CSVReader reader,bool dir){

}*/
airportsGraph::airportsGraph() {
    CSVReader reader;
    reader.populate();
    airports=reader.getAirports();
}
Airport airportsGraph::findAirportByCoord(const double lat, const double longi) const{
    auto it=airports.begin();
    while(it!=airports.end()){
        if(it->getLatitude()==lat&&it->getLongitude()==longi) return *it;
        it++;
    }
}
unordered_set<Airport,AirportHash> airportsGraph::findAirportsAround(const double lat, const double longi,
                                                                     const double radius) const {
    auto it= airports.begin();
    Airport center= findAirportByCoord(lat,longi);
    Airports temp;
    temp.insert(center);
    while(it!=airports.end()){
        if(center.calcDistanceHaversine(*it) <= radius){
            temp.insert(*it);
        }
        it++;
    }

    return temp;
}

unordered_set<Airport,AirportHash> airportsGraph::getAirports() {
    return  airports;
}

bool airportsGraph::isFlownByAirline(const Flight f,list<string> airlines) const {
    if(airlines.empty()) return true;
    auto it = airlines.begin();
    while(it!=airlines.end()){
        //TODO
        //auto find = airlines.find(Airline(*it));
        //if(f.airline_.getCode()==airline || f.airline_.get_callsign()==airline||f.airline_.getName()==airline) return true;
        it++;
    }
    return false;
}




