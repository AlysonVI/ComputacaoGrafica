#include "Ponto.h"

Ponto::Ponto(const QString& n, const QPointF& p)
    : Drawable(n, ObjectType::Ponto, {p}) {}

void Ponto::draw(QPainter& painter) const {
    painter.drawPoint(points[0]);
}
