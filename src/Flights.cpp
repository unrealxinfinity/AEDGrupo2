//
// Created by fuhao on 26/12/2022.
//
#include "Flight.h"

Flight::Flight(const string dest, const std::string airline,const float flightDistance) : DestAirportCode(dest), AirlineCode(airline),FlightDistance(flightDistance){}

bool Flight::operator==(Flight &other) {
    return this->getDestAirportCode()==other.getDestAirportCode() && this->getDestAirportCode() ==other.getDestAirportCode();
}
string Flight::getDestAirportCode() const {
    return DestAirportCode;
}
float Flight::getFlightDistance() const{
    return FlightDistance;
}

void Flight::setDestAirportCode(const std::string &dest) {
    DestAirportCode=dest;
}

const string Flight::getAirlineCode() const {
    return AirlineCode;
}

void Flight::setAirline(const string &airline) {
    AirlineCode = airline;
}
