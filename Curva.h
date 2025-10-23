#ifndef CURVA_H
#define CURVA_H

#include "Drawable.h"

class Curva : public Drawable {
private:
    QVector<Ponto> linhas;
public:
    Curva(const QString& n, const Ponto& p0, const Ponto& p1, const Ponto& p2, int altura);
    void Curva::casteljau(Ponto &p0, Ponto &p1, Ponto &p2, int n);
    void draw(QPainter& painter) override;
};

#endif

