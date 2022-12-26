//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETOGRUPO2_AIRPORT_H
#define PROJETOGRUPO2_AIRPORT_H
#include "Flight.h"
#include <unordered_set>
using namespace std;

typedef unordered_set<Flight,FlightHash,FlightHash> FlightsSet;
class Airport {
private:
    string Code;
    string Name;
    string City;
    float Latitude;
    float Longitude;
    FlightsSet flights;
    bool visited;
    int distance;
public:

    Airport(string code,string name,string city,float latitude,float longitude);
    Airport();
    void addFlight(Flight f){
        flights.insert(f);
    }
    string getCode() const;
    FlightsSet getFlights() const;
};

struct airportHash{
    int operator() (const Airport &other){
        return other.getFlights().size()%10
    }
    bool operator()(const Airport &a,Airport &b){
        return (a.getCode()==b.getCode());
    }
};

#endif //PROJETOGRUPO2_AIRPORT_H
