#include "Ponto.h"

Ponto::Ponto(double x, double y, double z)
    : Matriz(4,1){
    (*this)[0][0] = x;
    (*this)[1][0] = y;
    (*this)[2][0] = z;
    (*this)[3][0] = 1;
}

Ponto::Ponto(double x, double y) : Ponto(x,y,0) {}

QPointF* Ponto::convertToQPointF(){
    return (new QPointF((*this)[0][0], (*this)[1][0]));
}

void Ponto::draw(QPainter& painter) const {}

double Ponto::getX() const {
    return (*this)[0][0];
}

double Ponto::getY() const {
    return (*this)[1][0];
}

double Ponto::getZ() const {
    return (*this)[2][0];
}
