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
    bool isFlownByAirline(const Flight& f,const list<string>& airline) const;

    //estas funcoes find retornam o codigo/lista codigos do aeroporto,complexidade O(N)
    string findAirportByName(const string airportName) const;
    list<string> findAirportByCity(const string city, const string country) const;
    Airport findAirportByCoord(const double lat, const double longi) const;
    //encontra os aeroportos a partir de um centro, retorna unordered set com o centro inclusive;
    //complexidade O(N) sendo N a pesquisa pelo aeroporto com as coordenadas dadas e a pesquisa pelos aeroportos a menos de raio radius
    list<string> findAirportsAround(const double lat,const double longi,const double radius)const;
    list<string> toListOfString(list<Airport> airports);
public:
    pair<list<Flight>, string> bfs(const list<string>& source, const list<string>& dest, const list<string>& preferences);
    void populate();
    CSVReader();
    //Dando um input o decipher transforma o input numa lista de aeroportos para fazer bfs, faz throw de um inteiro caso os inputs estejam invalidos e nao estiverem de acordo com o formato dado
    //Complexidade O(N) sendo N a pesquisa pelos aeroportos de acordo com o input;
    list<string> decipherInput(const string src,const double radius=0);
    int distance(string airportA,string airportB);
    unordered_set<Airline,AirlineHash> getAirlines(){return airlines;}
    unordered_set<Airport, AirportHash> getAirports();
    //Mostra o caminho mais curto dando um src seguindo um formato, um dest seguindo tais formatos raius caso o user procure pela cidade ou pelas coordenadas e preferencias caso ela tenha alguma preferencia de companhia aeria;
    //Radius e preferencias estao como default 0 e empty caso o user nao precise de introduzir radius ou nao tenha preferencias;
    //Complexity O(N) being N the size of the path of travel
    void showShortestPath(const string src,const string dest,const double radius=0,const list<string> preferences={});
};


#endif //PROJETOGRUPO2_CSVREADER_H
