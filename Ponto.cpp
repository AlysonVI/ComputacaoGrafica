#include "Ponto.h"

Ponto::Ponto(float x, float y){
    this->coordenadas[0][0]= x;
    this->coordenadas[1][0]= y;
    this->coordenadas[2][0]= 1;
}
Ponto::Ponto(){
    this->coordenadas[0][0]= 0;
    this->coordenadas[1][0]= 0;
    this->coordenadas[2][0]= 1;
}

QPointF Ponto::convertToQPointF(){
    return *(new QPointF(coordenadas[0][0], coordenadas[1][0]));
}
void Ponto::draw(QPainter& painter) const {
    painter.drawPoint(*(new QPointF(coordenadas[0][0], coordenadas[1][0])));
}
