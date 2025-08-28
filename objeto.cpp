#include "objeto.h"
#include <iostream>

    Objeto::Objeto(){}
    Objeto::Objeto(string nome){

        this->nome = nome;
        numLinhas = 0;
    }

    Objeto::~Objeto(){}

    void Objeto::adicionaLinha(Linha l){
        vetorDeLinhas.push_back(l);
        numLinhas +=1;
    }

    void Objeto::mostraLinhas(){
        for(int i =0; i<numLinhas; i++){
            Linha laux = vetorDeLinhas[i];
            cout << "Linha[" << i << "] (x:" << laux.a.coordenadas[0][0]
                 << " y:" << laux.a.coordenadas[1][0] << ") + " << "(x:"
                 << laux.b.coordenadas[0][0] <<" y:"<< laux.b.coordenadas[1][0] <<")";
        }
    }


