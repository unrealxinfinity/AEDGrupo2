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

//Melhorar em termos de hash function que eu nao sei o que por c,:
struct AirportHash {
    size_t operator() (const Airport& other) const{
        size_t res = 0;
        for (char c : other.getCode()) {
            res += 37*c;
        }
        return res;
    }
    //queria implementar uma cena que fizesse com o struct levasse um argumento tipo float para verificar que dist de 2 airports <X faz com que key seja igual ao outro key

};
//esta KeyCompare nao funciona for some reason
struct AirportKeyEqual{
    bool operator()(const Airport *a , const Airport *b) const{
        return a==b; // a->getCode()==b->getCode() ;
    }
};


#endif //PROJETOGRUPO2_AIRPORT_H
