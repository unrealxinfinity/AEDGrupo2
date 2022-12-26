//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETOGRUPO2_FLIGHT_H
#define PROJETOGRUPO2_FLIGHT_H
#include <string>
#include "Airport.h"
#include "Airport.h"
using namespace std;

class Flight{
private:
    Airport Dest;
    string Airline;
    static int hashint;
public:
    Flight (const string dest,const string airline);
    Airport getDest() const;
    void setDest(const Airport &dest);
    const string getAirline() const;
    void setAirline(const string &airline);

};
struct FlightHash{
    int operator() (const Flight &other){
        return other.getDest().size()%14;
    }
    bool operator()(const Flight &other1, const Flight &other2){

    }

};
#endif //PROJETOGRUPO2_FLIGHT_H
