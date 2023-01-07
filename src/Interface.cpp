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

    MenuPrincipal: string userInput;
    cout << "Introduza o numero do comando: \n\t1.Calcular rota de voo \n\t2.Informacoes\n\t0.Sair do programa" << endl;
    cin >> userInput;
    if (userInput == "0") return 1;
    while(!is_in(userInput,1,4)){
        cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
        cin >> userInput;
    }

    //Caso o user escolha Calcular rota de voo
    if(userInput == "1"){
        menuRota: string criteria1, criteria2, aeroporto, cidade, loc;
        int x;
        string str, dest;
        cout << "Escolha o criterio para a partida:\n\tLocal de partida:\n\t1.Aeroporto\n\t2.Cidade-Pais\n\t3.Localizacao\n\t0.Voltar" << endl; //Local de chegada:\n\t1.Aeroporto\n\t2.Cidade\n\t3.Localizacao\n\t0.Voltar" << endl;

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
            cin.ignore();
            getline(cin,aeroporto);
            if (aeroporto == "0") goto menuRota;
            str = aeroporto;

        }
        //caso o criterio for cidade
        if (criteria1 == "2"){
            cout << "Introduza a cidade-pais pretendida neste mesmo formato:\n\t0.Voltar" << endl;
            cin.ignore();
            getline(cin,cidade);
            if (cidade == "0") goto menuRota;
            str = cidade;
        }
        //caso o criterio for localizacao
        if (criteria1 == "3"){
            cout << "Introduza as coordenadas neste formato - (latitude,longitude):\n\t0.Voltar" << endl;
            cin.ignore();
            getline(cin,loc);
            if (loc == "0") goto menuRota;
            cout << "Introduza o raio que abranja os aeroportos desejados (em kilometros): " << endl;
            cin >> x;
            str = loc;
        }

        
        //chegada
        cout << "Escolha o criterio para a chegada\n\tLocal de chegada:\n\t1.Aeroporto\n\t2.Cidade\n\t3.Localizacao\n\t0.Voltar" << endl;
        cin >> criteria2;
        while(!is_in(criteria2, 0, 3)){
            cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
            cin >> criteria2;
        }
        if (criteria2 == "0") goto MenuPrincipal;
        //caso o criterio for aeroporto
        if (criteria2 == "1"){
            cout << "Introduza o aeroporto pretendido:\n\t0.Voltar" << endl;
            cin.ignore();
            getline(cin,aeroporto);
            if (aeroporto == "0") goto menuRota;
            dest = aeroporto;
        }
        //caso o criterio for cidade
        if (criteria2 == "2"){
            cout << "Introduza a cidade-pais pretendida neste mesmo formato:\n\t0.Voltar" << endl;
            cin.ignore();
            getline(cin,cidade);
            if (cidade == "0") goto menuRota;
            dest = cidade;
        }
        //caso o criterio for localizacao
        if (criteria2 == "3"){
            cout << "Introduza as coordenadas neste formato - (latitude,longitude):\n\t0.Voltar" << endl;
            cin.ignore();
            getline(cin,loc);
            if (loc == "0") goto menuRota;
            cout << "Introduza o raio que abranja os aeroportos desejados (em kilometros): " << endl;
            cin >> x;
            dest = loc;
        }

        menuAirline: string air, perso;
        cout << "Quais companhias aereas pretende averiguar?\n\t1.Qualquer uma\n\t2.Personalizado\n\t0.Voltar" << endl;
        cin >> air;
        if (air =="0") goto menuRota;

        //qualquer uma
        if (air == "1"){
            perso = "";

        }
        //personalizado
        if (air == "2"){
            cout << "Introduza as companhias aereas pretendidas: " << endl;
            cin.ignore();
            getline(cin, perso);

        }

        menuResult:
        char sep = ',';
        unordered_set<string> pref1 = split(perso, sep);
        double rad = x;

        try {
            database->showShortestPath(str, dest, rad, pref1);
        } catch(int error){
            cout << "Alguns dos dados inseridos estao incorretos, por favor, tente novamente. " << endl;
            goto menuRota;
        }

    }


    //Caso o user escolha Informacoes
    else if(userInput == "2"){
        menuInfo: string ch1, ch2, cod;
        cout << "1.Aeroportos\n\t2.Estatisticas globais\n\t0.Voltar" << endl;
        cin >> ch1;

        if (ch1 == "0") goto MenuPrincipal;
        while(!is_in(ch1,1,2)){
            cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
            cin >> ch1;
        }

        if (ch1 == "1"){
            menuAero:
            cout << "1.Companhias aéreas do aeroporto\n\t2.Companhias aéreas para aeroporto\n\t3.Países do aeroporto\n\t4.Países para aeroporto\n\t5.Cidades do aeroporto\n\t6.Cidades para aeroporto\n\t7.Voos do aeroporto\n\t8.Voos para aeroporto\n\t0.Voltar: " << endl;
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
                try{
                    database -> airlinesFromAirport(cod);
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu1;
                }
            }
            if (ch2 == "2"){
                menu2:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                try{
                    database -> airlinesToAirport(cod);
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu2;
                }

            }
            if (ch2 == "3"){
                menu3:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                try{
                    database -> countriesFromAirport(cod);
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu3;
                }

            }
            if (ch2 == "4"){
                menu4:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                try{
                    database -> countriesToAirport(cod);
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu4;
                }

            }
            if (ch2 == "5"){
                menu5:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                try{
                    database -> citiesFromAirport(cod);
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu5;
                }

            }
            if (ch2 == "6"){
                menu6:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                try{
                    database -> citiesToAirport(cod);
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu6;
                }

            }
            if (ch2 == "7"){
                menu7:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                try{
                    database -> flightsFromAirport(cod);
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu7;
                }

            }
            if (ch2 == "8"){
                menu8:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                try{
                    database -> flightsToAirport(cod);
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu8;
                }

            }
        }

        if (ch1 == "2"){
            menuGlobal: string tipo, modo, country, airline;
            int k;
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
            k = 0;
            if (modo == "1"){modo = "nAirports";}
            if (modo == "2"){modo = "nFlights";}
            if (modo == "3"){modo = "nAirlines";}
            if (modo == "4"){
                modo = "top-k airports";
                cout << "Qual o numero de aeroportos que pretende que Top mostre: " << endl;
                cin >> k;
            }

            try {
                database->globalStatistics(tipo, modo, country, airline, k);
            } catch (int error) {
                cout << "Alguns dos dados inseridos estao incorretos, por favor, tente novamente. " << endl;
                goto menuGlobal;
            }
        }

    }
    return 0;
}

Interface::Interface(CSVReader &reader) : database(&reader) {}

