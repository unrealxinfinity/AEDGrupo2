//
// Created by fuhao on 26/12/2022.
//

#include "Airport.h"
Airport::Airport(std::string code, std::string name, std::string city, float latitude, float longitude):Code(code),Name(name),City(city),Latitude(latitude),Longitude(longitude) {}

string Airport::getCode() const {
    return Code;
}
unordered_set<Flight> Airport::getFlights() const {
    return flights;
}