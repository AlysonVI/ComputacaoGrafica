#include "Polygon.h"

Polygon::Polygon(const QString& n, const QVector<QPointF>& pts)
    : Drawable(n, ObjectType::Poligono, pts) {}

void Polygon::draw(QPainter& painter) const {
    painter.drawPolygon(points);
}
