//
// Created by fuhao on 26/12/2022.
//
#include "Flight.h"

Flight::Flight(const string dest, const std::string airline,const float flightDistance) : destAirportCode_(dest), airlineCode_(airline), flightDistance_(flightDistance){}
Flight::Flight() {
    destAirportCode_ == "";
    airlineCode_ == "";
    flightDistance_=0;
}
bool Flight::operator==(Flight &other) {
    return this->destAirportCode_ == other.destAirportCode_ && this->airlineCode_ == other.airlineCode_ ;
}

void Flight::operator=(const Flight &other){
    this->airlineCode_=other.airlineCode_;
    this->destAirportCode_=other.destAirportCode_;
    this->flightDistance_=other.flightDistance_;
}


