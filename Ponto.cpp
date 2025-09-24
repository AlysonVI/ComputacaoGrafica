#include "Ponto.h"

Ponto::Ponto(double x, double y)
    : Matriz(3,1){
    (*this)[0][0]= x;
    (*this)[1][0]= y;
    (*this)[2][0]= 1;

}

QPointF* Ponto::convertToQPointF(){
    return (new QPointF((*this)[0][0], (*this)[1][0]));
}

void Ponto::draw(QPainter& painter) const {
    painter.drawPoint(*(new QPointF((*this)[0][0], (*this)[1][0])));
}
