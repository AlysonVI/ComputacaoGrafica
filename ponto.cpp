#include <iostream>
#include <ponto.h>
#include <vector>

using namespace std;

    Ponto::Ponto(float x, float y){

        this->coordenadas[0][0] = x;
        this->coordenadas[1][0] = y;

    }
    Ponto::Ponto(){
        this->coordenadas[0][0] = 0;
        this->coordenadas[1][0]= 0;
    }
    Ponto::~Ponto(){}

    void Ponto::mostraPonto(){

        cout << coordenadas[0][0] << coordenadas[1][0];
    }

