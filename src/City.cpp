//
// Created by Afonso on 28/12/02022.
//
#include "City.h"

City::City(string name, string country): name(name), country(country) {}

string City::get_name() const {
    return name;
}

string City::get_country() const {
    return country;
}

bool City::operator==(const City &other) const {
    return name == other.get_name() && country == other.get_country();
}

