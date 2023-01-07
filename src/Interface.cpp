//
// Created by nesma on 28/12/2022.
//

#include "../header/Interface.h"
#include <iostream>
#include <set>
#include <algorithm>
#include <sstream>

using namespace std;

bool Interface::is_in(string choice, int lim_start, int lim_end) const{
    set<string> availableChoices={"0","1","2","3","4","5","6","7","8","9"};
    if(availableChoices.find(choice)!= availableChoices.end()&&stoi(choice)>=lim_start && stoi(choice) <=lim_end ) return true;
    return false;
}

unordered_set<string> Interface::split(const string &str, char sep){
    unordered_set<string> tokens;
    string i;
    stringstream ss(str);
    while (ss >> i) {
        tokens.insert(i);
        if (ss.peek() == sep) {
            ss.ignore();
        }
    }
    return tokens;
}


int Interface::initiate() {

    list <string> save; //contem os inputs do user
    auto it = save.begin();

    MenuPrincipal: string userInput;
    cout << "Introduza o numero do comando: \n\t1. Calcular rota de voo \n\t2.Informacoes\n\t0.Sair do programa" << endl;
    cin >> userInput;
    if (userInput == "0") return 1;
    while(!is_in(userInput,1,4)){
        cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
        cin >> userInput;
    }

    //Caso o user escolha Calcular rota de voo
    if(userInput == "1"){
        menuRota: string criteria1, criteria2, aeroporto, cidade, loc, x;
        cout << "Escolha o criterio para a partida e para a chegada:\n\tLocal de partida:\n\t1.Aeroporto\n\t2.Cidade-Pais\n\t3.Localizacao\n\tLocal de chegada:\n\t1.Aeroporto\n\t2.Cidade\n\t3.Localizacao\n\0.Voltar" << endl;

        //partida
        cin >> criteria1;
        while(!is_in(criteria1, 0, 3)){
            cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
            cin >> criteria1;
        }
        if (criteria1 == "0") goto MenuPrincipal;
        //caso o criterio for aeroporto
        if (criteria1 == "1"){
            cout << "Introduza o aeroporto pretendido:\n\t0.Voltar" << endl;
            getline(cin,aeroporto);
            if (aeroporto == "0") goto menuRota;
            //save.push_back(aeroporto);

        }
        //caso o criterio for cidade
        if (criteria1 == "2"){
            cout << "Introduza a cidade-pais pretendida neste mesmo formato:\n\t0.Voltar" << endl;
            getline(cin,cidade);
            if (cidade == "0") goto menuRota;
            save.push_back(cidade);
        }
        //caso o criterio for localizacao
        if (criteria1 == "3"){
            cout << "Introduza as coordenadas neste formato - (latitude,longitude):\n\t0.Voltar" << endl;
            getline(cin,loc);
            if (loc == "0") goto menuRota;
            cout << "Introduza o raio que abranja os aeroportos desejados (em kilometros): " << endl;
            getline(cin, x);
            save.push_back(loc);
        }

        
        //chegada
        cin >> criteria2;
        while(!is_in(criteria2, 0, 3)){
            cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
            cin >> criteria2;
        }
        if (criteria2 == "0") goto MenuPrincipal;
        //caso o criterio for aeroporto
        if (criteria2 == "1"){
            cout << "Introduza o aeroporto pretendido:\n\t0.Voltar" << endl;
            getline(cin,aeroporto);
            if (aeroporto == "0") goto menuRota;
            save.push_back(aeroporto);
        }
        //caso o criterio for cidade
        if (criteria2 == "2"){
            cout << "Introduza a cidade-pais pretendida neste mesmo formato:\n\t0.Voltar" << endl;
            getline(cin,cidade);
            if (cidade == "0") goto menuRota;
            save.push_back(cidade);
        }
        //caso o criterio for localizacao
        if (criteria2 == "3"){
            cout << "Introduza as coordenadas neste formato - (latitude,longitude):\n\t0.Voltar" << endl;
            getline(cin,loc);
            if (loc == "0") goto menuRota;
            cout << "Introduza o raio que abranja os aeroportos desejados (em kilometros): " << endl;
            getline(cin, x);
            save.push_back(loc);
        }

        menuAirline: string air, perso;
        cout << "Quais companhias aereas pretende averiguar?\n\t1.Qualquer uma\n\t2.Personalizado\n\t0.Voltar" << endl;
        cin >> air;
        if (air =="0") goto menuRota;

        //qualquer uma
        if (air == "1"){
            perso = "";
            save.push_back(perso);
        }
        //personalizado
        if (air == "2"){
            cout << "Introduza as companhias aereas pretendidas: " << endl;
            getline(cin, perso);
            save.push_back(perso);
        }

        menuResult:
        const string str = *it;
        it++;
        const string dest = *it;
        it++;
        const string pref = *it;
        char sep = ',';
        const unordered_set<string> pref1 = split(pref, sep);
        const double rad = stod(x);
        database -> showShortestPath(str, dest, rad, pref1);

    }


    //Caso o user escolha Informacoes
    else if(userInput == "2"){
        menuInfo: string ch1, ch2, cod;
        cout << "\t1.Aeroportos\n\t2.Estatisticas globais\n\t0.Voltar" << endl;
        cin >> ch1;

        while(!is_in(ch1,0,2)){
            cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
            cin >> ch1;
        }
        if(ch1=="0") goto MenuPrincipal;
        if (ch1 == "1"){
            menuAero:
            cout << "\t1.Companhias aéreas dos voos que partem do aeroporto\n\t2.Companhias aéreas dos voos que chegam ao aeroporto\n\t3.Países destino dos voos que partem do aeroporto\n\t4.Países origem dos voos que chegam ao aeroporto\n\t5.Cidades destino dos voos que partem do aeroporto\n\t6.Cidades origem dos voos que chegam ao aeroporto\n\t7.Voos que partem do aeroporto\n\t8.Voos que chegam ao aeroporto\n\t0.Voltar: " << endl;
            cin >> ch2;
            if (ch2 == "0") goto menuInfo;
            while(!is_in(ch2,1,8)) {
                cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                cin >> ch2;
            }

            if (ch2 == "1"){
                menu1:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                database -> airlinesFromAirport(cod);
            }
            if (ch2 == "2"){
                menu2:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                database -> airlinesToAirport(cod);
            }
            if (ch2 == "3"){
                menu3:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                database -> countriesFromAirport(cod);
            }
            if (ch2 == "4"){
                menu4:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                database -> countriesToAirport(cod);
            }
            if (ch2 == "5"){
                menu5:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                database -> citiesFromAirport(cod);
            }
            if (ch2 == "6"){
                menu6:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                database -> citiesToAirport(cod);
            }
            if (ch2 == "7"){
                menu7:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                database -> flightsFromAirport(cod);
            }
            if (ch2 == "8"){
                menu8:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                database -> flightsToAirport(cod);
            }
        }

        if (ch1 == "2"){
            menuGlobal: string tipo, modo, country, airline, k;
            cout << "Pretende: \n\t1.Network completa\n\t2.Pais\n\t3.Companhia aerea\n\t0.Voltar" << endl;
            cin >> tipo;
            if (tipo == "0") goto menuInfo;
            while(!is_in(tipo,1,3)) {
                cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                cin >> tipo;
            }
            if (tipo == "1"){
                tipo = "rede";
                country = "";
                airline = "";
            }
            if (tipo == "2"){
                tipo = "pais";
                cout << "Qual o pais que pretende: " << endl;
                cin >> country;
                airline = "";
            }
            if (tipo == "3"){
                tipo = "companhia aerea";
                cout << "Qual a companhia aerea que pretende: " << endl;
                country = "";
                cin >> airline;
            }

            cout << "Pretende: \n\t1.Numero de aeroportos\n\t2.Numero de voos\n\t3.Numero de companhias aereas\n\t4.Top-K de aeroportos\n\t0.Voltar" << endl;
            cin >> modo;
            if (modo == "0") goto menuInfo;
            while(!is_in(modo,1,4)) {
                cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                cin >> modo;
            }
            int k1;
            if (modo == "1"){modo = "nAirports";}
            if (modo == "2"){modo = "nFlights";}
            if (modo == "3"){modo = "nAirlines";}
            if (modo == "4"){
                modo = "top-k airports";
                cout << "Qual o numero de aeroportos que pretende que Top mostre: " << endl;
                cin >> k;
                k1 = stoi(k);
            }
            database -> globalStatistics(tipo,modo,country,airline,k1);
        }
    }
    return -1;
}

Interface::Interface(CSVReader &reader) : database(&reader) {}

