//
// Created by fuhao on 26/12/2022.
//

#include "Airport.h"
Airport::Airport(std::string code, std::string name, const City* city, double latitude, double longitude): code_(code), name_(name), city_(city), latitude_(latitude), longitude_(longitude) {}
Airport::Airport() {
    code_="";
    name_="";
    city_= nullptr;
    latitude_=0;
    longitude_=0;

}
string Airport::getCode() const {
    return code_;
}

string Airport::getName() const {
    return name_;
}
City* Airport::getCity() const {
    return const_cast<City *>(city_);
}
double Airport::getLongitude() const {
    return longitude_;
}
double Airport::getLatitude() const {
    return latitude_;
}
list<Flight> Airport::getFlights() const {
    return flights;
}
void Airport::operator=(const Airport &other) {
    this->code_=other.getCode();
    this->name_=other.getName();
    this->city_=other.getCity();
    this->longitude_=other.getLongitude();
    this->latitude_=other.getLatitude();
    this->distanceSince=other.distanceSince;
    this->visited=other.visited;
    this->flights =other.getFlights();
}
bool Airport::operator==(const Airport &other) const{
    return this->getCode()==other.getCode();
}

/**
 * Calculates the distance between two points using the Haversine formula \n
 * @attention Complexity: O(1) (unsure since the documentation for functions like pow() don't specify @attention Complexity)
 * @param b second airport for calculation
 * @return distance between two points
 */
double Airport::calcDistanceHaversine(const Airport &b) const{
    double aLatRad=this->getLatitude()*M_PI/180;
    double bLatRad=b.getLatitude()*M_PI/180;
    double aLongRad=this->getLongitude() * M_PI / 180;
    double bLongRad= b.getLongitude()*M_PI/180;

    return 2*6371*asin(sqrt(pow(sin((bLatRad-aLatRad)/2),2)+ cos(aLatRad)*cos(bLatRad)*pow(sin((bLongRad-aLongRad)/2),2)));
}
Airport::Airport(string code): code_(code) {}
