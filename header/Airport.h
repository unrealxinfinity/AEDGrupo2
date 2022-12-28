//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETOGRUPO2_AIRPORT_H
#define PROJETOGRUPO2_AIRPORT_H
#include <unordered_set>
#include<math.h>
#include <List>
#include<string>
#include "Flight.h"

using namespace std;

class Airport {
private:
    string Code;
    string Name;
    string City;
    float Latitude;
    float Longitude;

public:

    list<Flight> flights;

    Airport(string code,string name,string city,float latitude,float longitude);
    Airport();

    bool visited;
    int distanceSince;

    void addFlight(Flight f){
        flights.push_back(f);
    }
    string getCode() const;
    list<Flight>getFlights() const;
    float getLongitude() const;
    float getLatitude() const;
    string getName() const;
    string getCity() const;
    float calcDistanceHaversine(Airport &b);
    void operator=(Airport &other) ;
    bool operator ==(Airport &other);


};

//Melhorar em termos de hash function que eu nao sei o que por c,:
struct airportHash {
    int operator() (const Airport &other){
        return other.getFlights().size()%10;
    }
    //queria implementar uma cena que fizesse com o struct levasse um argumento tipo float para verificar que dist de 2 airports <X faz com que key seja igual ao outro key
    bool operator()(const Airport &a,Airport &b){
        return (a.getCode()==b.getCode()) ;
    }
};


#endif //PROJETOGRUPO2_AIRPORT_H
