//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETOGRUPO2_AIRPORTSGRAPH_H
#define PROJETOGRUPO2_AIRPORTSGRAPH_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Airport.h"
#include "Flight.h"
#include "CSVReader.h"
using namespace std;

typedef unordered_set<Airport,AirportHash> Airports;
class airportsGraph{
    Airports airports;

private:
    bool hasDir;

    //checks if a flight is flown by an airline, parameter airlines accepts callsign ,code or name, empty means all airlines are accepted;
    //Used for bfs , idea is to bfs_visit those flights that isFlownByAirline evaluates true maybe? But I believe this function will be useful;
    // complexity O(N) being N the size of the list of airlines the user provides;
    bool isFlownByAirline(const Flight f,list<string> airline) const;

public:
    void bfs(Airport &from);


    //airportsGraph(CSVReader reader,bool dir=true);
    airportsGraph();
    unordered_set<Airport,AirportHash> getAirports();

    //encontra os aeroportos a partir de um centro, retorna unordered set
    unordered_set<Airport,AirportHash> findAirportsAround(const double lat,const double longi,const double x)const;
    Airport findAirportByCoord(const double lat, const double longi) const;
    int distance(string airportA,string airportB);




};

#endif //PROJETOGRUPO2_AIRPORTSGRAPH_H
