#include "Linha.h"

Linha::Linha(const QString& n, const Ponto& p1, const Ponto& p2)
    : Drawable(n, ObjectType::Linha, {p1, p2}) {}

void Linha::draw(QPainter& painter){
    QPointF p12D(points[0].getX(), points[0].getY());
    QPointF p22D(points[1].getX(), points[1].getY());

    painter.drawLine((p12D), (p22D));
}
