//
// Created by nesma on 28/12/2022.
//

#include "../header/Interface.h"
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

bool Interface::is_in(string choice, int lim_start, int lim_end) const{
    set<string> availableChoices={"0","1","2","3","4","5","6","7","8","9"};
    if(availableChoices.find(choice)!= availableChoices.end()&&stoi(choice)>=lim_start && stoi(choice) <=lim_end ) return true;
    return false;
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
        menuRota: string criteria1, criteria2, aeroporto, cidade, loc;
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
            save.push_back(aeroporto);
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
            save.push_back(loc);
        }

        menuAirline: string air, perso;
        cout << "Quais companhias aereas pretende averiguar?\n\t1.Qualquer uma\n\t2.Personalizado\n\t0.Voltar" << endl;
        cin >> air;
        if (air =="0") goto menuRota;
        save.push_back(air);

        //qualquer uma
        if (air == "1"){
            perso = "Qualquer";
            save.push_back(perso);
        }
        //personalizado
        if (air == "2"){
            cout << "Introduza as companhias aereas pretendidas: " << endl;
            getline(cin, perso);
            save.push_back(perso);
        }

        menuResult:
        cout << "A carregar..." << endl;
        

    }


    //Caso o user escolha Informacoes
    else if(userInput == "2"){}

}

Interface::Interface(CSVReader &reader) : database(&reader) {}