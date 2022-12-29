//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETOGRUPO2_CSVREADER_H
#define PROJETOGRUPO2_CSVREADER_H
#include <string>
#include "airportsGraph.h"
#include "Airline.h"

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

    //fills the Flights of each Airport
    //void readFlights(string filename);
    //void insertFlights(Airport &a);
    void read_flights();
    void read_airports();
    void read_airlines();
public:
    void populate();
    CSVReader();
    unordered_set<Airline,AirlineHash> getAirlines(){return airlines;}
    unordered_set<Airport, AirportHash> getAirports() ;


};


#endif //PROJETOGRUPO2_CSVREADER_H
