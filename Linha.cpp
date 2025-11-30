#include "Linha.h"

Linha::Linha(const QString& n, const Ponto& p1, const Ponto& p2)
    : Drawable(n, ObjectType::Linha, {p1, p2}) {}

void Linha::draw(QPainter& painter){
    if (normPoints.isEmpty()) {
        return;
    }
    QPointF p12D(normPoints[0].getX(), normPoints[0].getY());
    QPointF p22D(normPoints[1].getX(), normPoints[1].getY());

    painter.drawLine((p12D), (p22D));
}
