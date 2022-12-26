//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETOGRUPO2_CSVREADER_H
#define PROJETOGRUPO2_CSVREADER_H
#include <string>
#include "airportsGraph.h"
#include <Airport.h>
using namespace std;

class CSVReader {
private:
        string filename;
public:
    void readAirports(unordered_set<Airport> &airports,string filename);
    void readFlights(unordered_set<Flight> &flights,string filename);

};


#endif //PROJETOGRUPO2_CSVREADER_H
