//
// Created by fuhao on 26/12/2022.
//

#include "Airport.h"
Airport::Airport(std::string code, std::string name, std::string city, float latitude, float longitude):Code(code),Name(name),City(city),Latitude(latitude),Longitude(longitude) {}

string Airport::getCode() const {
    return Code;
}
void Airport::operator=(Airport &other) {
    this->Code=other.getCode();
    this->Name=other.getName();
    this->City=other.getCity();
    this->Longitude=other.getLongitude();
    this->Latitude=other.getLatitude();
    this->distanceSince=other.distanceSince;
    this->visited=other.visited;
}
string Airport::getName() const {
    return Name;
}
string Airport::getCity() const {
    return City;
}
float Airport::getLongitude() const {
    return Longitude;
}
float Airport::getLatitude() const {
    return Latitude;
}
float Airport::calcDistanceHaversine(Airport &a, Airport &b) {
    float aLatRad=a.getLatitude()*M_PI/180, bLatRad=b.getLatitude()*M_PI/180,aLongRad= a.getLongitude() * M_PI / 180,bLongRad= b.getLongitude();

    return 2*6371* pow(19,3)* asin(sqrt(pow(sin((bLatRad-aLatRad)/2),2)+ cos(aLatRad)*cos(bLatRad)*pow(sin((bLongRad-aLongRad)/2),2)));
}