//
// Created by fuhao on 26/12/2022.
//
#include "Flight.h"

Flight::Flight(const Airport dest, const std::string airline) :Dest(dest),Airline(airline){}

Airport Flight::getDest() const {
    return Dest;
}

void Flight::setDest(const Airport &dest) {
    Dest = dest;
}

const string Flight::getAirline() const {
    return Airline;
}

void Flight::setAirline(const string &airline) {
    Airline = airline;
}
