//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETOGRUPO2_FLIGHT_H
#define PROJETOGRUPO2_FLIGHT_H

#include <string>
using namespace std;

class Flight{
public:
    string DestAirportCode;
    string AirlineCode;
    float FlightDistance;

    Flight (const string dest,const string airline,float flightDistance);
    Flight();

   bool operator==(Flight &other);
   void operator=(const Flight &other);
};

#endif //PROJETOGRUPO2_FLIGHT_H
