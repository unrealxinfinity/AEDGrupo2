//
// Created by fuhao on 28/12/2022.
//

#include <fstream>
#include <sstream>
#include "CSVReader.h"
using namespace std;

CSVReader::CSVReader() = default;



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
        it->addFlight(Flight(target, airline, 0));
    }
    in.close();
}
unordered_set<Airport, AirportHash> CSVReader::getAirports() {
    return airports;
}

