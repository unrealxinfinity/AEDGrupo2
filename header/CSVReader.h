//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETOGRUPO2_CSVREADER_H
#define PROJETOGRUPO2_CSVREADER_H
#include <string>
#include "airportsGraph.h"

using namespace std;

class CSVReader {
private:
        string filename;
public:
    //supposed idea to use CSV reader in the graph constructor to fill the airports set of the its field
    void readAirports(unordered_set<Airport,airportHash,airportHash> &airports,string filename);
    void readFlights(list<Flight> &flights,string filename);

};


#endif //PROJETOGRUPO2_CSVREADER_H
