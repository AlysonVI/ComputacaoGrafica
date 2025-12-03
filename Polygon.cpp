#include "Polygon.h"

Polygon::Polygon(const QString& n, const QVector<Ponto>& pts)
    : Drawable(n, ObjectType::Polygon, pts) {}

void Polygon::draw(QPainter& painter){
    if (normPoints.isEmpty()) {
        return;
    }

    painter.drawPolygon(*getQPoints());
}
