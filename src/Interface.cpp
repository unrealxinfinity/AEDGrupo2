//
// Created by nesma on 28/12/2022.
//

#include "../header/Interface.h"
#include <iostream>
#include <set>
#include <algorithm>
#include <sstream>

using namespace std;

bool Interface::is_in(const string& choice, int lim_start, int lim_end) const{
    set<string> availableChoices={"0","1","2","3","4","5","6","7","8","9","10"};
    if(availableChoices.find(choice)!= availableChoices.end()&&stoi(choice)>=lim_start && stoi(choice) <=lim_end ) return true;
    return false;
}

unordered_set<string> Interface::split(const string &str, char sep){
    unordered_set<string> tokens;
    string i;
    stringstream ss(str);
    while (getline(ss, i, sep)) {
        tokens.insert(i);
    }
    return tokens;
}


int Interface::initiate() {

    MenuPrincipal: string userInput;
    cout << "Introduza o numero do comando: \n\t1.Calcular rota de voo \n\t2.Informacoes\n\t0.Sair do programa" << endl;
    cin >> userInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (userInput == "0") return 1;
    while(!is_in(userInput,1,4)){
        cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
        cin >> userInput;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    //Caso o user escolha Calcular rota de voo
    if(userInput == "1"){
        menuRota: string criteria1, criteria2, aeroporto, cidade, loc;
        int x;
        string str, dest;
        cout << "Escolha o criterio para a partida:\n\tLocal de partida:\n\t1.Aeroporto\n\t2.Cidade-Pais\n\t3.Localizacao\n\t0.Voltar" << endl; //Local de chegada:\n\t1.Aeroporto\n\t2.Cidade-Pais\n\t3.Localizacao\n\t0.Voltar" << endl;

        //partida
        cin >> criteria1;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while(!is_in(criteria1, 0, 3)){
            cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
            cin >> criteria1;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (criteria1 == "0") goto MenuPrincipal;
        //caso o criterio for aeroporto
        if (criteria1 == "1"){
            cout << "Introduza o aeroporto pretendido em formato de codigo ou nomeDoAeroporto_cidade_pais :\n\t0.Voltar" << endl;
            
            getline(cin,aeroporto);
            if (aeroporto == "0") goto menuRota;
            str = aeroporto;

        }
        //caso o criterio for cidade
        if (criteria1 == "2"){
            cout << "Introduza a cidade-pais pretendida neste mesmo formato:\n\t0.Voltar" << endl;
            
            getline(cin,cidade);
            if (cidade == "0") goto menuRota;
            str = cidade;
        }
        //caso o criterio for localizacao
        if (criteria1 == "3"){
            cout << "Introduza as coordenadas neste formato - (latitude,longitude):\n\t0.Voltar" << endl;
            
            getline(cin,loc);
            if (loc == "0") goto menuRota;
            cout << "Introduza o raio que abranja os aeroportos desejados (em kilometros): " << endl;
            cin >> x;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            str = loc;
        }

        
        //chegada
        cout << "Escolha o criterio para a chegada\n\tLocal de chegada:\n\t1.Aeroporto\n\t2.Cidade\n\t3.Localizacao\n\t0.Voltar" << endl;
        cin >> criteria2;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while(!is_in(criteria2, 0, 3)){
            cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
            cin >> criteria2;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (criteria2 == "0") goto MenuPrincipal;
        //caso o criterio for aeroporto
        if (criteria2 == "1"){
            cout << "Introduza o aeroporto pretendido em codigo ou nomeDoAeroporto_cidade_pais :\n\t0.Voltar" << endl;
            
            getline(cin,aeroporto);
            if (aeroporto == "0") goto menuRota;
            dest = aeroporto;
        }
        //caso o criterio for cidade
        if (criteria2 == "2"){
            cout << "Introduza a cidade-pais pretendida neste mesmo formato:\n\t0.Voltar" << endl;
            
            getline(cin,cidade);
            if (cidade == "0") goto menuRota;
            dest = cidade;
        }
        //caso o criterio for localizacao
        if (criteria2 == "3"){
            cout << "Introduza as coordenadas neste formato - (latitude,longitude):\n\t0.Voltar" << endl;
            
            getline(cin,loc);
            if (loc == "0") goto menuRota;
            cout << "Introduza o raio que abranja os aeroportos desejados (em kilometros): " << endl;
            cin >> x;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            dest = loc;
        }

        menuAirline: string air, perso;
        cout << "Quais companhias aereas pretende averiguar?\n\t1.Qualquer uma\n\t2.Personalizado\n\t0.Voltar" << endl;
        cin >> air;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (air =="0") goto menuRota;

        //qualquer uma
        if (air == "1"){
            perso = "";

        }
        //personalizado
        if (air == "2"){
            cout << "Introduza as companhias aereas pretendidas: " << endl;
            
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
        cout << "Tipo de informacao desejada:\n\t1.Sobre aeroporto\n\t2.Estatisticas globais\n\t0.Voltar" << endl;
        cin >> ch1;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (ch1 == "0") goto MenuPrincipal;
        while(!is_in(ch1,1,2)){
            cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
            cin >> ch1;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (ch1 == "1"){
            menuAero:
            cout << "\t1.Companhias aereas responsaveis pelos voos que partem do aeroporto\n\t2.Companhias aereas responsaveis pelos voos que chegam ao aeroporto\n\t3.Paises destino dos voos do aeroporto\n\t4.Paises origem dos voos que chegam ao aeroporto\n\t5.Cidades destino dos voos que partem do aeroporto\n\t6.Cidades origem dos voos que chegam ao aeroporto\n\t7.Voos que partem do aeroporto\n\t8.Voos que chegam ao aeroporto\n\t9.Aeroportos atingiveis\n\t10.Verificar se o aeroporto e um ponto de artriculacao\n\t0.Voltar: " << endl;
            cin >> ch2;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (ch2 == "0") goto menuInfo;
            while(!is_in(ch2,0,10)) {
                cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                cin >> ch2;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (ch2 == "1"){
                menu1:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                try{
                    auto data = database -> airlinesFromAirport(cod);
                    cout << "Companhias aereas presentes em voos saindo do aeroporto:" << endl;
                    for (const auto& e : data) {
                        cout << e.getCode() << ", " << e.getName() << ". Callsign is " << e.get_callsign() << ", company is from " << e.getCountry() << '.' << endl;
                    }
                    cout<<endl;
                    cout<<"No total :"<<data.size()<<" Companhias."<<endl;
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu1;
                }
            }
            if (ch2 == "2"){
                menu2:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                try{
                    auto data = database -> airlinesToAirport(cod);
                    cout << "Companhias aereas presentes em voos entrando no aeroporto:" << endl;
                    for (const auto& e : data) {
                        cout << e.getCode() << ", " << e.getName() << ". Callsign is " << e.get_callsign() << ", company is from " << e.getCountry() << '.' << endl;
                    }
                    cout<<endl;
                    cout<<"No total :"<<data.size()<<" Companhias."<<endl;
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu2;
                }

            }
            if (ch2 == "3"){
                menu3:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Paises atingiveis em quantos voos? (numero inteiro):"<<endl;
                int n;
                cin >> n;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                try{
                    auto data = database ->reachableCountries(n, cod);
                    cout << "Os paises atingiveis sao:" << endl;
                    for (const auto& e : data) {
                        cout << e << endl;
                    }
                    cout<<endl;
                    cout<<"No total de: "<<data.size()<<" paises."<<endl;
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu3;
                }

            }
            if (ch2 == "4"){
                menu4:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                try{
                    auto data = database -> countriesToAirport(cod);
                    cout << "Os paises com voos a entrar no aeroporto sao:" << endl;
                    for (const auto& e : data) {
                        cout << e << endl;
                    }
                    cout<<endl;
                    cout<<"No total :"<<data.size()<<" paises."<<endl;

                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu4;
                }

            }
            if (ch2 == "5"){
                menu5:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Cidades atingiveis em quantos voos? (numero inteiro)";
                int n;
                cin >> n;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                try{
                    auto data = database ->reachableCities(n, cod);
                    for (const auto& e : data) {
                        cout << e.first << '-' << e.second << endl;
                    }
                    cout<<endl;
                    cout<<"No total :"<<data.size()<<" cidades."<<endl;
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu5;
                }

            }
            if (ch2 == "6"){
                menu6:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                try{
                    auto data = database -> citiesToAirport(cod);
                    cout << "As cidades que tem voos a entrar no aeroporto sao:" << endl;
                    for (const auto& e : data) {
                        cout << e.first << '-' << e.second << endl;
                    }
                    cout<<endl;
                    cout<<"No total :"<<data.size()<<" cidades."<<endl;
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu6;
                }

            }
            if (ch2 == "7"){
                menu7:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                try{
                    auto data = database -> flightsFromAirport(cod);
                    cout << "Os voos que saem do aeroporto sao:" << endl;
                    for (const auto& e : data) {
                        cout << "Destino: " << e.destAirportCode_ << "; Companhia: " << e.airline_ << "; Distancia: " << e.flightDistance_ << endl;
                    }
                    cout<<endl;
                    cout<<"No total :"<<data.size()<<" voos."<<endl;
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu7;
                }

            }
            if (ch2 == "8"){
                menu8:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                try{
                    auto data = database -> flightsToAirport(cod);
                    cout << "Os voos que entram no aeroporto sao:" << endl;
                    for (const auto& e : data) {
                        cout << "Origem: " << e.first << "; Companhia: " << e.second.airline_ << "; Distancia: " << e.second.flightDistance_ << endl;
                    }
                    cout<<endl;
                    cout<<"No total :"<<data.size()<<" voos."<<endl;
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu8;
                }
            }
            if (ch2 == "9"){
                menu9:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Aeroportos atingiveis em quantos voos? (numero inteiro):"<<endl;
                int n;
                cin >> n;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                try{
                    auto data = database ->reachableAirports(n, cod);
                    for (const auto& e : data) {
                        Airport find = database->getAirport(e);
                        cout << find.getCode() << ", " << find.getName() << ", localizado em " << find.getCity()->get_name() << '-' << find.getCity()->get_country() << ", coordenadas (" << find.getLatitude() << ';' << find.getLongitude() << ')' << endl;
                    }
                    cout<<endl;
                    cout<<"No total sao: "<<data.size()<< " aeroportos."<<endl;
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu10;
                }
            }
            if (ch2 == "10"){
                menu10:
                cout << "Por favor, insira o codigo do aeroporto: " << endl;
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                try{
                    auto data = database ->isArticulationPoint(cod);
                    if (data)
                        cout << "O aeroporto e ponto de articulacao" << endl;
                    else
                        cout << "O aeroporto nao e ponto de articulacao" << endl;
                }catch (int error){
                    cout << "O codigo inserido esta incorreto, por favor, tente novamente." << endl;
                    goto menu10;
                }
            }
        }

        if (ch1 == "2"){
            menuGlobal: string tipo, modo, country, airline;
            int k;
            cout << "Pretende: \n\t1.Network completa\n\t2.Pais\n\t3.Companhia aerea\n\t0.Voltar" << endl;
            cin >> tipo;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (tipo == "0") goto menuInfo;
            while(!is_in(tipo,0,3)) {
                cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                cin >> tipo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (tipo == "1"){
                cout << "Pretende: \n\t1.Numero de aeroportos\n\t2.Numero de voos\n\t3.Numero de companhias aereas\n\t4.Top-K de aeroportos\n\t0.Voltar" << endl;
                cin >> modo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (modo == "0") goto menuInfo;
                while(!is_in(modo,0,4)) {
                    cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                    cin >> modo;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                tipo = "rede";
                country = "";
                airline = "";
            }
            if (tipo == "2"){
                cout << "Pretende: \n\t1.Numero de aeroportos\n\t2.Numero de voos\n\t3.Numero de companhias aereas\n\t4.Top-K de aeroportos\n\t0.Voltar" << endl;
                cin >> modo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (modo == "0") goto menuInfo;
                while(!is_in(modo,0,4)) {
                    cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                    cin >> modo;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                tipo = "pais";
                cout << "Qual o pais que pretende: " << endl<<flush;

                getline(cin,country);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                airline = "";
            }
            if (tipo == "3"){
                cout << "Pretende: \n\t2.Numero de voos totais da companhia\n\t0.Voltar" << endl;
                cin >> modo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (modo == "0") goto menuInfo;
                while(!is_in(modo,2,2)) {
                    cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                    cin >> modo;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                tipo = "companhia aerea";
                cout << "Qual a companhia aerea que pretende: " << endl;
                cin >> airline;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            }


            k = 0;
            if (modo == "1"){modo = "nAirports";}
            if (modo == "2"){modo = "nFlights";}
            if (modo == "3"){modo = "nAirlines";}
            if (modo == "4"){
                modo = "top-k airports";
                cout << "Qual o numero de aeroportos que pretende que Top mostre: " << endl;
                cin >> k;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

