//
// Created by fuhao on 26/12/2022.
//
#include "Flight.h"

Flight::Flight(const string dest, const std::string airline,const float flightDistance) : DestAirportCode(dest), AirlineCode(airline),FlightDistance(flightDistance){}
Flight::Flight() {
    OriginAirportCode=="";
    DestAirportCode=="";
    AirlineCode=="";
    FlightDistance=0;
}
bool Flight::operator==(Flight &other) {
    return this->DestAirportCode==other.DestAirportCode && this->AirlineCode ==other.AirlineCode && this->getOriginAirportCode()==other.getOriginAirportCode();
}

void Flight::operator=(const Flight &other){
    this->OriginAirportCode=other.getOriginAirportCode();
    this->AirlineCode=other.AirlineCode;
    this->DestAirportCode=other.DestAirportCode;
    this->FlightDistance=other.FlightDistance;
}

string Flight::getOriginAirportCode() const {
    return OriginAirportCode;
}

