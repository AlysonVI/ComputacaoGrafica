#ifndef CURVA_H
#define CURVA_H

#include "Drawable.h"

class Curva : public Drawable {
private:
    void casteljau(const Ponto &p0, const Ponto &p1, const Ponto &p2, int n);
public:
    Curva(const QString& n, const Ponto& p0, const Ponto& p1, const Ponto& p2, int suavidade);
    void draw(QPainter& painter) override;
};

#endif

