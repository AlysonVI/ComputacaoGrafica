#include "Castelo.h"

Castelo::Castelo(const Ponto& p)
    : Drawable("Castelo", ObjectType::Castelo, {p}) {}

void Castelo::draw(QPainter& painter){
    painter.drawLine(*(points[0].convertToQPointF()), *((points[0]).convertToQPointF()));
}
double Castelo::getVariable(){
    return 0;
}
