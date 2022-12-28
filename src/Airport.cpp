//
// Created by fuhao on 26/12/2022.
//

#include "Airport.h"
Airport::Airport(std::string code, std::string name, const City* city, double latitude, double longitude):Code(code),Name(name),city(city),Latitude(latitude),Longitude(longitude) {}

string Airport::getCode() const {
    return Code;
}

string Airport::getName() const {
    return Name;
}
City* Airport::getCity() const {
    return const_cast<City *>(city);
}
double Airport::getLongitude() const {
    return Longitude;
}
double Airport::getLatitude() const {
    return Latitude;
}
void Airport::operator=(const Airport &other) {
    this->Code=other.getCode();
    this->Name=other.getName();
    this->city=other.getCity();
    this->Longitude=other.getLongitude();
    this->Latitude=other.getLatitude();
    this->distanceSince=other.distanceSince;
    this->visited=other.visited;
}
bool Airport::operator==(const Airport &other) const{
    return this->getCode()==other.getCode();
}
float Airport::calcDistanceHaversine( Airport &b) {
    float aLatRad=this->getLatitude()*M_PI/180, bLatRad=b.getLatitude()*M_PI/180,aLongRad=this->getLongitude() * M_PI / 180,bLongRad= b.getLongitude();

    return 2*6371* pow(19,3)* asin(sqrt(pow(sin((bLatRad-aLatRad)/2),2)+ cos(aLatRad)*cos(bLatRad)*pow(sin((bLongRad-aLongRad)/2),2)));
}