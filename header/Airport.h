//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETO_GRUPO2_AIRPORT_H
#define PROJETO_GRUPO2_AIRPORT_H
#include "Flight.h"
#include <unordered_set>
using namespace std;

typedef unordered_set<Flight,FlightHash,FlightHash> Flights;

class Airport {
private:
    string Code;
    string Name;
    string City;
    float Latitude;
    float Longitude;
    Flights flights;
    bool visited;
    int distance;
public:

    Airport(string code,string name,string city,float latitude,float longitude);

    void addFlight(Flight f){
        flights.insert(f);
    }
    string getCode() const;
    unordered_set<Flight> getFlights() const;
};
struct airportHash{
    int operator() (const Airport &other){
        return other.getFlights().size()%10
    }
};

#endif //PROJETO_GRUPO2_AIRPORT_H
