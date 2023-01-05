//
// Created by Afonso on 28/12/02022.
//

#include "../header/Airline.h"

Airline::Airline(string code, string name, string callsign, string country): code(code), name(name), callsign(callsign), country(country) {}

string Airline::get_callsign() const {
    return callsign;
}
Airline::Airline() {
    code="";
    callsign="";
    name="";
    country="";
}
string Airline::getCode() const {
    return code;
}
string Airline::getName() const {
    return name;
}
string Airline::getCountry() const {
    return country;
}
bool Airline::operator==(const Airline &other) const {
    return code==other.getCode();
}

Airline::Airline(string code): code(code) {}
bool Airline::operator<(const Airline &other) const {
    if(this->getName()<other.getName()) return true;
    else if(this->getName()==other.getName()){
        if(this->get_callsign()<other.get_callsign()) return true;
        else if(this->get_callsign()==other.get_callsign()){
            return  this->getCode()<other.getCode();
        }
    }
    return false;
}