//
// Created by nesma on 28/12/2022.
//

#ifndef PROJETOGRUPO2_INTERFACE_H
#define PROJETOGRUPO2_INTERFACE_H

#include <queue>
#include <string>
#include <list>
#include <math.h>
#include "CSVReader.h"

using namespace std;

class Interface {
private:
    bool is_in(const string& choice,int lim_start,int lim_end) const;
    CSVReader* database;
public:
    Interface();
    Interface(CSVReader& reader);
    unordered_set<string> split(const string &str, char sep);
    int initiate();
    //Dados dois locais, indicar a melhor maneira de voar de um para o outro (menor número de voos).
        //Local - aeroporto em especifico, cidade (considerar todos os aeroportos presentes) ou uma localização (coordenadas, considerar todos os aeroportas a X kms da localização).
        //Rede de voos - ter em conta qualquer companhia aerea, somente uma ou um conjunto.
        //usar formula de Haversine: hav(x) = sin^2(x/2)

    //Informações sobre o aeroporto:
        //quantos voos partem, quantas as companhias, para quantos destinos diferentes, de quantos paises diferentes, quantos aeroportos/cidades/países são atingíveis usando mas Y voos

};


#endif //PROJETOGRUPO2_INTERFACE_H
