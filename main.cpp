#include <iostream>
#include "Airport.h"
#include "airportsGraph.h"
#include <unordered_set>

//temp section for tests
//Tested
void testsAirportEqualAndAssignment(){
    Airport airportTest= Airport("BCN","BarcelonaAirport","Barcelona",1,1);
    Airport airportTest2= Airport("ABD","BarcelonaAirport","Barcelona",1,1);
    Airport temp;
    airportTest2=airportTest;

    cout<<airportTest2.getCode()<<endl;
    cout<<(airportTest2==airportTest)<<endl;

}
//error
void airportSetTest(){
    typedef unordered_set<Airport,AirportHash,AirportKeyEqual> Airports;
    Airport a = Airport("Code1","Test","Uhm",1,2);
    a.distanceSince=0;
    a.visited=false;
    a.addFlight(Flight("","",0));

   /* Airport b = Airport("","Test","",0,0);
    b.visited=false;
    b.distanceSince=0;
    b.addFlight(Flight("","",0));*/

    Airport target = Airport("Code1","Test","Uhm",1,2);
   // cout<<(a==b)<<endl;

    Airports airports;
    airports.insert(a);

    cout<<airports.find(target)->getCode()<<endl;


}
//tested
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

    airportSetTest();
    return 0;
}
