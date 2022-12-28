//
// Created by fuhao on 26/12/2022.
//

#ifndef PROJETOGRUPO2_CSVREADER_H
#define PROJETOGRUPO2_CSVREADER_H
#include <string>
#include "airportsGraph.h"

using namespace std;
typedef unordered_set<Flight*,FlightHash,FlightKeyEqual> Flights;


/*Conceito : tens um readFlights  para usar no construtor que lê todos os flights do ficheiro para *var flights*.
 Como flights.csv esta organizado em origem-dest-airline, o readAirports vai introduzir os aeroportos do ficheiro linha a linha para a estrutura
 de dados no grafo e, sabendo o AirportCode de cada linha no ficheiro usando insertFlights(uma funcao que serve para inserir Flight/Edge dos *flights* ao usar flights.find(Flight(AeroportoEmQuestao,"","")
 para inserir todos os Flights/edges ao Airport novo criado e mandar para a estrutura nos grafos.
 --expected complexity O(N*E) for readAirports sendo E o nr de Edges relacionados por esta implementacao, usando find de complexidade 1 do unordered_set;
 --expected complexity for insertFlights() is O(E) being E the nr of Flights related to a certain airport;
 */

class CSVReader {
private:
    string filename;
    Flight flights;

    //fills the Flights of each Airport
    //void readFlights(string filename);
    //void insertFlights(Airport &a);
public:
    CSVReader(string Flightsfilename);
    CSVReader();
    //supposed idea to use CSV reader in the graph constructor to fill the airports set of its field
    //void readAirports(unordered_set<Airport,airportHash,airportKeyEqual> &airports,string filename);

};


#endif //PROJETOGRUPO2_CSVREADER_H
