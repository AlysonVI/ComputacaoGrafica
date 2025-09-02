#ifndef LINHA_H
#define LINHA_H

#include "Drawable.h"

class Linha : public Drawable {
public:
    Linha(const QString& n, const QPointF& p1, const QPointF& p2);
    void draw(QPainter& painter) const override;
};

#endif
