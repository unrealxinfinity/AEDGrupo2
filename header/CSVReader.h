//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETOGRUPO2_CSVREADER_H
#define PROJETOGRUPO2_CSVREADER_H
#include <string>
#include <list>
#include "Airline.h"
#include "Airport.h"
#include "Flight.h"

using namespace std;

/*Conceito : tens um readFlights  para usar no construtor que lê todos os flights do ficheiro para *var flights*.
 Como flights.csv esta organizado em origem-dest-airline, o readAirports vai introduzir os aeroportos do ficheiro linha a linha para a estrutura
 de dados no grafo e, sabendo o AirportCode de cada linha no ficheiro usando insertFlights(uma funcao que serve para inserir Flight/Edge dos *flights* ao usar flights.find(Flight(AeroportoEmQuestao,"","")
 para inserir todos os Flights/edges ao Airport novo criado e mandar para a estrutura nos grafos.
 --expected complexity O(N*E) for readAirports sendo E o nr de Edges relacionados por esta implementacao, usando find de complexidade 1 do unordered_set;
 --expected complexity for insertFlights() is O(E) being E the nr of Flights related to a certain airport;
 */

class CSVReader {
private:
    unordered_set<Airport, AirportHash> airports;
    unordered_set<City, CityHash> cities;
    unordered_set<Airline, AirlineHash> airlines;

    void read_flights();
    void read_airports();
    void read_airlines();

    bool hasDir;

    //checks if a flight is flown by an airline, parameter airlines accepts callsign ,code or name, empty means all airlines are accepted;
    //Used for bfs , idea is to bfs_visit those flights that isFlownByAirline evaluates true maybe? But I believe this function will be useful;
    // complexity O(N) being N the size of the list of airlines the user provides;
    bool isFlownByAirline(const Flight f,list<string> airline) const;
public:
    list<Flight> bfs(const list<string>& source, const list<string>& dest);
    void populate();
    CSVReader();


    void bfs(Airport &from,Airport &to);

    //encontra os aeroportos a partir de um centro, retorna unordered set com o centro inclusive;
    //complexidade O(N) sendo N a pesquisa pelo aeroporto com as coordenadas dadas e a pesquisa pelos aeroportos a menos de raio radius
    unordered_set<Airport,AirportHash> findAirportsAround(const double lat,const double longi,const double radius)const;
    Airport findAirportByCoord(const double lat, const double longi) const;
    int distance(string airportA,string airportB);
    unordered_set<Airline,AirlineHash> getAirlines(){return airlines;}
    unordered_set<Airport, AirportHash> getAirports() ;


};


#endif //PROJETOGRUPO2_CSVREADER_H
