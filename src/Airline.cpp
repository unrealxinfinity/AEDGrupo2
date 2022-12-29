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
bool Airline::operator==(const Airline &other) const {
    return code==other.getCode();
}
