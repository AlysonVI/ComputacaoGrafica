#include <iostream>
#include <ponto.h>
using namespace std;

    Ponto::Ponto(float x, float y){

        this->x = x;
        this->y = y;

    }
    Ponto::~Ponto(){}

    void Ponto::mostraPonto(){

        cout << "ok!" << x << y;
    }

