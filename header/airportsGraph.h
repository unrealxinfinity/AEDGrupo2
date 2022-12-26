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
typedef unordered_set<Airport,airportHash,airportHash> Airports;
class airportsGraph{
    Airports airports;
    bool hasDir;
public:
    void bfs();
    airportsGraph(string airpotsCSV,string flightsCSV ,CSVReader reader,bool dir=true);
    int distance(string airportA,string airportB);


};

#endif //PROJETOGRUPO2_AIRPORTSGRAPH_H
