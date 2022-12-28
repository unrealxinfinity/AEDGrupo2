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
        size_t res = 0;
        for (char c : other.get_country()) {
            res += 17 * c;
        }
        for (char c : other.get_name()) {
            res += 41 * c;
        }
        return res;
    }
};

#endif //PROJETOGRUPO2_CITY_H
