//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETOGRUPO2_AIRPORT_H
#define PROJETOGRUPO2_AIRPORT_H

#include <unordered_set>
#include<math.h>
#include <List>
#include<string>
#include <iostream>
#include "Flight.h"
#include "City.h"

using namespace std;

class Airport {
private:
    string code_;
    string name_;
    const City* city_;
    double latitude_;
    double longitude_;

public:
    mutable list<Flight> flights;
    mutable Flight* predecessor;
    mutable string predecessor_code;

    Airport(string code,string name,const City* city,double latitude,double longitude);
    explicit Airport(string code);
    Airport();

    mutable bool visited;
    mutable bool is_destination;
    mutable bool in_stack;
    mutable int num;
    mutable int low;
    double distanceSince;

    void addFlight(Flight f) const{
        flights.push_back(f);
    }

    string getCode() const;

    list<Flight>getFlights() const;

    double getLongitude() const;
    double getLatitude() const;
    string getName() const;
    City* getCity() const;
    double calcDistanceHaversine(const Airport &b) const;
    void operator=(const Airport &other)  ;
    bool operator==(const Airport &other) const;


};

struct AirportHash {
    size_t operator() (const Airport& other) const{
        return hash<string>()(other.getCode());
    }
};



#endif //PROJETOGRUPO2_AIRPORT_H
