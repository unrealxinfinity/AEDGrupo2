#include <iostream>
#include "Airport.h"
#include "airportsGraph.h"
#include <unordered_set>

//temp section for tests
void testsAirportEqualAndAssignment(){
    Airport airportTest= Airport("BCN","BarcelonaAirport","Barcelona",1,1);
    Airport airportTest2= Airport("ABD","BarcelonaAirport","Barcelona",1,1);
    Airport temp;
    airportTest2=airportTest;

    cout<<airportTest2.getCode()<<endl;
    cout<<(airportTest2==airportTest)<<endl;

}
void testUnorderedSetFlights(){
    typedef unordered_set<Flight,FlightHash,FlightKeyEqual> Flights;
    Flights flights;
    Flight temp=Flight("Ola","Teste",0);
    Flight target=Flight("Ola","",1);
    flights.insert(temp);
    auto res = flights.find(target);

    cout<<res->getOriginAirportCode()<<res->DestAirportCode<<res->AirlineCode<<res->FlightDistance<<endl;

}

int main() {

    testUnorderedSetFlights();
    return 0;
}
