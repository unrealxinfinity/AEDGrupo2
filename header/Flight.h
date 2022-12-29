//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETOGRUPO2_FLIGHT_H
#define PROJETOGRUPO2_FLIGHT_H
#include <string>
#include "Airline.h"
using namespace std;

class Flight{
public:
    string destAirportCode_;
    string airline_;
   // string airlineCode_;
    float flightDistance_;


   // Flight (const string dest,const string airline,float flightDistance);
    Flight (const string dest,string airline, double flightDistance);
    Flight();

   bool operator==(Flight &other) const;
   Flight& operator=(const Flight &other);
};

#endif //PROJETOGRUPO2_FLIGHT_H
