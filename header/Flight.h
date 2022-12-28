//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETOGRUPO2_FLIGHT_H
#define PROJETOGRUPO2_FLIGHT_H

#include <string>
using namespace std;

class Flight{
private:
    //só usa DestAirportCode e airlineCode para Edge, OriginAirportCode serve para CSVReader;
    string  OriginAirportCode;
public:
    string DestAirportCode;
    string AirlineCode;
    float FlightDistance;

    Flight (const string dest,const string airline,float flightDistance);
    Flight();
    string getOriginAirportCode() const;

   bool operator==(Flight &other);
   void operator=(const Flight &other);
};
struct FlightHash{

    size_t operator() (const Flight &other) const{
        return  other.getOriginAirportCode().size()*rand()%100;
    }

};
struct FlightKeyEqual{
    bool operator()(const Flight &other1, const Flight &other2) const{
        return ((other1.AirlineCode==other2.AirlineCode)&&(other1.DestAirportCode==other2.DestAirportCode))? true : other1.getOriginAirportCode()==other2.getOriginAirportCode();
    }
};
#endif //PROJETOGRUPO2_FLIGHT_H
