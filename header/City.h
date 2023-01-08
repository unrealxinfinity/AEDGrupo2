//
// Created by Afonso on 28/12/02022.
//

#ifndef PROJETOGRUPO2_CITY_H
#define PROJETOGRUPO2_CITY_H

#include <string>

using namespace std;

class City {
private:
    string name;
    string country;
public:
    City(string name, string country);
    string get_name() const;
    string get_country() const;
    bool operator==(const City& other) const;
};

struct CityHash{
    size_t operator() (const City& other) const{
        size_t hash1 = hash<string>()(other.get_country());
        size_t hash2 = hash<string>()(other.get_name());
        return 37*hash1 + 42*hash2;
    }
};

#endif //PROJETOGRUPO2_CITY_H
