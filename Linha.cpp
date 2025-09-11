#include "Linha.h"

Linha::Linha(const QString& n, const Ponto& p1, const Ponto& p2)
    : Drawable(n, ObjectType::Linha, {p1, p2}) {}

void Linha::draw(QPainter& painter){
    painter.drawLine(*(points[0].convertToQPointF()), *(points[1].convertToQPointF()));
}
