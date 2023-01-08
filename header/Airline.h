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
    string getCountry() const;
    bool operator==(const Airline& other) const;
    bool operator <(const Airline& other) const;
};

struct AirlineHash{
    size_t operator() (const Airline& other) const{
        return hash<string>()(other.getCode());
    }
};

#endif //PROJETOGRUPO2_AIRLINE_H
