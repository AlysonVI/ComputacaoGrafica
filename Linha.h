#ifndef LINHA_H
#define LINHA_H

#include "Drawable.h"

class Linha : public Drawable {
public:
    Linha(const QString& n, const Ponto& p1, const Ponto& p2);
    void draw(QPainter& painter) override;

};

#endif
