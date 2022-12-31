//
// Created by Afonso on 28/12/02022.
//

#ifndef PROJETOGRUPO2_AIRLINE_H
#define PROJETOGRUPO2_AIRLINE_H

#include <string>

using namespace std;

class Airline {
private:
    string code;
    string name;
    string callsign;
    string country;
public:
    Airline(string code, string name, string callsign, string country);
    explicit Airline(string code);
    Airline();
    string get_callsign() const;
    string getCode() const;
    string getName() const;
    bool operator==(const Airline& other) const;
};

struct AirlineHash{
    size_t operator() (const Airline& other) const{
        size_t res = 0;
        for (char c : other.getCode()) {
            res += 13 * c;
        }
        return res;
    }
};

#endif //PROJETOGRUPO2_AIRLINE_H
