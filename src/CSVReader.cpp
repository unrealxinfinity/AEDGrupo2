//
// Created by fuhao on 28/12/2022.
//

#include "CSVReader.h"
using namespace std;

CSVReader::CSVReader() {
    filename="";
}
CSVReader::CSVReader(std::string Flightsfilename) {
    filename=Flightsfilename;
}
/*
void CSVReader::readAirports(unordered_set<Airport,airportHash,airportKeyEqual> &airports,string filename){

}*/
