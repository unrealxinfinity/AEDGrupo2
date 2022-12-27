//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETOGRUPO2_AIRPORT_H
#define PROJETOGRUPO2_AIRPORT_H
#include <unordered_set>
#include<math.h>
#include <List>
#include<string>

using namespace std;

class Airport {
private:
    string Code;
    string Name;
    string City;
    float Latitude;
    float Longitude;

public:

    struct Flight{
        Airport* Dist;
        string Airline;
        float FlightDistance;

    };
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
    float calcDistanceHaversine(Airport &a, Airport &b);
    void operator=(Airport &other) ;
    }
};

struct airportHash{
    int operator() (const Airport &other){
        return other.getFlights().size()%10;
    }
    bool operator()(const Airport &a,Airport &b){
        return (a.getCode()==b.getCode()) ;
    }
};

#endif //PROJETOGRUPO2_AIRPORT_H
