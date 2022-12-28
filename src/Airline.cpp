//
// Created by Afonso on 28/12/02022.
//

#include "../header/Airline.h"

Airline::Airline(string code, string name, string callsign, string country): code(code), name(name), callsign(callsign), country(country) {}

string Airline::get_callsign() const {
    return callsign;
}

bool Airline::operator==(const Airline &other) const {
    return callsign == other.get_callsign();
}
