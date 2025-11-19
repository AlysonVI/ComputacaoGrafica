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

// angulo[0] = angulo relativo a x, angulo[1] = angulo relativo a y
QVector<double> Ponto::getAnglesfromVectors(Ponto v1, Ponto v2) {
    double tamv1X = sqrt(v1.getX() * v1.getX() + v1.getZ() * v1.getZ());
    double tamv1Y = sqrt(v1.getY() * v1.getY() + v1.getZ() * v1.getZ());
    double tamv2X = sqrt(v2.getY() * v2.getY() + v2.getZ() * v2.getZ());
    double tamv2Y = sqrt(v2.getX() * v2.getX() + v2.getZ() * v2.getZ());

    // angulo entre a projeção de v1 e v2 no plano yz
    double angleRelativeToX = acos((v1.getY() * v2.getY() + v1.getZ() * v2.getZ())/ (tamv1X * tamv2X));
    // angulo entre a projeção de v1 e v2 no plano xz
    double angleRelativeToY = acos((v1.getX() * v2.getX() + v1.getZ() * v2.getZ())/ (tamv1Y * tamv2Y));

    QVector<double> angles = {angleRelativeToX, angleRelativeToY};
    return angles;
}
