//
// Created by fuhao on 26/12/2022.
//
#include "Flight.h"

//Flight::Flight(const string dest, const std::string airline,const float flightDistance) : destAirportCode_(dest), airlineCode_(airline), flightDistance_(flightDistance){}
Flight::Flight(const string dest, string airline, double flightDistance) {
    destAirportCode_=dest;
    airline_=airline;
    flightDistance_=flightDistance;
}
Flight::Flight() {
    destAirportCode_ == "";
   // airlineCode_ == "";
    flightDistance_=0;
}
bool Flight::operator==(Flight &other) const {
    return this->destAirportCode_ == other.destAirportCode_ && this->airline_==other.airline_;// this->airlineCode_ == other.airlineCode_ ;
}

Flight& Flight::operator=(const Flight &other){
    //this->airlineCode_=other.airlineCode_;
    this->airline_=other.airline_;
    this->destAirportCode_=other.destAirportCode_;
    this->flightDistance_=other.flightDistance_;
    return *this;
}


