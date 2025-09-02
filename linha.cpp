#include "Linha.h"

Linha::Linha(const QString& n, const QPointF& p1, const QPointF& p2)
    : Drawable(n, ObjectType::Linha, {p1, p2}) {}

void Linha::draw(QPainter& painter) const {
    painter.drawLine(points[0], points[1]);
}
