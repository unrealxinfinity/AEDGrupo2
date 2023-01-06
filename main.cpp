#include <iostream>
#include "Airport.h"
#include "CSVReader.h"
#include <string>
#include <sstream>
#include <unordered_set>

//temp section for tests
//Tested

/* void testAirport(){
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

    CSVReader reader = CSVReader();
    reader.populate();
    cout<<reader.getAirports().begin()->getCode()<<endl;


}

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

    typedef unordered_set<Airport,AirportHash> Airports;
    City city = City("Porto","Portugal");
    City *cityP=&city;
    Airport a = Airport("Code1","Test",cityP,1,2);
    a.distanceSince=0;
    a.visited=false;
    a.addFlight(Flight("","",0));

    Airport b = Airport("","Test",cityP,0,0);
    b.visited=false;
    b.distanceSince=0;
    b.addFlight(Flight("","",0));

    Airport target = Airport("Code1","Test",cityP,1,2);
   // cout<<(a==b)<<endl;

    Airports airports;
    airports.insert(a);

    City city = City("Porto","Portugal");
    City *cityP=&city;
    airportsGraph graph= airportsGraph();
    auto it = graph.findAirportByCoord(-6.081689,145.391881);
    cout<<it.getCode()<<endl;

    Airport airport= Airport("GKA","Goroka",cityP,-6.081689,145.391881);
    Airport airport1= Airport("MAG","Madang",cityP,-5.207083,145.788700);
    cout<<airport.calcDistanceHaversine(airport1)<<endl;

    auto it2= graph.findAirportsAround(-6.081689,145.391881,400);
   cout<<it2.begin()->getCode()<<endl;

    cout<<(++it2.begin())->getCode()<<endl;




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

void AirlineTest(){
    Airline a= Airline("IBE","Iberia Airlines","Iberia","Spain");
    Airline b= Airline("RYR","Raynair","RAINAIR","Ireland");
    unordered_set<Airline,AirlineHash> airlines;
    Airline target= Airline("RYR","","","");
    airlines.insert(a);
    airlines.insert(b);
    auto it = airlines.find(target);
    cout<<it->getCode()<<endl;
}
 */ /*
void isFlownByAirlineTest(){
    CSVReader reader;
    Flight f= Flight("CDG","AAL",0);
    list<string> air={"American Airlines"};
   // cout<<reader.isFlownByAirline(f,air)<<endl;
}
void testFindAirportsAround(){
    CSVReader reader= CSVReader();
    auto container=reader.findAirportsAround(40,-73,100);
    cout<<"hello"<<endl;
}
void testFindAirportByCity(){
    CSVReader reader;
    list<Airport> res;
    res=reader.findAirportByCity("London","United Kingdom");
    auto it=res.begin();
    while(it!=res.end()){
        cout<<it->getCode()<<endl;
        it++;
    }
}
void testFindAirportByName(){
    CSVReader reader;
    auto it=reader.findAirportByName("Mount Hagen");
    cout<<it.getCode()<<endl;
}
 */
/*void testDecipherInput(){
    string input={"Oradea"};
    CSVReader reader;
    list<string> res;
    res=reader.decipherInput(input,100);
    auto it=res.begin();
    while(it!=res.end()){
        cout<<*it<<endl;
        it++;
    }
}

*/

int main() {
    CSVReader reader;
    //reader.showShortestPath("Porto-Portugal","Lisbon-Portugal",50,{"TAP Air Portugal"});
    auto temp =reader.reachableCities(4,"OPO");
    for(auto it : temp){
        cout<<it.first<<" "<<it.second<<endl;
    }

}
