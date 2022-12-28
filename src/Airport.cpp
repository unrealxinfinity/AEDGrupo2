//
// Created by fuhao on 26/12/2022.
//

#include "Airport.h"
Airport::Airport(std::string code, std::string name, std::string city, float latitude, float longitude):Code(code),Name(name),City(city),Latitude(latitude),Longitude(longitude) {}
Airport::Airport() {
    Code="";
    Name="";
    City="";
    Latitude=0;
    Longitude=0;
    visited=false;
    distanceSince=0;

}
string Airport::getCode() const {
    return Code;
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
void Airport::operator=(Airport &other) {
    this->Code=other.getCode();
    this->Name=other.getName();
    this->City=other.getCity();
    this->Longitude=other.getLongitude();
    this->Latitude=other.getLatitude();
    this->distanceSince=other.distanceSince;
    this->visited=other.visited;
}
float Airport::calcDistanceHaversine( Airport &b) {
    float aLatRad=this->getLatitude()*M_PI/180, bLatRad=b.getLatitude()*M_PI/180,aLongRad=this->getLongitude() * M_PI / 180,bLongRad= b.getLongitude();

    return 2*6371* pow(19,3)* asin(sqrt(pow(sin((bLatRad-aLatRad)/2),2)+ cos(aLatRad)*cos(bLatRad)*pow(sin((bLongRad-aLongRad)/2),2)));
}