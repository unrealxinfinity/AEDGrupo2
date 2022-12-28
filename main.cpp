#include <iostream>
#include "Airport.h"
#include "airportsGraph.h"
#include "CSVReader.h"
#include <unordered_set>

//temp section for tests
//Tested

void testAirport(){
    /*unordered_set<Airport,AirportHash> airports;
    City city = City("Porto","Portugal");
    City *cityP=&city;
    airports.insert(Airport("BFS","Test",cityP,1,1));

    auto it= airports.find(Airport("BFS","", nullptr,1,1));

    Airport test= Airport("BFS","Test",cityP,41.24,-8.6);
    Airport test2= Airport("Ola","Test",cityP,38.77,-9.135);
    Airport test3= Airport("LIS","Test",cityP,39.88,-10.33);

    airports.insert(test);
    airports.insert(test2);
    airports.insert(test3);
    unordered_set<Airport,AirportHash> res;

    airportsGraph graph= airportsGraph();
    */
    CSVReader reader = CSVReader();
    reader.populate();
    cout<<reader.getAirports().begin()->getCode()<<endl;


}
/*void testsAirportEqualAndAssignment(){
    Airport airportTest= Airport("BCN","BarcelonaAirport","Barcelona",1,1);
    Airport airportTest2= Airport("ABD","BarcelonaAirport","Barcelona",1,1);
    Airport temp;
    airportTest2=airportTest;

    cout<<airportTest2.getCode()<<endl;
    cout<<(airportTest2==airportTest)<<endl;

}
//error
void airportSetTest(){
    typedef unordered_set<Airport*,AirportHash,AirportKeyEqual> Airports;
    Airport a = Airport("Code1","Test","Uhm",1,2);
    a.distanceSince=0;
    a.visited=false;
    a.addFlight(Flight("","",0));

   /* Airport b = Airport("","Test","",0,0);
    b.visited=false;
    b.distanceSince=0;
    b.addFlight(Flight("","",0));

    Airport target = Airport("Code1","Test","Uhm",1,2);
   // cout<<(a==b)<<endl;

    Airports airports;
    airports.insert(&a);

    cout<<(*airports.find(&target))->getCode()<<endl;


}
//tested
void testUnorderedSetFlights(){
    typedef unordered_set<Flight*,FlightHash,FlightKeyEqual> Flights;
    Flights flights;
    Flight temp=Flight("Ola","Teste",0);
    Flight target=Flight("Ola","",10);
    flights.insert(&temp);
    auto res = flights.find(&target);

    cout<<(*res)->getOriginAirportCode()<<(*res)->destAirportCode_<<(*res)->airlineCode_<<(*res)->flightDistance_<<endl;

}
*/
int main() {
    testAirport();
    //CSVReader reader;
    //reader.populate();
    return 0;
}
