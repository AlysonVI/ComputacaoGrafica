#ifndef PONTO_H
#define PONTO_H

#include "Drawable.h"

class Ponto : public Drawable {
public:
    Ponto(const QString& n, const QPointF& p);
    void draw(QPainter& painter) const override;
};

#endif
