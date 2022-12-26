//
// Created by fuhao on 26/12/2022.
//

#include "Flight.h"
Flight::Flight(const string dest, const std::string airline) :Dest(dest),Airline(airline){}

string Flight::getDest() const {
    return Dest;
}

void Flight::setDest(const string &dest) {
    Dest = dest;
}

const string Flight::getAirline() const {
    return Airline;
}

void Flight::setAirline(const string &airline) {
    Airline = airline;
}
