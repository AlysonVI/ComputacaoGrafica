#ifndef POLYGON_H
#define POLYGON_H

#include "Drawable.h"

class Polygon : public Drawable {
public:
    Polygon(const QString& n, const QVector<Ponto>& pts);
    void draw(QPainter& painter) override;
};

#endif
