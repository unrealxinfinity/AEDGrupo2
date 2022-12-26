//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETOGRUPO2_FLIGHT_H
#define PROJETOGRUPO2_FLIGHT_H
#include <string>
#include "Airport.h"
using namespace std;

class Flight{
private:
    string Dest;
    string Airline;

public:
    Flight (const string dest,const string airline);
    string getDest() const;
    void setDest(const string &dest);
    const string getAirline() const;
    void setAirline(const string &airline);
};
struct FlightHash{
    int operator() (const Flight &other){
        return other.getDest().size()%14;
    }
    bool operator()(const Flight &other1, const Flight &other2){
        return (other1.getDest()==other2.getDest())&&(other1.getAirline()==other2.getAirline());
    }

};
#endif //PROJETOGRUPO2_FLIGHT_H
